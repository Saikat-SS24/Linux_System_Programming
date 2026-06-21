/*
demo on shallow copy

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
    Student s1("bhimashankar");
    s1.dispStudent();
    Student s2 = s1;  // shallow copy //default copy constr
    s2.dispStudent();
    s1.setName("Amit");

    s1.dispStudent();
    s2.dispStudent();
    

    return 0;
}