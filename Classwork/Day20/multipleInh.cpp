/*
Multiple Inheritance
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

//Multilevel -> Person and Employee properties and getting inherited
// to Manager
class Manager: public Employee
{
protected:
    int teamSize;
public:
    Manager(string n, int a, int id, int tsize)
    : Employee(n,a,id)
    {
        this->teamSize = tsize;
    }

    void dispManager()
    {
        dispEmp();
        cout<<"Team Size: "<<teamSize<<endl;
    }

};


class Department //another BC
{
protected:
    string deptName;
public:
    Department(string d="General"): deptName(d) {}

    void dispDept()
    {
        cout<<"Dept: "<<deptName<<endl;
    }

};

//Multiple inheritance: from emp and dept bc, child class is created
class TechLead: public Employee, public Department
{
public:
    TechLead(string n, int a, int id, string dept="General")
    :   Employee(n,a,id), Department(dept)
    {}

    void dispTechLead()
    {
        dispEmp();
        dispDept();
    }
};

int main()
{
    TechLead tl("Vandhana", 23,1011,"Embedded");
    tl.dispTechLead();

    return 0;

}