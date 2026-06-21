/*
inheritance

*/

#include <iostream>
using namespace std;


class Person //Base class //Parent class
{
protected:
    string name;
    char gender;
    int age;
public:
    Person()
    {
        cout<<"\nDef Constr of Person got called";
        name = "";
        gender = '\0';
        age = 0;
    }

    Person(string n, char g, int a)
    {
        cout<<"\nP Constr of Person got called";
        name = n;
        gender = g;
        age = a;
    }

    void dispPerson(){ 
        cout<<"\nPerson Details";
        cout<<"\nName: "<<name<<endl;
        cout<<"\nGender: "<<gender<<endl;
        cout<<"\nAge: "<<age<<endl;
    }

};

class Employee: public Person
{
private:
    int emp_id;
    int emp_sal;
public:
    Employee(string n, char g, int a, int id, int s)
    {
        cout<<"\nConstr of Employee got called";
        name = n;
        gender = g;
        age = a;
        emp_id = id;
        emp_sal = s;
    }

    void dispEmp()
    {
        dispPerson();
        cout<<"\nEmployee Detailes\n";
        //cout<<"\nName: "<<name<<endl;
        cout<<"\nID: "<<emp_id<<endl;
        cout<<"\nSalary: "<<emp_sal<<endl;
    }
};

int main()
{
    //Person p("xyz", 'm',22);
    //p.dispPerson();
   // p.name = "bhima";
    Employee e("bhima",'m',25,101,10000);
    e.dispEmp();

    return 0;
}