//#pragma once
//Person Class
// decalration of the class


#ifndef PERSON_H
#define PERSON_H

#include <iostream>
using namespace std;

class Person
{
private:
    string name;
    int age;
public:
    Person(){
        cout<<"\nConstr got invoked\n";
        name = "xyz";
        age = 0;
    }

    Person(const string n, const int a)
    {
        cout << "\nParametarized constr got invoked";
        name = n;
        age = a;
    }

    Person(const Person &obj)
    {
        cout << "\n Copy const got invoked\n";
        name = "Mr/Mss. " + obj.name;
        age = obj.age;
    }
public:
    void setName(const string);
    void setAge(int);
    string getName();
    int getAge();
    void setPerson();
    void dispPerson();
};


#endif
