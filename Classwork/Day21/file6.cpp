/*

Operator Overloading

obj3 = obj1 + obj2

*/

#include <iostream>

using namespace std;

class Rectangle
{
    int w;
    int h;
public:
    Rectangle(int v1, int v2): w(v1),h(v2){}
    int calcArea() { return w*h; }
    Rectangle operator+(const Rectangle &objR2)
    {
        return Rectangle((this->w + objR2.w),(this->h + objR2.h));
    }

    Rectangle operator++(){
        ++w;
        ++h;
        return *this;
    }

    bool operator>(Rectangle &objr2)
    {
        return (this->calcArea() > objr2.calcArea());
    }

    friend ostream& operator<<(ostream& out, const Rectangle& r);
};

ostream& operator<<(ostream& out, const Rectangle &r)
{
    out<<"\nLength: "<<r.h<<"\nWidth: "<<r.w<<"\nArea: "<<(r.w*r.h);
    return out;
}


int main()
{
    Rectangle r1(3,4);
    Rectangle r2(4,5);

    Rectangle r3 = r1+r2;

    cout<<"Area of r3: "<<r3.calcArea()<<endl;
    // ++r1;
    // cout<<"Area of r1 (after inc): "<<r1.calcArea()<<endl;
    
    Rectangle r4(4,5);
    bool res = r2>r1;
    cout<<"Compare r2 with r1: "<<res<<endl;
    
    res = r2>r4;
    cout<<"Compare r2 with r4: "<<res<<endl;

    cout<<r2<<endl;
    

    return 0;
}