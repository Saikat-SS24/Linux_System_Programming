#include <iostream>
#include <memory>

using namespace std;


/*
unique_ptr
stores one ptr only at one time.
we can't copy uptrs, we can only transfer the ownership 
move() 
*/

class Rectangle
{
private:
    int l,b;
public:
    Rectangle(int l, int b){
        this->l = l;
        this->b = b;
    }
    int area() { return l*b; }
};

int main()
{
    unique_ptr<Rectangle> ptr1(new Rectangle(3,4));
    cout<<ptr1->area()<<endl;

    unique_ptr<Rectangle> ptr2;

    ptr2 = move(ptr1); //ownership transfer

    cout<<ptr2->area()<<endl;
    //cout<<ptr1->area()<<endl;


    return 0;
}