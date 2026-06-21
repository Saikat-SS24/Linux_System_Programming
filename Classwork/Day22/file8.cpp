/*
weak_ptr -> it is a non-owning smart ptr
used along with shared_ptr to prevent circular dependencies

- does not inc referece count
- prevents circular dep
- need to use lock before we use it

*/
#include <iostream>
#include <memory>

using namespace std;

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
    shared_ptr<Rectangle> ptr1(new Rectangle(3,6));
    weak_ptr<Rectangle> ptr2(ptr1);

    cout<<"\nArea: "<<ptr1->area()<<endl;
    cout<<"\nCount: "<<ptr1.use_count()<<endl;

   // cout<<"\nArea: "<<ptr2.area()<<endl;
   cout<<(*ptr2.lock()).area()<<endl;
   auto temp = ptr2.lock();
   cout<<"\nArea: "<<temp->area()<<endl;
   cout<<"\nCount: "<<ptr2.use_count()<<endl;
    

    return 0;
}