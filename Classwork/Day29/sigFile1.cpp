#include <iostream>
#include <signal.h>

using namespace std;


void Menu()
{
    cout<<"\nPress, ";
    cout<<"\n1. Addition";
    cout<<"\n2. Sub";
    cout<<"\n3. exit";
    cout<<"\nChoice: ";
    int ch;
    cin>>ch;
    switch(ch)
    {
        case 1: case 2: 
            cout<<"\nAddition and sub functions are called"<<endl;
            break;
        case 3:
            exit(EXIT_SUCCESS);
        default:
            cout<<"\nEnter the correct choice\n";
            Menu();
    }
}


void sigFunc(int sigNum)
{
    cout<<"\nCaught the signal with sigNum: "<<sigNum<<endl;
    if (sigNum == 11)
    {
        cout<<"\nError: Illegal access to the memory address\n";
        exit(EXIT_FAILURE);
    }
    else if(sigNum == SIGFPE)
    {
        cout<<"\nError: Divide by zero error occured\n";
        exit(EXIT_FAILURE);
    }
    else{
        cout<<"\nUncaught signal <"<<sigNum<<"> number"<<endl;
    }
}


void sigSegv(int sigNum)
{
    cout<<"\nError: Illegal access to the memory address\n";
    exit(EXIT_FAILURE);
}

void sigINT(int sigNum)
{
    Menu();
}

int main()
{
    int a=10, b=0;
    int res=0;
    char *p = (char *)"hello";

    cout<<"\nPress control + c to end up the program"<<endl;

    signal(SIGINT, sigINT);
    signal(SIGHUP, sigFunc);
    signal(SIGCONT, sigFunc);
    signal(SIGQUIT, sigFunc);
    signal(SIGILL, sigFunc);
    signal(SIGSEGV, sigSegv);
    signal(SIGFPE, sigFunc);
    signal(SIGUSR1, sigFunc);

    //p[10] = 'z';
    //res = a/b;
    Menu();
    
    while(1);

    return 0;

}