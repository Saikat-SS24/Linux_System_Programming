#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <signal.h>
#include <time.h>
#include <errno.h>

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

// ── Global shared-DB pointer (used by signal handler) ─────────────────────────
static SharedDB *g_db = NULL;

// ═════════════════════════════════════════════════════════════════════════════
//  CRUD operations (all thread-safe via reader-writer lock)
// ═════════════════════════════════════════════════════════════════════════════

static int emp_add(SharedDB *db, const char *name, const char *dept,
                   const char *email, double salary) {
    rw_write_lock(db);

    if (db->count >= MAX_EMPLOYEES) {
        rw_write_unlock(db);
        return -1;  // full
    }
    // Find first free slot (active==0) or use next slot
    int slot = -1;
    for (int i = 0; i < db->count; i++) {
        if (!db->employees[i].active) { slot = i; break; }
    }
    if (slot == -1) slot = db->count++;

    Employee *e  = &db->employees[slot];
    e->id        = db->next_id++;
    e->salary    = salary;
    e->active    = 1;
    strncpy(e->name,  name,  MAX_NAME_LEN  - 1);
    strncpy(e->dept,  dept,  MAX_DEPT_LEN  - 1);
    strncpy(e->email, email, MAX_EMAIL_LEN - 1);

    int assigned_id = e->id;
    rw_write_unlock(db);
    return assigned_id;
}

static int emp_update_salary(SharedDB *db, int id, double new_salary) {
    rw_write_lock(db);
    for (int i = 0; i < db->count; i++) {
        if (db->employees[i].active && db->employees[i].id == id) {
            db->employees[i].salary = new_salary;
            rw_write_unlock(db);
            return 0;
        }
    }
    rw_write_unlock(db);
    return -1;  // not found
}

static int emp_delete(SharedDB *db, int id) {
    rw_write_lock(db);
    for (int i = 0; i < db->count; i++) {
        if (db->employees[i].active && db->employees[i].id == id) {
            db->employees[i].active = 0;
            rw_write_unlock(db);
            return 0;
        }
    }
    rw_write_unlock(db);
    return -1;
}

// Search by name (substring, case-sensitive).  Fills out[] up to max results.
// Returns number of results found.
static int emp_search(SharedDB *db, const char *keyword,
                      Employee *out, int max) {
    int found = 0;
    rw_read_lock(db);
    for (int i = 0; i < db->count && found < max; i++) {
        if (db->employees[i].active &&
            strstr(db->employees[i].name, keyword)) {
            out[found++] = db->employees[i];
        }
    }
    rw_read_unlock(db);
    return found;
}

static void emp_list_all(SharedDB *db) {
    rw_read_lock(db);
    printf("\n" BOLD CYN "%-6s %-22s %-18s %-26s %12s\n" RST,
           "ID", "Name", "Department", "Email", "Salary (INR)");
    printf(CYN "%-6s %-22s %-18s %-26s %12s\n" RST,
           "------","----------------------","------------------",
           "--------------------------","------------");
    int printed = 0;
    for (int i = 0; i < db->count; i++) {
        if (!db->employees[i].active) continue;
        Employee *e = &db->employees[i];
        printf("%-6d %-22s %-18s %-26s %12.2f\n",
               e->id, e->name, e->dept, e->email, e->salary);
        printed++;
    }
    if (!printed) printf(YLW "  (no records)\n" RST);
    printf("\n");
    rw_read_unlock(db);
}

// ═════════════════════════════════════════════════════════════════════════════
//  Worker thread — simulates background tasks (audit, batch updates)
// ═════════════════════════════════════════════════════════════════════════════

typedef struct {
    int       tid;
    SharedDB *db;
} WorkerArg;

