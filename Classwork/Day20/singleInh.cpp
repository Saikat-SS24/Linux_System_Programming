/*
Single Inheritance
*/
#include <iostream>

using namespace std;

class Person
{
protected:
    string name;
    int age;
public:
    Person(string name = "Unknown", int age=0){
        this->name = name;
        this->age = age;
    }

    void dispPerson(){
        cout<<"\nName: "<<name<<"\nAge: "<<age<<endl;
    }
};


//single inheritance

class Employee: public Person
{
protected:
    int empid;
public:
    Employee(string n, int a, int id)
    : Person(n,a)
    {
        empid = id;
    }
    void dispEmp()
    {
        dispPerson();
        cout<<"ID: "<<empid<<endl;
    }
};

int main()
{
    Employee e("Saikat", 24,101);
    e.dispEmp();

    return 0;

}