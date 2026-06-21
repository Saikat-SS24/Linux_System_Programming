#include <iostream>
#include <signal.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>

using namespace std;

void chld_handler(int sigNum)
{
    cout<<"\nChild Process terminated\n";
    wait(NULL);
}


int main()
{
    struct sigaction sa;

    sa.sa_handler = chld_handler;

    sigemptyset(&sa.sa_mask);

    sa.sa_flags = 0;

    sigaction(SIGCHLD,&sa, 0);

    int pid = fork();

    if(pid == 0)
    {
        cout<<"\nChild Process started PID: "<<getpid()<<endl;
        sleep(3);
        cout<<"\nChild Exiting.....\n";
    }
    else
    {
        while(1)
        {
            cout<<"\nParent Process running PID: "<<getpid()<<endl;
            sleep(1); 
        }
    }

    return 0;
}
