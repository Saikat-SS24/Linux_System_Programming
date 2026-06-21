#include "common.h"

using namespace std;


int main()
{
    int fd[2];
    pipe(fd);

    // cout<<fd[0]<<endl;
    // cout<<fd[1]<<endl;
    // write(fd[1], "hello",5);
    // char temp[20];
    // read(fd[0],temp,20);

    // cout<<"temp="<<temp<<endl;

    // read(fd[0],temp,20);

    // cout<<"temp="<<temp<<endl;

    if(fork() == 0)
    {
        cout << "\nchild process" << endl;
        close(fd[0]);
        write(fd[1], "helloWorld",10);
        close(fd[1]);
    }
    else
    {
        cout << "\nParent process" << endl;
        close(fd[1]);
        char temp[20];
        memset(temp,'\0',20);
        read(fd[0],temp,20);

        cout<<"temp="<<temp<<endl;
        close(fd[0]);
    }

    

    return 0;
       
}