#include <iostream>
#define SEQCOUNT 6

using namespace std;

int checkHW();
int checkOS();
int checkConfig();
int checkStatus();
int applyConfig();
int checkNW();
int runApp();

//void initFunc(int *(*)(), int);


typedef int (*FunctPtr)(); 
int main()
{
    FunctPtr seq[SEQCOUNT] = {checkHW, checkOS, checkConfig,checkStatus, applyConfig, checkNW};
    int count=0, ret=0;
    for(int i=0;i<SEQCOUNT;i++)
    {
            ret = seq[i]();
            if(ret == 0)
                count++;
    }

    if(count == SEQCOUNT)
        runApp();
    else
        cout<<"\nSomething went wrong\n";

    return 0;
}
/*
void initFunc(int *(*arr)(), int seqCount)
{
    for(int i=0;i<seqCount;i++)
        arr[i];
}
*/




int checkHW()
{
    cout<<"Checks for hardward component"<<endl;
    cout<<"\nAll hardware components are OK (1/0): ";
    int val;
    cin>>val;
    return val;
}

int checkNW()
{
    cout<<"Checks for Network"<<endl;
    cout<<"\nNetwork is present (1/0): ";
    int val;
    cin>>val;
    return val;
}



int checkOS()
{
    cout<<"Checks for Kernel"<<endl;
    cout<<"\nis Kernel compatible to HW (1/0): ";
    int val;
    cin>>val;
    return val;
}

int checkConfig()
{
    cout<<"Checks for config file (config.xml)"<<endl;
    cout<<"\nconfig file is Present (1/0): ";
    int val;
    cin>>val;
    return val;
}

int checkStatus()
{
    cout<<"Checks for latest status file (status.xml)"<<endl;
    cout<<"\nStatus file is Present (1/0): ";
    int val;
    cin>>val;
    return val;
}

int applyConfig()
{
    cout<<"\nApplied the config"<<endl;
    return 0;   
}

int runApp()
{
    cout<<"\nApplication is running now\n";
    return 0;
}

