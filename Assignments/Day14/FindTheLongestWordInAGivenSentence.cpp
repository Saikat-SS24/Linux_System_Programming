/* Find the longest word in a given sentence */

#include <iostream>
#include <string>

using namespace std;

string findLongestWord(string sentence) {
    string longest = "";
    string currentWord = "";
    
    // Add a space at the end to ensure the last word is processed
    sentence += " "; 

    for (int i = 0; i < sentence.length(); i++) {
        // If the character is not a space, build the current word
        if (sentence[i] != ' ') {
            currentWord += sentence[i];
        } 
        // If we hit a space, the current word is finished
        else {
            if (currentWord.length() > longest.length()) {
                longest = currentWord;
            }
            currentWord = ""; // Reset for the next word
        }
    }
    
    return longest;
}

int main() {
    string str;
    cout << "Enter a sentence: ";
    getline(cin, str); // Use getline to include spaces

    string result = findLongestWord(str);

    cout << "The longest word is: " << result << endl;
    cout << "Length: " << result.length() << endl;

    return 0;
}