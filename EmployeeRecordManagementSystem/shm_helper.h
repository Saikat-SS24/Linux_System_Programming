#ifndef SHM_HELPER_H
#define SHM_HELPER_H

#include "common.h"

// Create & initialise shared memory (call once from the server process).
// Returns pointer to SharedDB on success, NULL on error.
SharedDB *shm_create(void);

// Open existing shared memory (call from client / worker processes).
// Returns pointer to SharedDB on success, NULL on error.
SharedDB *shm_open_existing(void);

// Unmap shared memory (does NOT unlink — call shm_destroy for that).
void shm_close(SharedDB *db);

// Unmap + unlink shared memory and semaphores (call from server on shutdown).
void shm_destroy(SharedDB *db);

// ── Reader-Writer lock helpers (implemented inline for simplicity) ─────────────

// Acquire read lock (allows concurrent readers).
static inline void rw_read_lock(SharedDB *db) {
    sem_wait(&db->sem_rdcnt);
    db->reader_count++;
    if (db->reader_count == 1)
        sem_wait(&db->sem_write);   // first reader blocks writers
    sem_post(&db->sem_rdcnt);
}

static inline void rw_read_unlock(SharedDB *db) {
    sem_wait(&db->sem_rdcnt);
    db->reader_count--;
    if (db->reader_count == 0)
        sem_post(&db->sem_write);   // last reader unblocks writers
    sem_post(&db->sem_rdcnt);
}

// Acquire exclusive write lock.
static inline void rw_write_lock(SharedDB *db) {
    sem_wait(&db->sem_write);
}

static inline void rw_write_unlock(SharedDB *db) {
    sem_post(&db->sem_write);
}

#endif // SHM_HELPER_H
