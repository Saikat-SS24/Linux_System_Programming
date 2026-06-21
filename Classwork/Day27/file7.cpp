#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fstream>


using namespace std;



int main()
{
    int status;
    int a=10;
    

    if(fork() == 0)
    {
        //child process
        cout<<"\nChild Process PID: "<<getpid()<<endl;
        a = a+100;
        cout<<"\n[child] a="<<a<<endl;
      
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

     
    }

   

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
