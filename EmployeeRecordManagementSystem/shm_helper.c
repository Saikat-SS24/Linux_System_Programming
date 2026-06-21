#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <semaphore.h>

#include "common.h"
#include "shm_helper.h"

// ── Create & initialise ───────────────────────────────────────────────────────
SharedDB *shm_create(void) {
    // Remove any stale objects from a previous run
    shm_unlink(SHM_NAME);

    int fd = shm_open(SHM_NAME, O_CREAT | O_RDWR, 0666);
    if (fd < 0) { perror("shm_open(create)"); return NULL; }

    if (ftruncate(fd, sizeof(SharedDB)) < 0) {
        perror("ftruncate"); close(fd); return NULL;
    }

    SharedDB *db = mmap(NULL, sizeof(SharedDB),
                        PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    close(fd);
    if (db == MAP_FAILED) { perror("mmap(create)"); return NULL; }

    // Zero-initialise the whole region
    memset(db, 0, sizeof(SharedDB));
    db->next_id = 1;

    // Initialise process-shared semaphores (pshared=1)
    if (sem_init(&db->sem_write, 1, 1) < 0) { perror("sem_init(write)"); return NULL; }
    if (sem_init(&db->sem_rdcnt, 1, 1) < 0) { perror("sem_init(rdcnt)"); return NULL; }

    printf("[SHM] Shared memory created (%zu bytes)\n", sizeof(SharedDB));
    return db;
}

// ── Open existing ─────────────────────────────────────────────────────────────
SharedDB *shm_open_existing(void) {
    int fd = shm_open(SHM_NAME, O_RDWR, 0666);
    if (fd < 0) { perror("shm_open(existing)"); return NULL; }

    SharedDB *db = mmap(NULL, sizeof(SharedDB),
                        PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    close(fd);
    if (db == MAP_FAILED) { perror("mmap(existing)"); return NULL; }
    return db;
}

// ── Close (unmap only) ────────────────────────────────────────────────────────
void shm_close(SharedDB *db) {
    if (db) munmap(db, sizeof(SharedDB));
}

// ── Destroy (unmap + unlink) ──────────────────────────────────────────────────
void shm_destroy(SharedDB *db) {
    if (!db) return;
    sem_destroy(&db->sem_write);
    sem_destroy(&db->sem_rdcnt);
    munmap(db, sizeof(SharedDB));
    shm_unlink(SHM_NAME);
    printf("[SHM] Shared memory destroyed.\n");
}
