#include "common.h"
#define MAX_BUF 1024
#define PERMS 0666

using namespace std;

int main()
{
     key_t key = ftok("/home/student/25SUB5936_U21", 2026);
     int shmid = shmget(key,1024, PERMS | IPC_CREAT);


     if(shmid < 0)
     {
        perror("shmget");
        return 1;
     }

     cout<<"\nShared mem id: "<<shmid<<endl;
     //char *str1 = (char *)malloc(sizeof(char)*200);
     char *str1 = (char *)shmat(shmid,(void *)0, 0);
     cout<<"\nmessage: "<<str1<<endl;
     
     shmdt(str1);


     return 0;


}