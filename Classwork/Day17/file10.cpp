#include <iostream>
#include <cstdlib>

using namespace std;

int global_var = 100;

const int global_const = 200;

//static variable
static int static_global = 300;


int main()
{
    int local_var = 10;
    const int local_const = 20;

    static int static_local = 30;

    //heap memory
    int *heap_var = (int *)malloc(sizeof(int));
    *heap_var = 40;

    cout<<"[Inside Main]"<<endl;

    free(heap_var);

    return 0;
}