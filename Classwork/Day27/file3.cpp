#include <iostream>
#include <sys/types.h>
#include <unistd.h>

using namespace std;

typedef unsigned long long ULL;

int main()
{
    pid_t PID;
    cout<<"\nWelcome\n";

    PID = fork();
    if(PID == 0)
    {
        //child process
        sleep(2);
        cout<<"\nChild Process Started"<<endl;
        for(ULL i=0;i<1090000;i++)
        {
            if(i%2 == 0)
                cout<<"\nEven = "<<i;
        }
        cout<<"\nChild Process Ended PID: "<<getpid()<<endl;
    }
    else
    {
        //parent process
        cout<<"\nParent Process Started"<<endl;
        cout<<"\nChild Process Started"<<endl;
        for(ULL i=0;i<1090000;i++)
        {
            if(i%2 != 0)
                cout<<"\nOdd = "<<i;
        }
        cout<<"\nParent Process Ended PID: "<<getpid()<<endl;
    }

    cout<<"\nEnd of the Program\n"<<endl;

    return 0;
}