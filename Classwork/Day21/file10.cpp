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

    ofstream fout("stdRecsB.db",ios::binary);
    fout.write((char *)&s1,sizeof(s1));
    fout.write((char *)&s2,sizeof(s2));
    fout.write((char *)&s3,sizeof(s3));
    
    fout.close();
    
    ifstream fin("stdRecsB.db",ios::binary);
    if(!fin)
    {
        cerr<<"\nUnable to open the file"<<endl;
        exit(EXIT_FAILURE);
    }

    Student s;
    while(fin.read((char *)&s,sizeof(s)))
        s.dispStudent();

    fin.close();

    return 0;
    
}