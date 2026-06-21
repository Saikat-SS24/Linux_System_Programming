/*C Program to Find the Frequency of Every Word in a given String

i/p
"Hi I am a C Programmer, I Love C Coding, I am Passionate towards C Coding"
o/p
I = 3
am = 2
C = 3
Coding = 2*/

#include <stdio.h>
#include <string.h>
#include <ctype.h>

void findFrequency(char str[]) {
    char words[50][50]; // To store up to 50 unique words of length 50
    int count[50] = {0}; // To store the frequency of each word
    int numUnique = 0;

    char *token = strtok(str, " ,.-");

    while (token != NULL) {
        char temp[50];
        for(int i = 0; token[i]; i++) {
            temp[i] = tolower(token[i]);
            if(token[i+1] == '\0') temp[i+1] = '\0';
        }

        int found = 0;
        // Check if the word already exists in our list
        for (int i = 0; i < numUnique; i++) {
            if (strcmp(words[i], temp) == 0) {
                count[i]++;
                found = 1;
                break;
            }
        }

        // If it's a new word, add it to our list
        if (!found) {
            strcpy(words[numUnique], temp);
            count[numUnique] = 1;
            numUnique++;
        }

        token = strtok(NULL, " ,.-");
    }

    // Display the results
    printf("\nWord Frequencies:\n");
    for (int i = 0; i < numUnique; i++) {
        printf("%s = %d\n", words[i], count[i]);
    }
}

int main() {
    char input[200] = "Hii I am a C programmer, I love coding, I am passionate about c coding";
    
    printf("Input: %s\n", input);
    findFrequency(input);

    return 0;
}