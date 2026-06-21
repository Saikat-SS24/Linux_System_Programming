/*For a given array of stock prizes, calculate span of each day using stack
*/

#include <iostream>
#include <stack>
#include <vector>

using namespace std;

int main() {
    int n;
    cout << "Enter number of days: ";
    cin >> n;

    int prices[n];
    cout << "Enter stock prices: ";
    for (int i = 0; i < n; i++) cin >> prices[i];

    // Array to store the final span results
    int span[n];
    // Stack to store the indices of the days
    stack<int> s;

    for (int i = 0; i < n; i++) {
        // 1. If today's price is higher than the days on the stack, 
        // those days don't "block" our span anymore. Pop them.
        while (!s.empty() && prices[s.top()] <= prices[i]) {
            s.pop();
        }

        // 2. If stack is empty, today is the highest price seen so far.
        if (s.empty()) {
            span[i] = i + 1;
        } 
        // 3. Otherwise, the span is the distance to the last "stronger" day.
        else {
            span[i] = i - s.top();
        }

        // 4. Push today's index onto the stack
        s.push(i);
    }

    cout << "\nSpan results: ";
    for (int i = 0; i < n; i++) cout << span[i] << " ";
    cout << endl;

    return 0;
}