static void *worker_thread(void *arg) {
    WorkerArg *wa = (WorkerArg *)arg;
    printf(MAG "[Thread-%d] Started (TID=%lu)\n" RST,
           wa->tid, pthread_self());

    // Each worker does a periodic read-audit every 4 seconds
    for (int cycle = 0; cycle < 3; cycle++) {
        sleep(4);

        rw_read_lock(wa->db);
        int active = 0;
        double total_salary = 0.0;
        for (int i = 0; i < wa->db->count; i++) {
            if (wa->db->employees[i].active) {
                active++;
                total_salary += wa->db->employees[i].salary;
            }
        }
        rw_read_unlock(wa->db);

        printf(MAG "[Thread-%d] Audit #%d: Active=%d  TotalSalary=%.2f\n" RST,
               wa->tid, cycle + 1, active, total_salary);
    }

    printf(MAG "[Thread-%d] Exiting.\n" RST, wa->tid);
    free(wa);
    return NULL;
}

// ═════════════════════════════════════════════════════════════════════════════
//  Signal handler — clean shutdown
// ═════════════════════════════════════════════════════════════════════════════
static void handle_signal(int sig) {
    (void)sig;
    printf(YLW "\n[Server] Caught signal — shutting down...\n" RST);
    shm_destroy(g_db);
    exit(0);
}

// ═════════════════════════════════════════════════════════════════════════════
//  Interactive menu
// ═════════════════════════════════════════════════════════════════════════════
static void print_menu(void) {
    printf(BOLD "\n┌─── Employee Record Manager ─────────────────┐\n" RST);
    printf("│  " YLW "1" RST "  Add Employee                           │\n");
    printf("│  " YLW "2" RST "  List All Employees                     │\n");
    printf("│  " YLW "3" RST "  Search Employee by Name                │\n");
    printf("│  " YLW "4" RST "  Update Employee Salary                 │\n");
    printf("│  " YLW "5" RST "  Delete Employee                        │\n");
    printf("│  " YLW "6" RST "  Show Statistics                        │\n");
    printf("│  " RED "0" RST "  Exit (destroys shared memory)          │\n");
    printf(BOLD "└─────────────────────────────────────────────┘\n" RST);
    printf("Choice: ");
}

