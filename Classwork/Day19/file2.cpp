/*
demo on deep copy

*/

#include <iostream>
#include <cstring>

using namespace std;

class Student
{
private:
    char *name;
public:
    Student(const char *n)
    {
       name = new char[strlen(n)+1];
       strcpy(name,n);
    }

    Student(const Student &obj)
    {
        //copy constr
        // cout<<"\nCpy constr called\n";
        name = new char[strlen(obj.name)+1];
        strcpy(name, obj.name); //deep copy
    }

    void setName(const char *n)
    {
        strcpy(name, n);
    }
    ~Student()
    {
        cout<<"\nDestr called\n";
        delete [] name;
    }

    void dispStudent() { cout<<"\nName: "<<name<<endl; }

};


int main()
{
    Student s1("saikatsheet");
    s1.dispStudent();
    Student s2 = s1;  // deep copy //copy constr
    //Student s2(s1);
    s2.dispStudent();
    s1.setName("Sourav");

    s1.dispStudent();
    s2.dispStudent();
    

    return 0;
}