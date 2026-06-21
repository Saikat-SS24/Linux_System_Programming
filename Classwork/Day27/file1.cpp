#include <iostream>
#include <unistd.h>
#include <sys/types.h>

using namespace std;


int main()
{
    pid_t PID;
    
    cout<<"\nWelcome to System Programming"<<endl;
    
    PID = fork();
    if(PID == 0)
    {
        //child process
        //sleep(10);
        cout<<"\nChild Process"<<endl;
        cout<<"\nPID: "<<PID<<endl;
        cout<<"\nProcess ID (PID): "<<getpid()<<endl;
        cout<<"\nParent Process ID (PPID): "<<getppid()<<endl;
        exit(0);
    }
    else
    {
        //parent process
        
        cout<<"\nParent Process"<<endl;
        cout<<"\nPID: "<<PID<<endl; 
        cout<<"\nProcess ID (PID): "<<getpid()<<endl;
        cout<<"\nParent Process ID (PPID): "<<getppid()<<endl;

        sleep(60);
        cout<<"\nEnd of parent\n";

    }

    
    cout<<"\nEnd of the Program"<<endl;

    return 0;
}