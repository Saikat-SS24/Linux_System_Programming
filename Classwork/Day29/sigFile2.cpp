#include <iostream>
#include <signal.h>
#include <cstring>
#include <stdlib.h>


using namespace std;

void sigHandle(int sigNum)
{
    if(sigNum == 11)
    {
        cout<<"\nSignal Caught: "<<sigNum<<endl;
        cout<<"\nSegmentation fault occured\n";
        exit(EXIT_FAILURE);
    }
    else if(sigNum == 10)
    {
        cout<<"\nWelcome User\n"<<endl;
    }
    else
    {
        cout<<"\nUncaught Signal\n";
    }
}


void mystrcat(char *str1, char *str2)
{
    strcat(str1, str2);
}

int main()
{
    struct sigaction sa;

    sa.sa_handler = &sigHandle;
    sa.sa_flags = SA_RESTART;

    sigaction(SIGSEGV, &sa, 0);
    sigaction(SIGUSR1, &sa, 0);

    raise(SIGUSR1);

    char *s1 = (char *)malloc(10);
    char *s2 = (char *)malloc(10);

    strcpy(s2,"Hello");
    mystrcat(s1, s2);
    cout<<s1<<endl;

    delete [] s2;
    delete [] s1;

    return 0;


}