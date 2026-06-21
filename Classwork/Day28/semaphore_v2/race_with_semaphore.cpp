#include "common.h"
#include "data.h"

#define PERMS 0666

int main()
{
    key_t key = ftok("/home/student/25SUB5936_TR", 2026);

    int shmid = shmget(key,
                       sizeof(SharedData),
                       PERMS);

    if(shmid < 0)
    {
        perror("shmget");
        exit(EXIT_FAILURE);
    }

    SharedData *data =
        (SharedData *)shmat(shmid,
                            NULL,
                            0);

    if(data == (void *)-1)
    {
        perror("shmat");
        exit(EXIT_FAILURE);
    }

    // Access existing semaphore
    int semid = semget(key,
                       1,
                       PERMS);

    if(semid < 0)
    {
        perror("semget");
        exit(EXIT_FAILURE);
    }

    struct sembuf lock;
    struct sembuf unlock;

    lock.sem_num = 0;
    lock.sem_op  = -1;
    lock.sem_flg = 0;

    unlock.sem_num = 0;
    unlock.sem_op  = 1;
    unlock.sem_flg = 0;

    for(int i = 0; i < 100; i++)
    {
        // LOCK
        semop(semid, &lock, 1);

        // CRITICAL SECTION
        int temp = data->counter;

        temp++;

        usleep(1);

        data->counter = temp;

        // UNLOCK
        semop(semid, &unlock, 1);
    }

    cout << "\nProcess Completed\n";

    shmdt(data);

    return 0;
}