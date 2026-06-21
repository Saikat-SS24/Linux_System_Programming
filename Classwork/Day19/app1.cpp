#include <iostream>
#include "Person.h"

using namespace std;

int main()
{
    Person *p = new Person[3];
    //Person p1,p2,p3;
    cout<<"[Inside Main Method]"<<endl;
    // p.setName("saikat");
    // p.setAge(24);

    //p.dispPerson();
    //p1.dispPerson();
    /*
    p[0].setName("Saikat");
    p[0].setAge(24);
    p[1].setName("Sheet");
    p[1].setAge(23);
    p[2].setName("Sourav");
    p[2].setAge(24);
    */
    
    for(int i=0;i<3;i++)
    {
        /*string n;
        int a;
        cout<<"Enter details of Person"<<endl;
        cout<<"\nName: ";cin>>n;
        cout<<"\nAge: ";cin>>a;
        p[i].setName(n); p[i].setAge(a);
        */
        p[i].setPerson();

    }
    
    for(int i=0;i<3;i++)
        p[i].dispPerson();
    return 0;
}