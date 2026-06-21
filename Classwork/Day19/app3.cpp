#include <iostream>
#include "Person.h"

using namespace std;

int main()
{
    Person p1;
    
    cout<<"[Inside Main Method]"<<endl;
    
    p1.setPerson();
    p1.dispPerson();
    
    Person p2 = p1;
    p2.dispPerson();

    cout<<"\nAddress of p1="<<&p1<<endl;
    cout<<"\nAddress of p2="<<&p2<<endl;

    return 0;
}