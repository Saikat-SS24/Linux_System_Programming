#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <time.h>

#include "common.h"
#include "shm_helper.h"

// ── ANSI colours ──────────────────────────────────────────────────────────────
#define RST  "\033[0m"
#define BOLD "\033[1m"
#define GRN  "\033[32m"
#define YLW  "\033[33m"
#define CYN  "\033[36m"
#define RED  "\033[31m"
#define MAG  "\033[35m"
#define BLU  "\033[34m"

// ── Per-thread task argument ──────────────────────────────────────────────────
typedef struct {
    int       tid;
    SharedDB *db;
    int       task;   // 0=reader  1=writer  2=searcher
} TaskArg;

// ── Thread: concurrent reader ─────────────────────────────────────────────────
static void *reader_thread(void *arg) {
    TaskArg *ta = (TaskArg *)arg;
    printf(CYN "[Reader-%d] TID=%lu  Acquiring read lock...\n" RST,
           ta->tid, pthread_self());

    rw_read_lock(ta->db);

    printf(CYN "[Reader-%d] READ LOCK acquired — scanning records...\n" RST, ta->tid);
    int active = 0;
    for (int i = 0; i < ta->db->count; i++) {
        if (ta->db->employees[i].active) {
            active++;
            // Simulate read processing time
            usleep(50000);  // 50 ms
        }
    }
    printf(CYN "[Reader-%d] Found %d active employees. Releasing lock.\n" RST,
           ta->tid, active);

    rw_read_unlock(ta->db);
    free(ta);
    return NULL;
}

// ── Thread: concurrent writer ─────────────────────────────────────────────────
static void *writer_thread(void *arg) {
    TaskArg *ta = (TaskArg *)arg;
    printf(MAG "[Writer-%d] TID=%lu  Acquiring write lock...\n" RST,
           ta->tid, pthread_self());

    rw_write_lock(ta->db);

    printf(MAG "[Writer-%d] WRITE LOCK acquired.\n" RST, ta->tid);
    // Add a new employee record
    if (ta->db->count < MAX_EMPLOYEES) {
        char name[MAX_NAME_LEN];
        snprintf(name, sizeof(name), "ClientEmp_%d", ta->tid);
        int slot = ta->db->count++;
        Employee *e = &ta->db->employees[slot];
        e->id     = ta->db->next_id++;
        e->salary = 50000.0 + ta->tid * 1000.0;
        e->active = 1;
        strncpy(e->name,  name,             MAX_NAME_LEN  - 1);
        strncpy(e->dept,  "Remote",         MAX_DEPT_LEN  - 1);
        strncpy(e->email, "client@emp.com", MAX_EMAIL_LEN - 1);
        printf(MAG "[Writer-%d] Added employee ID=%d name=%s\n" RST,
               ta->tid, e->id, e->name);
        usleep(80000);  // 80 ms — simulate write processing
    }

    rw_write_unlock(ta->db);
    printf(MAG "[Writer-%d] WRITE LOCK released.\n" RST, ta->tid);
    free(ta);
    return NULL;
}

// ── Thread: searcher ──────────────────────────────────────────────────────────
static void *searcher_thread(void *arg) {
    TaskArg *ta = (TaskArg *)arg;
    const char *kw = "Sharma";   // demo search keyword

    printf(BLU "[Searcher-%d] TID=%lu  Searching for \"%s\"...\n" RST,
           ta->tid, pthread_self(), kw);

    rw_read_lock(ta->db);
    int found = 0;
    for (int i = 0; i < ta->db->count; i++) {
        if (ta->db->employees[i].active &&
            strstr(ta->db->employees[i].name, kw)) {
            printf(BLU "[Searcher-%d] Found: [%d] %s | %s | %.2f\n" RST,
                   ta->tid,
                   ta->db->employees[i].id,
                   ta->db->employees[i].name,
                   ta->db->employees[i].dept,
                   ta->db->employees[i].salary);
            found++;
        }
    }
    rw_read_unlock(ta->db);

    if (!found)
        printf(BLU "[Searcher-%d] No results for \"%s\".\n" RST, ta->tid, kw);
    free(ta);
    return NULL;
}

