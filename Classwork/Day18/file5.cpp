#include <iostream>
#include <pthread.h>
#include <unistd.h>

using namespace std;


int balance = 1000;
FILE *fp;

void *deposit(void *args)
{
    for(int i=0;i<5;i++){
        int temp = balance;
        temp +=100;
        usleep(1000);
        balance = temp;
        fprintf(fp,"Deposit: Balance = %d\n",balance);
    }

    return NULL;
}


void *withdraw(void *args)
{
    for(int i=0;i<5;i++){
        int temp = balance;
        temp -=50;
        usleep(1000);
        balance = temp;
        fprintf(fp,"Withdraw: Balance = %d\n",balance);
    }

    return NULL;
}


int main()
{
    pthread_t t1,t2;
    fp = fopen("race.txt", "w");

    pthread_create(&t1, NULL, deposit, NULL);
    pthread_create(&t2, NULL, withdraw, NULL);

    pthread_join(t1,NULL);
    pthread_join(t2,NULL);


    fprintf(fp,"\nFinal Balance = %d\n",balance);

    fclose(fp);
    pthread_exit(NULL);

    return 0;
    
    
}

