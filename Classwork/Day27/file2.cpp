#include <iostream>
#include <unistd.h>
#include <sys/types.h>


/*
                                    fork()-28
                            fork()-29                fork()-29
                            fork()-30                fork()-30
                            HW-31                    HW-31
                    fork()-29                               fork()-29
               fork()-30       fork()-30                fork()-30       fork()-30
               HW-31            HW-31                   HW-31           HW-31
        fork()-30              fork()-30                fork()-30   fork()-30
    HW          HW          HW          HW            HW        HW  Hw  HW




*/


using namespace std;


int main()
{
    cout<<"\nBefore fork() Process ID: "<<getpid()<<endl;
    cout<<"\nBefore fork() PPID: "<<getppid()<<endl;

    fork();
    fork();
    fork();
    cout<<"Hello World!"<<endl;

    return 0;
}