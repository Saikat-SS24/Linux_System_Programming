#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <string.h>

int main() {
    const int seg_size = 1024;
    int shmid = shmget(IPC_PRIVATE, seg_size, IPC_CREAT | IPC_EXCL | 0666);
    if (shmid == -1) {
        perror("shmget");
        return 1;
    }
    printf("Writer: Shared memory ID: %d\n", shmid);

    char* shm = (char*)shmat(shmid, NULL, 0);
    if (shm == (char*)-1) {
        perror("shmat");
        return 1;
    }

    strcpy(shm, "Hello from shared memory!");

    shmdt(shm);
    printf("Writer: Wrote message and detached.\n");
    return 0;
}