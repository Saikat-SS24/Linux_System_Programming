/*Use queue to generate binary numbers from 1 to N

Example: 1, 10, 11, 100, 101
*/

#include <iostream>
#include <queue>
#include <string>

using namespace std;

void generateBinary(int n) {
    // Create a queue of strings to store binary numbers
    queue<string> q;

    // 1. Enqueue the first binary number
    q.push("1");

    cout << "Binary numbers from 1 to " << n << ":" << endl;

    // 2. Run a loop n times
    for (int i = 1; i <= n; i++) {
        // Get the front element and print it
        string current = q.front();
        q.pop();
        cout << current << " ";

        // 3. Generate the next two numbers by appending '0' and '1'
        // and push them back into the queue
        string s1 = current + "0";
        string s2 = current + "1";

        q.push(s1);
        q.push(s2);
    }
    cout << endl;
}

int main() {
    int n;
    cout << "Enter the value of N: ";
    cin >> n;

    if (n <= 0) {
        cout << "Please enter a positive integer." << endl;
    } else {
        generateBinary(n);
    }

    return 0;
}