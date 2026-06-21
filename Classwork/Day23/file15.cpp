/*

without iterator
- algo must know container internal
for(int i=-;i<vec.size();i++)
    process(vec[i])

by using iterators
- one aglo works for any container
for(auto it = c.begin();it!=c.end();it++);

operations:
*it -> dereferencing of it value
++it -> advances to the next elem
it++ -> advance, return the old position
--it
it+n -> advaning by n steps (random access)
it1 == it2 => are both iterators at same pos



*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>


using namespace std;


class Employee
{
private:
    int empId;
    string empName;
    double empSalary;
public:
    Employee(int id, string n, double s)
    : empId(id), empName(n), empSalary(s){}

    int getId() const { return empId; }
    string getName() const { return empName;}
    double getSal() const { return empSalary; }

    void setName(string n) { empName = n;}

    void display() const{
        cout<<"\nEmployee Details are\n";
        cout<<"ID: "<<empId<<endl;
        cout<<"Name: "<<empName<<endl;
        cout<<"Salary: "<<empSalary<<endl;
    }
};

int main()
{
    vector<Employee> v1;

    
    v1.emplace_back(Employee(101,"abc1",1011));
    v1.emplace_back(Employee(102,"abc2",1012));
    v1.emplace_back(Employee(103,"abc3",1013));
    v1.emplace_back(Employee(104,"abc4",1014));

    vector<Employee>::iterator it;

    for(it = v1.begin();it!=v1.end();it++)
        it->display();
     v1.emplace_back(Employee(105,"abc5",1015));
    for(it = v1.begin();it!=v1.end();it++)
        it->display();


    for(it = v1.begin();it!=v1.end();it++)
    {
        if(it->getId() == 103)
            it->setName("bhima");
    }
    
    for(it = v1.begin();it!=v1.end();it++)
        it->display();

    it = v1.begin();
    v1.erase(it+2);
    
    for(it = v1.begin();it!=v1.end();it++)
        it->display();


    return 0;
}