#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

// ─── PRODUCER-CONSUMER PROBLEM ───────────────────────────────────────
// Classic problem: one thread PRODUCES data, another CONSUMES it.
// Semaphores coordinate: consumer waits until producer has data.

#define BUFFER_SIZE 5

int buffer[BUFFER_SIZE];
int bufferCount = 0;

sem_t emptySlots;    // Counts how many empty slots (starts at BUFFER_SIZE)
sem_t fullSlots;     // Counts how many filled slots  (starts at 0)
pthread_mutex_t bufMutex;

void* producer(void* arg) {
    for (int i = 1; i <= 8; i++) {
        sem_wait(&emptySlots);           // Wait for an empty slot
        pthread_mutex_lock(&bufMutex);

        // Produce item
        buffer[bufferCount++] = i * 10;
        printf("  Producer: added %d  [buffer size: %d]\n",
               i * 10, bufferCount);

        pthread_mutex_unlock(&bufMutex);
        sem_post(&fullSlots);            // Signal that a slot is now full

        usleep(100000);  // Simulate production time (100ms)
    }
    return NULL;
}

void* consumer(void* arg) {
    for (int i = 0; i < 8; i++) {
        sem_wait(&fullSlots);            // Wait until there's something to consume
        pthread_mutex_lock(&bufMutex);

        // Consume item
        int item = buffer[--bufferCount];
        printf("  Consumer: removed %d [buffer size: %d]\n",
               item, bufferCount);

        pthread_mutex_unlock(&bufMutex);
        sem_post(&emptySlots);           // Signal that a slot is now empty

        usleep(200000);  // Consumer is slower (200ms)
    }
    return NULL;
}

int main() {
    pthread_t prodThread, consThread;

    // Initialize semaphores
    sem_init(&emptySlots, 0, BUFFER_SIZE);  // All slots start empty
    sem_init(&fullSlots,  0, 0);            // No full slots initially
    pthread_mutex_init(&bufMutex, NULL);

    printf("=== Producer-Consumer with Semaphores ===\n\n");

    pthread_create(&prodThread, NULL, producer, NULL);
    pthread_create(&consThread, NULL, consumer, NULL);

    pthread_join(prodThread, NULL);
    pthread_join(consThread, NULL);

    printf("\nAll items produced and consumed.\n");

    // Cleanup
    sem_destroy(&emptySlots);
    sem_destroy(&fullSlots);
    pthread_mutex_destroy(&bufMutex);

    return 0;
}