#ifndef COMMON_H
#define COMMON_H

#include <semaphore.h>
#include <time.h>

// ── Tunables ──────────────────────────────────────────────────────────────────
#define MAX_EMPLOYEES     100
#define MAX_NAME_LEN       64
#define MAX_DEPT_LEN       32
#define MAX_EMAIL_LEN      64
#define NUM_WORKER_THREADS  4   // concurrent worker threads per process

// ── POSIX IPC names ───────────────────────────────────────────────────────────
#define SHM_NAME   "/emp_shm"        // shared memory object
#define SEM_WRITE  "/emp_sem_write"  // write mutex  (binary semaphore)
#define SEM_READ   "/emp_sem_read"   // reader count mutex
#define SEM_RDCNT  "/emp_sem_rdcnt"  // reader count guard

// ── Employee record ───────────────────────────────────────────────────────────
typedef struct {
    int    id;
    char   name [MAX_NAME_LEN];
    char   dept [MAX_DEPT_LEN];
    char   email[MAX_EMAIL_LEN];
    double salary;
    int    active;          // 1 = exists, 0 = deleted
} Employee;

// ── Shared-memory region layout ───────────────────────────────────────────────
//   Lives at the start of the POSIX shared-memory object.
//   Semaphores are stored INSIDE shared memory so every process shares them.
typedef struct {
    // Embedded POSIX semaphores (process-shared)
    sem_t  sem_write;      // exclusive writer lock
    sem_t  sem_rdcnt;      // protects reader_count below
    int    reader_count;   // active concurrent readers

    // Database
    int      count;                    // total slots used (including deleted)
    int      next_id;                  // auto-increment counter
    Employee employees[MAX_EMPLOYEES];
} SharedDB;

#endif // COMMON_H
