/*
(a < b) => relational expr 
(b > c)

( a > b ) && ( a > c) => a is biggest

a=5 => dec value

res = a & a;

0000 0000 0000 0101
0000 0000 0000 0000
===================
0000 0000 0000 0000


0000 0000 0000 0101
0000 0000 0000 0101
===================
0000 0000 0000 0101 =>5


res = a | 2;

0000 0000 0000 0101
0000 0000 0000 0010
===================
0000 0000 0000 0111 =>7

<<, >>

res = a << 1;
0000 0000 0000 0101 = 5
0000 0000 0000 1010 = 10


res = a >> 1;
0000 0000 0000 0101 = 5
0000 0000 0000 0010 = 2 

res = a << 2;
0000 0000 0000 0101 => 5
0000 0000 0001 0100 => 20

res = a >> 2;
0000 0000 0000 0101 => 5
0000 0000 0000 0001 => 1

a += 2; => a = a+2

a++; => a = a+1

post inc op++ 
pre inc  ++op







int a=10;   a=10;
int b=++a;  a=11, b=11
int c=b++;  c=11, b=12

c++; c=12
printf("\n%d %d %d\n",++a,b++,++c);  12, 12, 13 
printf("\n%d %d %d\n",a,b,c);  12, 13, 13 


12 12 13
12 12 12




res = ~a;
1111 1111 1111 1010 
*/

#include <iostream>

using namespace std;
/*
int main()
{
    int a=5;
    int res = a<<1;
    cout<<res<<endl;
    cout<<(a>>1)<<endl;

    return 0;
}
*/
/*
int main()
{

    int a=10; //  a=10;
    int b=++a; // a=11, b=11
    int c=b++; // c=11, b=12

    c++;// c=12
    printf("\n%d %d %d\n",++a,b++,++c); // 12, 12, 13 
    printf("\n%d %d %d\n",a,b,c); // 12, 13, 13 

    return 0;
}

*/

int main()
{
    int a=100,b=201,c=301;

    int res=0;

    //res = (a>b)?(110):(201);


    res = (a>b)?((a>c)?(a):(c)):((b>c)?(b):(c));

    cout<<"res="<<res<<endl;

    return 0;
}