/*

r_datatype fName(parameters_list)
{
    //function body
    return value;
}


types,

1. function with args and return datatype
2. function with no args and return datatype
3. function with no args and no return type


1. prototype of the funtion -> declaring a function
2. defination of the function -> defining the body of the function
3. calling the function

*/

#include <iostream>

using namespace std;


//1. functions with return type and parameters
int addition(int,int); //prototyping of function
                       // signature of function
//2. function with RT and no args
int func2(void);

int retValue=0;

int main()
{
    int temp=0;
    
    retValue = addition(10,20); //calling the function 
                                //executing the function

    cout<<"Sum="<<retValue<<endl;

    cout<<func2()<<endl;

    return 0;
}

//defining the function
int addition(int v1, int v2) 
{
    //local variables
    int sum = 0;
    sum = v1 + v2;

    return sum;
}

int func2(void)
{
    int v;
    v = retValue * 20;
    return v;
}