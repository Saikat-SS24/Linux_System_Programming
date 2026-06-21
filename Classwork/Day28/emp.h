#pragma once
#include "common.h"

using namespace std;

class Employee
{
    int id;
    char name[20];
public:
    Employee(const int i, const char *n){
        this->id = i;
        strcpy(this->name,n);
    }

    void setData(const int i, const char *n)
    {
        this->id = i;
        strcpy(this->name,n);
    }

    void display(){
        cout<<"\nID: "<<id<<endl;
        cout<<"\nName: "<<name<<endl;
    }
};

