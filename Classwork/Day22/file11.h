/*
class templates

template <typename T>
class className
{
    private:
        T v1;
    public:
        T func(T v2);
};



template <typename T1, typename T2>
class className
{
    private:
        T1 v1;
        T2 v2;
    public:
        T2 func(T1, T2);
};
generic class

*/

#pragma once
#include <iostream>
#include <cstring>
#include <string>

#define SIZE 5


using namespace std;


template <typename T>
class Stack
{
public:
    Stack();
    void push(T);
    T pop();

    T topElement();

    bool isFull();

    bool isEmpty();

private:
    int top;
    T st[SIZE];
};



