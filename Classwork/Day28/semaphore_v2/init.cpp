#include "common.h"
#include "data.h"

#define PERMS 0666

union semun
{
    int val;
};

int main()
{
    key_t key = ftok("/home/student/25SUB5936_TR", 2026);

    // Shared Memory
    int shmid = shmget(key,
                       sizeof(SharedData),
                       PERMS | IPC_CREAT);

    if(shmid < 0)
    {
        perror("shmget");
        exit(EXIT_FAILURE);
    }

    SharedData *data =
        (SharedData *)shmat(shmid,
                            NULL,
                            0);

    data->counter = 0;

    shmdt(data);

    // Semaphore
    int semid = semget(key,
                       1,
                       PERMS | IPC_CREAT);

    if(semid < 0)
    {
        perror("semget");
        exit(EXIT_FAILURE);
    }

    union semun su;

    su.val = 1;

    if(semctl(semid,
              0,
              SETVAL,
              su) < 0)
    {
        perror("semctl");
        exit(EXIT_FAILURE);
    }

    cout << "\nShared Memory and Semaphore Initialized\n";

    return 0;
}