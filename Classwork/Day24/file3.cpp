#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

bool Comp (const char n1[], const char n2[])
{
    return (strcmp(n1,n2)<0);
}

int main()
{
    char *names[20]={"abc","def","bcd","efg","ade"};

    //for(int i=0;i<4;i++)
    sort(names,names+5, Comp);

    for(int i=0;i<5;i++)
        cout<<names[i]<<endl;
    

    return 0;
}