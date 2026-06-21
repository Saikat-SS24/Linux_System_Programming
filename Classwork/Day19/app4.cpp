#include <iostream>
#include "Array.h"

using namespace std;

int main(int argc, char *argv[])
{
    int n=0;
    //cout<<"\nHow many value you need: ";
    //cin>>n;
    if(argc != 2)
    {
        cout<<"\nUseage\n./app n\n\n";
        exit(EXIT_FAILURE);
    }
    n = atoi(argv[1]);
    Array arr(n);
    arr.getValue();
    arr.dispArr();
    arr.sort();
    cout<<"\nAfter sorting list is\n";
    arr.dispArr();

    return 0;
}