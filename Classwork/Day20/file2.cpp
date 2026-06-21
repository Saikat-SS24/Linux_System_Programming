/*

Base member      public inherit   protected inherit   private inherit
  ─────────────    ──────────────   ─────────────────   ───────────────
  public:          public           protected           private
  protected:       protected        protected           private
  private:         inaccessible     inaccessible        inaccessible

*/

#include <iostream>
using namespace std;

class A //Base class
{
private:
    int a;
public:
    A() { cout<<"\nDef Cstr of A called\n"; a = 0; }
    A(int a) { cout<<"\nPara Cstr of A called\n"; this->a = a; }
    ~A() {cout<<"\nDestr A called\n";}
    void setA(int a){ this->a = a; }
    int getA() { return a; }
    void dispA() { cout<<"\nA = "<<this->a<<endl; }
};

// : public A  (public) is refered as inheritance mode
class B : public A
{
private:
    int b;
private: // inherite properities of A in this mode
    //int a;
    
public:
    B() { cout<<"\nDef Cstr of B called\n"; b = 0; }
    B(int b) { cout<<"\nPara Cstr of B called\n"; this->b = b; }
    ~B() {cout<<"\nDestr B called\n";}
    void setB(int b){ this->b = b; }
    int getB() { return b; }
    void dispB() { cout<<"\nB = "<<this->b<<endl; 
        a = 30;
        dispA(); 
    }
};


class C: public B
{
public:
    C() { cout<<"\nDef Cnstr of C called\n "; }
    ~C() { cout<<"\nDestr of C called\n "; }
    void dispC()
    {
         a = 40;
         cout<<"\n[inside class C] a = "<<a<<endl;
    }
};


int main()
{
    //A objA(10);
    B objB(20);
    //objB.a = 20;

    //objA.dispA();
    objB.dispB();

    C objC;
    objC.dispC();

    return 0;
}