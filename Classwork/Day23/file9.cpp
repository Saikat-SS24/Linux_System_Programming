#include <iostream>
#include <map>
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

    void display() const{
        cout<<"\nEmployee Details are\n";
        cout<<"ID: "<<empId<<endl;
        cout<<"Name: "<<empName<<endl;
        cout<<"Salary: "<<empSalary<<endl;
    }
};

int main()
{
    Employee e1(101,"abc1",1011);
    Employee e2(102,"abc2",1012);
    Employee e3(103,"abc3",1013);
    Employee e4(104,"abc4",1014);

    map<int, Employee> m1;
    m1.insert({e1.getId(),e1});
    m1.insert({e2.getId(),e2});
    m1.insert({e3.getId(),e3});
    m1.insert({e4.getId(),e4});

     for (auto& p : m1){
        cout<<"\n==============\n";
        cout << p.first << " "<<endl;
        p.second.display();
     }

     cout<<endl;


     m1.emplace(105,Employee(105,"abc5",1015));
     for (auto& p : m1){
        cout<<"\n==============\n";
        cout << p.first << " "<<endl;
        p.second.display();
     }
     cout<<endl;
     m1.emplace(12,Employee(106,"abc5",1016));
     for (auto& p : m1){
        cout<<"\n==============\n";
        cout << p.first << " "<<endl;
        p.second.display();
     }
     cout<<endl;


     return 0;
}