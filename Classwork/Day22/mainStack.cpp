#include <iostream>
#include "file11.h"

using namespace std;


int main()
{
    Stack<int> stk_ints;
    
    stk_ints.push(10);
    stk_ints.push(20);
    stk_ints.push(30);
    stk_ints.push(40);
    stk_ints.push(50);
    stk_ints.push(60);
    cout<<"\nPooped out Element: "<<stk_ints.pop()<<endl;
    cout<<"\nPooped out Element: "<<stk_ints.pop()<<endl;
    cout<<"\nPooped out Element: "<<stk_ints.pop()<<endl;
    cout<<"\nPooped out Element: "<<stk_ints.pop()<<endl;
    cout<<"\nPooped out Element: "<<stk_ints.pop()<<endl;
    cout<<"\nPooped out Element: "<<stk_ints.pop()<<endl;

    stk_ints.displayStack();

    Stack<string> stk_str;

    stk_str.push("abc1");
    stk_str.push("abc2");
    stk_str.push("abc3");
    stk_str.push("abc4");
    stk_str.push("abc5");
    
    stk_str.displayStack();

    cout<<"\nPooped out Element: "<<stk_str.pop()<<endl;
    
    



    return 0;
}