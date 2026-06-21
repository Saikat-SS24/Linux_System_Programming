#include <iostream>
#include <stack>
using namespace std;
int main(){
    stack<int> st;
    st.push(10);
    st.push(7);
    st.push(11);
    st.push(5);
    st.push(20);
    
    // Accessing top element
    //cout << "Top element: " << st.top() << endl;
    
    // Popping an element
    //st.pop();
    //cout << "Top element after pop: " << st.top() << endl;

    stack<int> temp(st);

    for(;!temp.empty();)
    {
        cout<<temp.top()<<endl;
        temp.pop();
    }
    return 0;
}