#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>

int main() {
    int shmid;
    printf("Reader: Enter shmid from writer: ");
    scanf("%d", &shmid);

    char* shm = (char*)shmat(shmid, NULL, 0);
    if (shm == (char*)-1) {
        perror("shmat");
        return 1;
    }
    printf("Reader: Message: %s\n", shm);

    shmdt(shm);
    printf("Reader: Detached.\n");
    return 0;
}