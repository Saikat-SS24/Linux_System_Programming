#include <iostream>
#include <memory>

using namespace std;

/*
shared_ptr
allow multiple ownership for the same address space/object.
it will also use ref count to manage memory

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
    shared_ptr<Rectangle> ptr1(new Rectangle(3,5));
    cout<<ptr1->area()<<endl;
    shared_ptr<Rectangle> ptr2 = ptr1;
    cout<<ptr2->area()<<endl;
    cout<<ptr1->area()<<endl;
    shared_ptr<Rectangle> ptr3 = ptr2;
    cout<<ptr1.use_count()<<endl;

    return 0;
}