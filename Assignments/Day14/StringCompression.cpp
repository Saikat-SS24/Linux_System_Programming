/* Implement basic string compression:
Example: "aaabbc" -> "a3b2c1" */

#include <iostream>
#include <string>

using namespace std;

string compressString(string str) {
    int n = str.length();
    if (n == 0) return "";

    string compressed = "";
    int count = 1;

    for (int i = 0; i < n; i++) {
        // Check if the next character is the same as the current one
        if (i + 1 < n && str[i] == str[i + 1]) {
            count++;
        } 
        // If different character or end of string, append to result
        else {
            compressed += str[i];          // Append character
            compressed += to_string(count); // Append count
            count = 1;                     // Reset count for next character
        }
    }

    // Standard rule: Only return compressed string if it's actually shorter
    return (compressed.length() < n) ? compressed : str;
}

int main() {
    string s;
    cout << "Enter a string to compress: ";
    cin >> s;

    string result = compressString(s);

    cout << "Compressed String: " << result << endl;

    return 0;
}