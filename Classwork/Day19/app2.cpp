#include <iostream>
#include "Person.h"

using namespace std;

int main()
{
    Person *p = new Person[3];
    
    cout<<"[Inside Main Method]"<<endl;
    
    for(int i=0;i<3;i++)
        p[i].setPerson();

    for(int i=0;i<3;i++)
        p[i].dispPerson();
    
        return 0;
}