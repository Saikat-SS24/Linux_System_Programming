/*
strtok => tokenzing the string

*/

#include <cstring> //include <string.h>
#include <iostream>

using namespace std;

int main()
{

    //char line[] = "This is a CPP programming class";
    char emp_rec[] = "amit|25|M|99999|20000|SE";
    char *temp=nullptr;
    char words[10][50];
    /*
    temp = strtok(line," ");
    cout<<"temp="<<temp<<endl;

    temp = strtok(NULL," ");
    cout<<"temp="<<temp<<endl;

    temp = strtok(NULL," ");
    cout<<"temp="<<temp<<endl;

    temp = strtok(NULL," ");
    cout<<"temp="<<temp<<endl;

    temp = strtok(NULL," ");
    cout<<"temp="<<temp<<endl;

    temp = strtok(NULL," ");
    cout<<"temp="<<temp<<endl;

    temp = strtok(NULL," ");
    if(temp != NULL)
        cout<<"temp="<<temp<<endl;
    else   
        cout<<"End of the string"<<endl;

    */
    cout<<"\n==============\n";
    //temp = strtok(line," ");
    temp = strtok(emp_rec,"|");
    
    int i=0;
    while(temp != NULL)
    {
        cout<<"temp: "<<temp<<endl;
        strcpy(words[i++],temp);
        temp = strtok(NULL,"|");

    }
    cout<<"\n==============\n";
    
    for(int it=0;it<i;it++)
        cout<<words[it]<<endl;
    cout<<endl;
    return 0;
}


