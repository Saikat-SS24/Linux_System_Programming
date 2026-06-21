#include "common.h"
#include "data.h"

#define PERMS 0666

int main()
{
    key_t key = ftok("/home/student/25SUB5936_TR", 2026);

    int shmid = shmget(key,
                       sizeof(SharedData),
                       PERMS | IPC_CREAT);

    SharedData *data =
        (SharedData *)shmat(shmid,
                            NULL,
                            0);

    data->counter = 0;

    cout << "\nCounter Initialized to 0\n";

    shmdt(data);

    return 0;
}