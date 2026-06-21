//decalre
/*
struct tagName{
memeber = >public
};

class nameClass
{
public:
    //public sccess specifier
    methods and variable delared here are accessed
    outside the class as well

protected:
//protected access specifier
    //mem and variables delared here will be accessable
    // within the class and inherited class

private:
//private access specifier
//methods or variable decalre here will be accessable within the 
//class only (not in inherited or outside the class)


};

*/

#include <iostream>
#include <string.h>
using namespace std;

class Person
{
    /*
    name, address, phno, gender,age,
    height, weight, bloodgroup
    */
   public:
    string name;
    string address;
    int phno;
    char gender;
    int age;
    float height;
    float weight;
    char bg[4];
};

int main()
{
    //create a object of the class
    Person obj;
    cout<<"Size of the object: "<<sizeof(obj)<<endl;
    cout<<"\nAddress of obj: "<<&obj<<endl;
    obj.age = 24;
    obj.name = "Saikat";
    obj.gender = 'M';
    strcpy(obj.bg , "AB+");

    cout<<"Name: "<<obj.name<<endl;
    cout<<"Age: "<<obj.age<<endl;

    return 0;
}