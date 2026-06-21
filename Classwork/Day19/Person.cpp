#include <iostream>
#include "Person.h"

using namespace std;

//implementaion of the class

// :: -> scope resolution op

void Person::setName(const string n) 
{
    name = n;
}

void Person::setAge(int a) 
{
    age = a;
}

string Person::getName()
{
    return name;
}

int Person::getAge() { return age; }

void Person::dispPerson()
{
    cout<<"\nDetails of the Person\n";
    cout<<"\nName: "<<name<<endl;
    cout<<"\nAge: "<<age<<endl;
}

void Person::setPerson()
{
    cout<<"\nEnter Details of the Person\n";
    cout<<"\nName: ";cin>>name;
    cout<<"\nAge: ";cin>>age;
}