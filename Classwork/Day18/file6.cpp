#include <iostream>
#include <pthread.h>
#include <unistd.h>

using namespace std;


int balance = 1000;
FILE *fp;
pthread_mutex_t myLock;

void *deposit(void *args)
{
    for(int i=0;i<5;i++){
        pthread_mutex_lock(&myLock);
        int temp = balance;
        temp +=100;
        usleep(1000);
        balance = temp;
        fprintf(fp,"Deposit: Balance = %d\n",balance);
        pthread_mutex_unlock(&myLock);
    }

    return NULL;
}


void *withdraw(void *args)
{
    for(int i=0;i<5;i++){
        pthread_mutex_lock(&myLock);
        int temp = balance;
        temp -=50;
        usleep(1000);
        balance = temp;
        fprintf(fp,"Withdraw: Balance = %d\n",balance);
        pthread_mutex_unlock(&myLock);
    }

    return NULL;
}


int main()
{
    pthread_t t1,t2;
    fp = fopen("race.txt", "w");

    pthread_mutex_init(&myLock, NULL);

    pthread_create(&t1, NULL, deposit, NULL);
    pthread_create(&t2, NULL, withdraw, NULL);

    pthread_join(t1,NULL);
    pthread_join(t2,NULL);


    fprintf(fp,"\nFinal Balance = %d\n",balance);

    fclose(fp);
    pthread_mutex_destroy(&myLock);
    
    pthread_exit(NULL);

    return 0;
    
    
}

