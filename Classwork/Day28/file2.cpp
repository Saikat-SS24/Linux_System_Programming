#include "common.h"

using namespace std;

int main(int argc, char *argv[])
{
    cout<<"\nWelcome to CPP Programming"<<endl;
    // execl("/home/student/25SUB5936_U21/Classwork/Day28/app", 
    //     "app", argv[1], argv[2], (char*)0);

    // char *temp[3];
    // temp[0] = (char *)"app";
    // temp[1] = (char *)"2";
    // temp[2] = (char *)"5";
    // temp[3] = (char *)0;

    //execv("/home/student/25SUB5936_U21/Classwork/Day28/app",temp);
    
    if(fork()==0)
        execv(argv[1], argv);
    else
    {
        wait(0);
    }

    cout<<"\nEND OF PROGRAM"<<endl;
    return 0;
}