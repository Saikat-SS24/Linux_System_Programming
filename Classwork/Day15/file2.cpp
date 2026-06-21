#include <iostream>
#include <cstring>

using namespace std;

typedef struct person
{
    char name[20];
    int age;
}PERSON;


struct {
    int id;
    char title[20];
}b1,b2;

//typedef struct person PERSON;

void getDetails(PERSON *p)
{
    cout<<"\nEnter the details of the Person"<<endl;
    cout<<"Name: ";
    cin>>p->name;
    cout<<"Age: ";
    cin>>p->age;
}

void printDetails(PERSON p)
{
    cout<<"\nPerson Details are\n";
    cout<<"Name: "<<p.name<<endl;
    
    cout<<"Age: "<<p.age<<endl;
}


int main()
{
    PERSON p1,p2,p[3];

    /*
    cout<<"Size of Person Structure: "<<sizeof(PERSON)<<endl;   
    cout<<"size of unNamed struct: "<<sizeof(b1)<<endl;
    getDetails(&p1);
    getDetails(&p2);
    
    printDetails(p1);
    printDetails(p2);

    b1.id = 101;
    strcpy(b1.title,"C Programming");

    cout<<"\nID: "<<b1.id<<endl;
    cout<<"\nTitle: "<<b1.title<<endl;
    */

    for(int i=0;i<3;i++)
        getDetails(&p[i]);
    
    for(int i=0;i<3;i++)
        printDetails(p[i]);
    
    

    return 0;

}