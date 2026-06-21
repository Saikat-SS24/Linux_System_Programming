/*
function overide
*/
#include <iostream>

using namespace std;

class Animal
{
public:
    void makeSound(){ cout<<"\nAnimal Makes Sound"<<endl;}
};

class Dog: public Animal
{
public:
    void makeSound()  { cout<<"\nWoff"<<endl;} //overriding function
    void move() { cout<<"Walks and jumps"<<endl;}
};

class Cat: public Animal
{
public:
    void makeSound () { cout<<"\nMeow"<<endl;}
    void move() { cout<<"Walks, jumps and climb"<<endl;} 
};

int main()
{
    Animal a;
    a.makeSound();
    Dog objD;
    objD.makeSound();
    objD.move();

    Cat objC;
    objC.makeSound();
    objC.move();
    return 0;
}