/*
Run time polymorphism
@run time compiler is mentioning which func to exec.
*/
#include <iostream>

using namespace std;

class Animal
{
public:
    Animal() { cout<<"\nAnimal Cnstr called"<<endl;}
    virtual ~Animal() { cout<<"\nAnimal Destr called"<<endl;}
    
    virtual void makeSound(){ cout<<"\nAnimal Makes Sound"<<endl;} //virtual function

};

class Dog: public Animal
{
public:
    Dog() { cout<<"\nDog Cnstr called"<<endl;}
    ~Dog() { cout<<"\nDog Destr called"<<endl;}
    void makeSound()  override { cout<<"\nWoff"<<endl;} //overriding function
    void move() { cout<<"Walks and jumps"<<endl;}
};

class Cat: public Animal
{
public:
    Cat() { cout<<"\nCat Cnstr called"<<endl;}
    ~Cat() { cout<<"\nCat Destr called"<<endl;}
    void makeSound() override { cout<<"\nMeow"<<endl;}
    void move() { cout<<"Walks, jumps and climb"<<endl;} 
};

int main()
{
    Animal *bcPtr=nullptr;
    //Dog d;
    
    //bcPtr = &d;
    bcPtr = new Dog;
    bcPtr->makeSound();

    delete bcPtr;

    return 0;
}