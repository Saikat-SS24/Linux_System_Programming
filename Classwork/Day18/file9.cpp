#include <iostream>
#include <string.h>

using namespace std;


class Person{

private:    
    string name;
    char g; 
    int age;

public:
    //getter and setter
    void setName(const string n)
    {
        name  = to_Ext(n);
        //name = n;
    }
    void setAge(int a)
    {
        age = a;
    }
    void setGender(char gen)
    {
        g = gen;
    }

    string getName() //encapsulation
    {
        return name;
    }
    int getAge()
    { return age;}
    char getGender() { return g;}

    void setDetails()
    {
        cout<<"\nEnter the details of the Person\n";
        cout<<"\nName: ";cin>>name;
        cout<<"\nAge: ";cin>>age;
        cout<<"\nGender: ";cin>>g;
    }

    void printDetails()
    {
        cout<<"\nDetails of the Person\n";
        cout<<"\nName: "<<name;
        cout<<"\nAge: "<<age;
        cout<<"\nGender: "<<g<<endl;
    }

private:
    string to_Ext(string n) //abstraction
    {
        n = n+" Sheet";
        return n;
    }
};

int main()
{
    Person obj1;
    obj1.setName("Saikat");
    obj1.setAge(24);
    obj1.setGender('M');

    cout<<"Name: "<<obj1.getName()<<endl;
    cout<<"Age: "<<obj1.getAge()<<endl;
    cout<<"Gender: "<<obj1.getGender()<<endl;

    Person obj2;
    obj2.setDetails();
    obj2.printDetails();

    obj2.setAge(50);
    obj2.printDetails();
   
    
    return 0;
}