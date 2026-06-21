#include <iostream>

using namespace std;

//forward decalaration of the classes
class Bonus;

class Employee
{
    private:
        float sal;
    public:
        Employee(float s): sal(s){}
        float getSal() { return sal;}
        friend float calculateBonus(Employee &, Bonus &);
    
};

class Bonus
{
    private:
        string level;
    public:
        Bonus(string b): level(b){}
        friend float calculateBonus(Employee &, Bonus &);

};


float calculateBonus(Employee &objE, Bonus &objB)
{
    float Bonus = 0;
    if(objB.level == "1")
        Bonus = objE.sal * 0.2;
    else if(objB.level == "2")
        Bonus = objE.sal * 0.4;
    else if(objB.level == "3")
        Bonus = objE.sal * 0.6;
    if(objB.level == "4"){
        Bonus = objE.sal * 1.0;
        objE.sal = objE.sal+Bonus;
    }
    
    return Bonus;
}

int main()
{
    Employee e1(10000);
    Employee e2(10000);
    Bonus b1("1");
    Bonus b2("2");
    Bonus b3("3");
    Bonus b4("4");

    cout<<calculateBonus(e1,b1)<<endl;
    cout<<calculateBonus(e2,b4)<<endl;
    cout<<"Salary of e2: "<<e2.getSal()<<endl;

    return 0;
    
}