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
   
    pid_t PID;

    PID = fork();
    if(PID == 0)
    {
        cout<<"\nIn the main Child"<<endl;
        if(fork()==0)
        {
            cout<<"\nSecond Child PID: "<<getpid()<<endl;
            cout<<"\n[FC] PPID : "<<getppid()<<endl;
        }
        else
        {
            sleep(30);
            cout<<"\nParent Child PID: "<<getpid()<<endl;
            cout<<"\nChild's PPID: "<<getppid()<<endl;
        }
    }
    else
    {   
        sleep(40);
        cout<<"\nParent Process PID: "<<getpid()<<endl;
        cout<<"\nPPID: "<<getppid()<<endl;
        if(fork()==0)
        {
            cout<<"\n[Parent][Chld] PID: "<<getpid()<<endl;
            cout<<"\n[Parent]'sChild PPID: "<<getppid()<<endl;
        }
        else
        {
            sleep(10);
            cout<<"\n[Parent] PID: "<<getpid()<<endl;
            cout<<"\nPPID[bash]: "<<getppid()<<endl;
        }
    }

    cout<<"\nEnd of the Program"<<endl;
    
    return 0;
}