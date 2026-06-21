/*
multi threading

using posix thread
and using c++ thread

*/

#include <iostream>

using namespace std;

typedef unsigned long long ULL;

void findODD(ULL,ULL);
void findEven(ULL,ULL);

ULL sumODD = 0;
ULL sumEven = 0;



int main()
{
   ULL start=0, end=19000000000;
   
   //findEven(start,end);
   findODD(start,end);

   cout<<sumODD<<endl;
   //cout<<sumEven<<endl;

   return 0;
}


void findODD(ULL start, ULL end)
{
    ULL i;
    for(i=start;i<end;i++)
    {
        if(i%2 != 0)
        {
            sumODD += i;
        }
    }  
}


void findEven(ULL start, ULL end)
{
    ULL i;
    for(i=start;i<end;i++)
    {
        if(i%2 == 0)
        {
            sumEven += i;
        }
    }  
}