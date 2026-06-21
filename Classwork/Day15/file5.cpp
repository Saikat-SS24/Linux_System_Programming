#include <iostream>
using namespace std;


typedef union book
{
    char title[30];
    int id;
    
}BOOK;


int main()
{
    BOOK b1;
    cout<<"Size of book: "<<sizeof(BOOK)<<endl;
    b1.id = 101;
    cout<<b1.id<<endl;
    sprintf(b1.title,"%s","C++ Programming");
    cout<<b1.title<<endl;
    cout<<b1.id<<endl;
    
    
    return 0 ;

}