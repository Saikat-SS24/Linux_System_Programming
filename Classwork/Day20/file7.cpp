/*

Pure virtual function:
by making a function pure virtual you are making
mandatory to implement the base class function
defined in the derived class

virtual funcName() = 0; //pure vitual function


these are defined in Base class

*/

#include <iostream>

using namespace std;


//ABC -> Abstract Base Class
class Animal
{
public:
    virtual ~Animal() {}
    virtual void sound() = 0; //pure virtual function
    virtual void move() = 0;
};

class Dog: public Animal
{
    int *ptr;
public:
    Dog(){ptr =new int;}
    void sound() { cout<<"\nDog Barks"<<endl;}
    void move() { cout<<"\nDog can walk, run and jump"<<endl;}
    void hunt() {cout<<"\nDog can hunt"<<endl;}
    ~Dog(){ delete ptr;}
};


int main()
{
    // Dog d;
    // d.hunt();
    // d.sound();
    // d.move();

    Animal *bcPtr = new Dog;
    bcPtr->move();
    bcPtr->sound();


    delete bcPtr;
    
    return 0;
}

