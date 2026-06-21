/*

syntax:

struct tag_name
{
    //properties of the structure
    // related variables of the st
};

//defining the structure
struct student
{
    char regNo[20];
    char name[100];
    char gender;
    char address[200];
    unsinged long int phone;
    float cgpa;
};

// variables of the student
//declraing the variable of the structure
struct student s1,s2,s3;

//use the varibales and as well access the members of the structure
s1=value

struct student s={"25sub5555", "amit", 'M',"Bangalore",88889999,8.5};

members can be access in 2 ways
1. using dot ( . ) operator
2. using arrow ( -> ) operator

stVar.memName

strcpy(s1.regNo,"25SUB5936");
strcpy(s1.name, "amit kumar");
s1.gender = 'm';
s1.phno = 9998888;


arrow operator is accessed if the variable of the struct is declared as ptr to 
the st.

struct student *ptr;
ptr->phone = 999888;

structure padding

*/

#include <iostream>
#include <cstring>

using namespace std;

struct Book
{
    int id;
    int pages;
    float price;
    char title[20];
    char author[20];
}b3,b4, b[10];


//b3,b4 are global variables
//b[10] array of 10 books

int main()
{
    struct Book b1 = {101,200,200.5,"CPP Programming", "Strustrup"};
    struct Book b2, _b[3];

    //b1 and b2 are local to the main
    // _b[3] are array of 3 books

    cout<<"ID: "<<b1.id<<endl;
    cout<<"Title: "<<b1.title<<endl;
    cout<<"Author: "<<b1.author<<endl;
    cout<<"Pages: "<<b1.pages<<endl;
    cout<<"Price: "<<b1.price<<endl;

    cout<<endl;

    cout<<"\nEnter the b2 values: "<<endl;
    cout<<"\nTitle: ";
    fgets(b2.title,19,stdin);
    b2.title[strlen(b2.title)-1] = '\0';
    cout<<"ID: ";
    cin>>b2.id;
    //fflush(stdin);
    char ch;
    scanf("%c",&ch);
    cout<<"Author: ";
    fgets(b2.author,19,stdin);
    b2.author[strlen(b2.author)-1] = '\0';
    cout<<"No of Pages: ";
    cin>>b2.pages;
    cout<<"Price: ";
    cin>>b2.price;




    cout<<"ID: "<<b2.id<<endl;
    cout<<"Title: "<<b2.title<<endl;
    cout<<"Author: "<<b2.author<<endl;
    cout<<"Pages: "<<b2.pages<<endl;
    cout<<"Price: "<<b2.price<<endl;

    cout<<endl;

    for(int i=0;i<20;i++)
        cout<<b2.title[i]<<"\t ascii value="<<(int)b2.title[i]<<endl;
    cout<<endl;
    
    
    for(int i=0;i<20;i++)
        cout<<b2.author[i]<<"\t ascii value="<<(int)b2.author[i]<<endl;
    cout<<endl;
    
    return 0;

}