#include "common.h"
#include "data.h"

#define PERMS 0666

int main()
{
    key_t key = ftok("/home/student/25SUB5936_TR", 2026);

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

    if(data == (void *)-1)
    {
        perror("shmat");
        exit(EXIT_FAILURE);
    }

    // Increment counter many times
    for(int i = 0; i < 100; i++)
    {
        int temp = data->counter;

        temp++;

        // Artificial delay
        usleep(1);

        data->counter = temp;
    }

    cout << "\nProcess Completed\n";

    shmdt(data);

    return 0;
}