// ═════════════════════════════════════════════════════════════════════════════
//  main
// ═════════════════════════════════════════════════════════════════════════════
int main(void) {
    // ── Setup ────────────────────────────────────────────────────────────────
    signal(SIGINT,  handle_signal);
    signal(SIGTERM, handle_signal);

    printf(BOLD GRN
        "╔══════════════════════════════════════════════╗\n"
        "║   Employee Record Management System v1.0    ║\n"
        "║   POSIX Shared Memory + Semaphores +        ║\n"
        "║   Multithreading                            ║\n"
        "╚══════════════════════════════════════════════╝\n" RST);

    g_db = shm_create();
    if (!g_db) { fprintf(stderr, "Failed to create shared memory.\n"); return 1; }

    // ── Spawn worker threads ─────────────────────────────────────────────────
    pthread_t workers[NUM_WORKER_THREADS];
    for (int i = 0; i < NUM_WORKER_THREADS; i++) {
        WorkerArg *wa = malloc(sizeof(WorkerArg));
        wa->tid = i + 1;
        wa->db  = g_db;
        if (pthread_create(&workers[i], NULL, worker_thread, wa) != 0) {
            perror("pthread_create");
        }
        pthread_detach(workers[i]);
    }

    // ── Seed some demo data ──────────────────────────────────────────────────
    emp_add(g_db, "Arjun Sharma",   "Engineering",  "arjun@company.com",   85000.00);
    emp_add(g_db, "Priya Nair",     "HR",           "priya@company.com",   72000.00);
    emp_add(g_db, "Ravi Kumar",     "Finance",      "ravi@company.com",    90000.00);
    emp_add(g_db, "Sneha Patel",    "Engineering",  "sneha@company.com",   95000.00);
    emp_add(g_db, "Vikram Mehta",   "Sales",        "vikram@company.com",  68000.00);
    printf(GRN "[Server] Seeded 5 demo employees.\n" RST);

    // ── Interactive menu loop ────────────────────────────────────────────────
    int choice;
    char buf[256];

    while (1) {
        print_menu();
        if (!fgets(buf, sizeof(buf), stdin)) break;
        choice = atoi(buf);

        if (choice == 0) break;

        switch (choice) {

        case 1: {  // Add
            char name[MAX_NAME_LEN], dept[MAX_DEPT_LEN], email[MAX_EMAIL_LEN];
            double sal;
            printf("  Name   : "); fgets(name,  sizeof(name),  stdin); name[strcspn(name,"\n")] = 0;
            printf("  Dept   : "); fgets(dept,  sizeof(dept),  stdin); dept[strcspn(dept,"\n")] = 0;
            printf("  Email  : "); fgets(email, sizeof(email), stdin); email[strcspn(email,"\n")] = 0;
            printf("  Salary : "); fgets(buf, sizeof(buf), stdin); sal = atof(buf);
            int id = emp_add(g_db, name, dept, email, sal);
            if (id > 0) printf(GRN "  ✔ Added — ID: %d\n" RST, id);
            else        printf(RED "  ✘ Database full.\n" RST);
            break;
        }

        case 2:    // List
            emp_list_all(g_db);
            break;

        case 3: {  // Search
            char kw[MAX_NAME_LEN];
            printf("  Search keyword: "); fgets(kw, sizeof(kw), stdin); kw[strcspn(kw,"\n")] = 0;
            Employee res[MAX_EMPLOYEES];
            int n = emp_search(g_db, kw, res, MAX_EMPLOYEES);
            if (n == 0) { printf(YLW "  No results.\n" RST); break; }
            printf(BOLD CYN "  Found %d result(s):\n" RST, n);
            for (int i = 0; i < n; i++)
                printf("  [%d] %s | %s | %s | %.2f\n",
                       res[i].id, res[i].name, res[i].dept,
                       res[i].email, res[i].salary);
            break;
        }

        case 4: {  // Update salary
            int id; double sal;
            printf("  Employee ID  : "); fgets(buf, sizeof(buf), stdin); id  = atoi(buf);
            printf("  New Salary   : "); fgets(buf, sizeof(buf), stdin); sal = atof(buf);
            if (emp_update_salary(g_db, id, sal) == 0)
                printf(GRN "  ✔ Salary updated.\n" RST);
            else
                printf(RED "  ✘ ID %d not found.\n" RST, id);
            break;
        }

        case 5: {  // Delete
            int id;
            printf("  Employee ID to delete: "); fgets(buf, sizeof(buf), stdin); id = atoi(buf);
            if (emp_delete(g_db, id) == 0)
                printf(GRN "  ✔ Employee %d deleted.\n" RST, id);
            else
                printf(RED "  ✘ ID %d not found.\n" RST, id);
            break;
        }

        case 6: {  // Stats
            rw_read_lock(g_db);
            int active = 0; double total = 0, max_sal = 0, min_sal = 1e12;
            for (int i = 0; i < g_db->count; i++) {
                if (!g_db->employees[i].active) continue;
                active++;
                total += g_db->employees[i].salary;
                if (g_db->employees[i].salary > max_sal) max_sal = g_db->employees[i].salary;
                if (g_db->employees[i].salary < min_sal) min_sal = g_db->employees[i].salary;
            }
            rw_read_unlock(g_db);
            printf(CYN "\n  Active Employees : %d\n"
                       "  Total Salary     : %.2f\n"
                       "  Average Salary   : %.2f\n"
                       "  Highest Salary   : %.2f\n"
                       "  Lowest  Salary   : %.2f\n\n" RST,
                   active, total,
                   active ? total / active : 0.0,
                   active ? max_sal : 0.0,
                   active ? min_sal : 0.0);
            break;
        }

        default:
            printf(YLW "  Invalid option.\n" RST);
        }
    }

    // ── Cleanup ───────────────────────────────────────────────────────────────
    shm_destroy(g_db);
    printf(GRN "[Server] Goodbye!\n" RST);
    return 0;
}
