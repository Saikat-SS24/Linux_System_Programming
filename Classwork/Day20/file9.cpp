#include <iostream>

using namespace std;

class Person
{
protected:
    int age;
    string name;
public:
    Person(int age, string  name): name(name), age(age){}
    virtual void print() = 0 ;
    
};

class Employee: public Person
{
    int id;
public:
    Employee(int age, string name, int id)
    : Person(age,name) {this->id = id;}

    void print(){
        cout<<"Name: "<<name<<endl;
        cout<<"age: "<<age<<endl;
        cout<<"id: "<<id<<endl;
    }
};


class Student : public Person {
    int rollNo;

public:
    Student(int age, string name, int r)
        : Person(age, name), rollNo(r) {}

    void print() override {
        cout << "[Student]\n";
        cout << "Name: " << name << endl;
        cout << "Age: " << age << endl;
        cout << "Roll No: " << rollNo << endl;
        cout << "------------------\n";
    }
};

class Manager : public Person {
    int teamSize;

public:
    Manager(int age, string name, int t)
        : Person(age, name), teamSize(t) {}

    void print() override {
        cout << "[Manager]\n";
        cout << "Name: " << name << endl;
        cout << "Age: " << age << endl;
        cout << "Team Size: " << teamSize << endl;
        cout << "------------------\n";
    }
};



void displayRecords(Person *ptr[], int size)
{
    for (int i = 0; i < size; i++) {
        ptr[i]->print();
    }
}

int main()
{

    /*
    Employee e1(22, "abc1", 101);
    Employee e2(23, "abc2", 102);

    Person* ptr[2];

    ptr[0] = &e1;
    ptr[1] = &e2;

    displayRecords(ptr,2);


    */
    
    Employee e1(22, "Emp1", 101);
    Student s1(20, "Stu1", 501);
    Manager m1(40, "Mgr1", 10);

    Person* ptr[3];

    ptr[0] = &e1;
    ptr[1] = &s1;
    ptr[2] = &m1;

    displayRecords(ptr, 3);
    
    

    return 0;
    
}