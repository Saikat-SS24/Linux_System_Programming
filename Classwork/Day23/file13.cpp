#include <iostream>
#include <queue>
using namespace std;

int main()
{
    queue<int> q;
    q.push(3);
    q.push(4);
    q.push(5);

    // Accessing the front and back elements
    cout << q.front() << endl;
    cout << q.back();
    
    return 0;
}