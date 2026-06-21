#include <stdio.h>
#include <fcntl.h>
#include <semaphore.h>
#define SEM_NAME "/posix_sem"
int main() {
    sem_t *sem = sem_open(SEM_NAME, O_CREAT, 0644, 1);
    printf("POSIX Semaphore created\n");
    sem_close(sem);
    return 0;
}