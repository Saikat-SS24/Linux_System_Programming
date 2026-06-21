#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

using namespace std;


int main()
{
    pid_t pid;

    pid = fork();

    if(pid > 0)
    {
        //parent process
        wait(0);
        cout<<"\nParent Process: PID = "<<getpid()<<endl;
    }
    else if(pid == 0)
    {
        //child process
        cout<<"\nChild Process: PID = "<<getpid()<<endl;
    }
    else
        cout<<"\nUnable to create child"<<endl;
    
    cout<<"\nEnd"<<endl;

    return 0;

}