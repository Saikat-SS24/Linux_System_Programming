#include <iostream>

using namespace std;


void greet(const char *);


int main()
{
    //greet("Saikat");
    //greet("Sheet");

    void (*fPtr)(const char *) = greet;

    fPtr("Saikat");
    fPtr("Sheet");



    return 0;
}
void greet(const char *name)
{
    cout<<"Hello, "<<name<<"\nHow are you doing"<<endl;
}
