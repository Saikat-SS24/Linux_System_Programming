/* Check whether two strings are anagrams of each other */

#include <iostream>
#include <string>
#include <algorithm> // Required for sort()

using namespace std;

bool areAnagrams(string s1, string s2) {
    // 1. If lengths are different, they aren't anagrams
    if (s1.length() != s2.length()) {
        return false;
    }

    // 2. Sort both strings
    sort(s1.begin(), s1.end());
    sort(s2.begin(), s2.end());

    // 3. Compare sorted strings
    for (int i = 0; i < s1.length(); i++) {
        if (s1[i] != s2[i]) {
            return false;
        }
    }

    return true;
}

int main() {
    string str1, str2;

    cout << "Enter first string: ";
    cin >> str1;
    cout << "Enter second string: ";
    cin >> str2;

    if (areAnagrams(str1, str2)) {
        cout << "The strings are anagrams!" << endl;
    } else {
        cout << "The strings are NOT anagrams." << endl;
    }

    return 0;
}