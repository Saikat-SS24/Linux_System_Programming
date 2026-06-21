#include "common.h"
#include "data.h"

#define PERMS 0666

int main()
{
    key_t key = ftok("/home/student/25SUB5936_TR", 2026);

    int shmid = shmget(key,
                       sizeof(SharedData),
                       PERMS);

    SharedData *data =
        (SharedData *)shmat(shmid,
                            NULL,
                            0);

    cout << "\nFinal Counter Value: "
         << data->counter
         << endl;

    shmdt(data);

    return 0;
}