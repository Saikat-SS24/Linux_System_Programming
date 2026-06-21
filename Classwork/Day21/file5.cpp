#include <iostream>

using namespace std;

class Employee
{
private:
    int sal;
public:
    Employee(int s): sal(s){}
    friend class HR;
};

class HR
{
public:
    void updateSalary(Employee &e, int newSal){
        e.sal = newSal;
    }

    void display(Employee &e)
    {
        cout<<"Salary: "<<e.sal<<endl;
    }
};

int main()
{
    Employee emp(50000);
    HR hr;
    hr.display(emp);
    hr.updateSalary(emp, 70000);
    hr.display(emp);

    return 0;
}