// ── Demo: stress test with mixed reader/writer/searcher threads ───────────────
static void run_concurrent_demo(SharedDB *db) {
    printf(BOLD YLW
        "\n╔══════════════════════════════════════════════╗\n"
        "║  Concurrent Thread Demo (Client Process)    ║\n"
        "║  Launching: 3 Readers, 2 Writers,           ║\n"
        "║             2 Searchers simultaneously      ║\n"
        "╚══════════════════════════════════════════════╝\n" RST);

    // Thread count breakdown
    int n_readers   = 3;
    int n_writers   = 2;
    int n_searchers = 2;
    int total = n_readers + n_writers + n_searchers;

    pthread_t *threads = malloc(total * sizeof(pthread_t));
    int t = 0;

    // Readers
    for (int i = 0; i < n_readers; i++) {
        TaskArg *ta = malloc(sizeof(TaskArg));
        ta->tid  = i + 1;
        ta->db   = db;
        ta->task = 0;
        pthread_create(&threads[t++], NULL, reader_thread, ta);
    }

    // Writers (interleaved — tests lock contention)
    for (int i = 0; i < n_writers; i++) {
        TaskArg *ta = malloc(sizeof(TaskArg));
        ta->tid  = i + 1;
        ta->db   = db;
        ta->task = 1;
        pthread_create(&threads[t++], NULL, writer_thread, ta);
    }

    // Searchers
    for (int i = 0; i < n_searchers; i++) {
        TaskArg *ta = malloc(sizeof(TaskArg));
        ta->tid  = i + 1;
        ta->db   = db;
        ta->task = 2;
        pthread_create(&threads[t++], NULL, searcher_thread, ta);
    }

    // Wait for all
    for (int i = 0; i < total; i++)
        pthread_join(threads[i], NULL);

    free(threads);
    printf(GRN "\n[Client] All threads completed.\n" RST);
}

// ── Interactive menu ──────────────────────────────────────────────────────────
static void print_menu(void) {
    printf(BOLD "\n┌─── Client Menu ──────────────────────────────┐\n" RST);
    printf("│  " YLW "1" RST "  View All Employees (read-lock)          │\n");
    printf("│  " YLW "2" RST "  Search Employee by Name                 │\n");
    printf("│  " YLW "3" RST "  Run Concurrent Thread Demo              │\n");
    printf("│  " YLW "4" RST "  Show Shared Memory Stats                │\n");
    printf("│  " RED "0" RST "  Exit                                    │\n");
    printf(BOLD "└──────────────────────────────────────────────┘\n" RST);
    printf("Choice: ");
}

// ═════════════════════════════════════════════════════════════════════════════
//  main
// ═════════════════════════════════════════════════════════════════════════════
int main(void) {
    printf(BOLD GRN
        "╔══════════════════════════════════════════════╗\n"
        "║   Employee Record Client v1.0               ║\n"
        "║   Connecting to shared memory...            ║\n"
        "╚══════════════════════════════════════════════╝\n" RST);

    SharedDB *db = shm_open_existing();
    if (!db) {
        fprintf(stderr, RED "Cannot open shared memory. Is the server running?\n" RST);
        return 1;
    }
    printf(GRN "[Client] Connected to shared memory.\n" RST);

    char buf[256];
    int choice;

    while (1) {
        print_menu();
        if (!fgets(buf, sizeof(buf), stdin)) break;
        choice = atoi(buf);

        if (choice == 0) break;

        switch (choice) {

        case 1: {  // List all (read-lock)
            rw_read_lock(db);
            printf(BOLD CYN "\n%-6s %-22s %-18s %-26s %12s\n" RST,
                   "ID","Name","Department","Email","Salary");
            printf(CYN "%-6s %-22s %-18s %-26s %12s\n" RST,
                   "------","----------------------","------------------",
                   "--------------------------","------------");
            int found = 0;
            for (int i = 0; i < db->count; i++) {
                if (!db->employees[i].active) continue;
                Employee *e = &db->employees[i];
                printf("%-6d %-22s %-18s %-26s %12.2f\n",
                       e->id, e->name, e->dept, e->email, e->salary);
                found++;
            }
            rw_read_unlock(db);
            if (!found) printf(YLW "  (no records)\n" RST);
            break;
        }

        case 2: {  // Search
            char kw[MAX_NAME_LEN];
            printf("  Keyword: "); fgets(kw, sizeof(kw), stdin);
            kw[strcspn(kw, "\n")] = 0;

            rw_read_lock(db);
            int found = 0;
            for (int i = 0; i < db->count; i++) {
                if (db->employees[i].active &&
                    strstr(db->employees[i].name, kw)) {
                    Employee *e = &db->employees[i];
                    printf(GRN "  [%d] %s | %s | %s | %.2f\n" RST,
                           e->id, e->name, e->dept, e->email, e->salary);
                    found++;
                }
            }
            rw_read_unlock(db);
            if (!found) printf(YLW "  No results for \"%s\".\n" RST, kw);
            break;
        }

        case 3:  // Concurrent demo
            run_concurrent_demo(db);
            break;

        case 4: {  // Stats
            rw_read_lock(db);
            int active = 0; double total = 0;
            for (int i = 0; i < db->count; i++) {
                if (db->employees[i].active) {
                    active++;
                    total += db->employees[i].salary;
                }
            }
            rw_read_unlock(db);
            printf(CYN "\n  SHM Object      : %s\n"
                       "  Total slots     : %d\n"
                       "  Active records  : %d\n"
                       "  Total salary    : %.2f\n"
                       "  Avg salary      : %.2f\n\n" RST,
                   SHM_NAME, db->count, active, total,
                   active ? total / active : 0.0);
            break;
        }

        default:
            printf(YLW "  Invalid option.\n" RST);
        }
    }

    shm_close(db);
    printf(GRN "[Client] Disconnected. Goodbye!\n" RST);
    return 0;
}
