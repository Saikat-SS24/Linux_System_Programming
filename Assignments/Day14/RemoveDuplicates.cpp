/* Remove duplicate characters from a string without using extra arrays */

#include <iostream>
#include <string>

using namespace std;

void removeDuplicates(string &str) {
    int n = str.length();
    if (n < 2) return; // No duplicates possible in strings shorter than 2

    int index = 0; // Keeps track of the "clean" part of the string

    for (int i = 0; i < n; i++) {
        bool isDuplicate = false;

        // Check if str[i] has appeared in the string before this position
        for (int j = 0; j < i; j++) {
            if (str[i] == str[j]) {
                isDuplicate = true;
                break;
            }
        }

        // If it's not a duplicate, move it to the 'index' position
        if (!isDuplicate) {
            str[index] = str[i];
            index++;
        }
    }

    // Resize the string to remove the leftover characters at the end
    str.erase(index);
}

int main() {
    string s;
    cout << "Enter a string: ";
    getline(cin, s);

    removeDuplicates(s);

    cout << "String after removing duplicates: " << s << endl;

    return 0;
}