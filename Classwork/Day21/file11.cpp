//binary io

#include <iostream>
#include <fstream>

using namespace std;

class Student{
    int id;
    string name;
    float marks;

public:
    Student () { id=0;name="";marks=0.0f;}
    Student(int id, string name, float marks)
    {
        this->id = id;
        this->name = name;
        this->marks = marks;
    }

    void dispStudent()
    {
        cout<<"\nStudent Details\n";
        cout<<"Name: "<<name<<endl;
        cout<<"ID: "<<id<<endl;
        cout<<"Marks: "<<marks<<endl;
    }

    friend ostream& operator<<(ostream& out, const Student& s);
    friend istream& operator>>(istream& in, Student& s);
};

ostream& operator<<(ostream& out, const Student &s)
{
    out<<s.id<<"\t"<<s.name<<"\t"<<s.marks;
    return out;
}

istream& operator>>(istream& in, Student &s)
{
    in>>s.id>>s.name>>s.marks;
    return in;
}



int main()
{
    Student s1(101,"abc1",65.5);
    Student s2(102,"abc2",75.5);
    Student s3(103,"abc3",85.5);
    fstream fs;
    fs.open("stdRecsB1.bin",ios::out | ios::binary);
    
    fs.write((char *)&s1,sizeof(s1));
    fs.write((char *)&s2,sizeof(s2));
    fs.write((char *)&s3,sizeof(s3));
    
    fs.close();
    
    fs.open("stdRecsB1.bin",ios::in | ios::out | ios::binary );
    if(!fs)
    {
        cerr<<"\nUnable to open the file"<<endl;
        exit(EXIT_FAILURE);
    }

    fs.seekp(2*sizeof(Student));// move the no of bytes
    Student s(104,"xyz",35.5);
    fs.write((char *)&s, sizeof(s));
    fs.close();

    fs.open("stdRecsB1.bin", ios::in|ios::binary);
    Student d;
    while(fs.read((char *)&d,sizeof(d)))
        d.dispStudent();
    
    fs.close();
    return 0;
    
}