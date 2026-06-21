#include <iostream>
#include <pthread.h>
#include <unistd.h>

using namespace std;

void *myThreadFunc(void *args)
{
    sleep(1);
    cout<<"\nHello, This is a CPP Programming Class\n";
    return nullptr;
}

int main()
{
    pthread_t t1;
    cout<<"\nBefore thread is created\n";
    pthread_create(&t1,NULL,myThreadFunc,NULL);
    cout<<"\nThread id: "<<t1<<endl;
    pthread_join(t1,NULL);
    cout<<"\nAfter the thread\n";

    return 0;
}