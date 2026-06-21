/*

char arrays[CAP]; // strings are declared

*/

#include <iostream>
#define CAP 51
using namespace std;

int main()
{
    char name[CAP];
    int len=0;
    cout<<"\nEnter the name: ";
    scanf("%[^\n]s",name);
    cout<<"Name: "<<name<<endl;

    for(int i=0;i<CAP;i++)
        cout<<name[i]<<"\t Ascii Value = "<<(int)name[i]<<endl;
    
    for(int i=0;i<CAP;i++)
    {
        if(name[i]=='\0')
            break;
        len++;
    }
    cout<<"String lenght="<<len<<endl;
    
    return 0;


}