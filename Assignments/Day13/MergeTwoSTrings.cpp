/*alternativel merge two strings

i/p
Bhima
ABCDEOLM
o/p
BAhBiCmDaEOLM
*/

#include <iostream>
#include <string>
using namespace std;

int main() {
    string s1, s2, result = "";
    
    cout << "Enter first string: ";
    cin >> s1;
    cout << "Enter second string: ";
    cin >> s2;

    int i = 0, j = 0;

    // Keep looping while there are characters in either string
    while (i < s1.length() || j < s2.length()) {
        
        // If s1 still has characters, add one
        if (i < s1.length()) {
            result += s1[i];
            i++;
        }

        // If s2 still has characters, add one
        if (j < s2.length()) {
            result += s2[j];
            j++;
        }
    }

    cout << "Output: " << result << endl;

    return 0;
}