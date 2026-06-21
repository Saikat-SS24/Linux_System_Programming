#pragma once
#include <iostream>
using namespace std;

class Array
{
private:
    int *ptr = nullptr;
    int Cap;

private:
    void swapElem(int &, int &); //abstraction
    void bubbleSort();
    

public:
    Array(); //default constr
    Array(int);
    ~Array();
public:
    void getValue();

    void dispArr();

    void sort();
    
};
