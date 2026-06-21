/*
multi threading

using posix thread
and using c++ thread

*/

#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include <chrono>

using namespace std;

typedef unsigned long long ULL;

void *findODD(void *);
void *findEven(void *);

ULL sumODD = 0;
ULL sumEven = 0;

struct vargs{
    ULL start;
    ULL end;
};

int main()
{
   ULL start=0, end=19000000000;
   struct vargs args = { 0, 1900000000};
   pthread_t tid1, tid2;

   auto startTime = chrono::high_resolution_clock::now();

   cout<<"[Inside Main function]"<<endl;
   pthread_create(&tid1,NULL,findODD,&args);
   pthread_create(&tid2,NULL,findEven,&args);
   
   pthread_join(tid1, NULL);
   pthread_join(tid2, NULL);
   
   auto endTime = chrono::high_resolution_clock::now();


   cout<<"sumODD="<<sumODD<<endl;
   cout<<"sumEven="<<sumEven<<endl;
   cout<<"\nAfter the Operations\n";
   chrono::duration<double> d = endTime - startTime;

   cout<<"\nExecution Time: "<<d.count()<<" seconds\n";
   pthread_exit(NULL);

   return 0;
}


void *findODD(void *args)
{
    ULL i;
    struct vargs *ptr = (struct vargs*)args;
    ULL start = ptr->start;
    ULL end = ptr->end;
    
    for(i=start;i<end;i++)
    {
        //cout<<"[Inside findODD]"<<endl;
        if(i%2 != 0)
        {
            sumODD += i;
        }
    }  

    return NULL;
}


void *findEven(void *args)
{
    ULL i;
    struct vargs *ptr = (struct vargs*)args;
    ULL start = ptr->start;
    ULL end = ptr->end;

    for(i=start;i<end;i++)
    {
        //cout<<"[Inside findEven]"<<endl;
        if(i%2 == 0)
        {
            sumEven += i;
        }
    }  

    return NULL;
}


