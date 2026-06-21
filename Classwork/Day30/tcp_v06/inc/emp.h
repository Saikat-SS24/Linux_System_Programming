#pragma once
#include <iostream>
#include <sstream>
#include <cstring>
#include <string>

using namespace std;

class Employee
{
private:
    int empId;
    char empName[30];
    double empSalary;
public:
    Employee() {
        empId = 0;
        strcpy(empName,"UnKnown");
        empSalary = 0.0;
    }
    Employee(int id, char *n, double s)
    : empId(id), empSalary(s){ strcpy(empName,n);}

    int getId() const { return empId; }
    string getName() const { return empName;}
    double getSal() const { return empSalary; }

    void input(){
        cout<<"\nEnter Employee Details\n";
        cout<<"\nID: ";cin>>empId;
        cout<<"\nName: ";cin>>empName;
        cout<<"\nSalary: ";cin>>empSalary;
    }

    string serialization()
    {
        ostringstream oss;
        oss<< empId<<"|"
           << empName<<"|"
           << empSalary;

        return oss.str();
    }


    void deserialization(string data)
    {
        istringstream iss(data);
        string temp;
        getline(iss,temp,'|');
        empId = stoi(temp);
        getline(iss,temp,'|');
        strcpy(empName,temp.c_str());
        getline(iss, temp, '|');
        empSalary = stof(temp);
    }

    void display() const{
        cout<<"\nEmployee Details are\n";
        cout<<"ID: "<<empId<<endl;
        cout<<"Name: "<<empName<<endl;
        cout<<"Salary: "<<empSalary<<endl;
    }
};