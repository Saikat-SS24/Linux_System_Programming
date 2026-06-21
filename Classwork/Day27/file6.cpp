#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fstream>


using namespace std;

typedef unsigned long long ULL;

void Even(fstream &fs)
{
    for(ULL i=0;i<1090000;i++)
    {
        if(i%2 == 0)
            fs <<"Even = "<<i<<endl;
    }
}

void Odd(fstream &fs)
{
    for(ULL i=0;i<1090000;i++)
    {
        if(i%2 != 0)
            fs <<"Odd = "<<i<<endl;
    }
}

int main()
{
    int status;
    int a=10;
    fstream fs;

   // fs.open("Data1.dat", ios::in|ios::out|ios::app);

    // if(!fs){
    //     cout<<"\nUnable to open file"<<endl;
    //     exit(EXIT_FAILURE);
    // }

    if(fork() == 0)
    {
        //child process
        cout<<"\nChild Process PID: "<<getpid()<<endl;
        a = a+100;
        cout<<"\n[child] a="<<a<<endl;
      //  Odd(fs);
      int i;
      cout<<"\nEnter the exit status of child: ";
      cin>>i;
      exit(i);
    }
    else
    {
        wait(&status);
        cout<<"\nParent Process PID: "<<getpid()<<endl;
        a = a+200;
        cout<<"\n[parent] a="<<a<<endl;
        cout<<"\nWIFEXITED = "<<status/256 <<endl;

     //   Even(fs);
    }

   // fs.close();

    cout<<"\nEnd"<<endl;
    return 0;

}



/*
a=10
 if(fork() == 0)
    {
        //child process
        cout<<"\nChild Process PID: "<<getpid()<<endl;
        a = a+100;
        cout<<"\n[child] a="<<a<<endl;
      //  Odd(fs);
    }
    else
    {
        wait(0);
        cout<<"\nParent Process PID: "<<getpid()<<endl;
        a = a+200;
        cout<<"\n[parent] a="<<a<<endl;
     //   Even(fs);
    }

   // fs.close();

    cout<<"\nEnd"<<endl;



//parent process
a=10
 if(fork() == 0)
    {
        //child process
        cout<<"\nChild Process PID: "<<getpid()<<endl;
        a = a+100;
        cout<<"\n[child] a="<<a<<endl;
      //  Odd(fs);
    }
    else
    {
        wait(0);
        cout<<"\nParent Process PID: "<<getpid()<<endl;
        a = a+200;
        cout<<"\n[parent] a="<<a<<endl;
     //   Even(fs);
    }

   // fs.close();

    cout<<"\nEnd"<<endl;




*/
