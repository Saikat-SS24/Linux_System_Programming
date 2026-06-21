/*C Program to Remove all Characters in Second String which are present in First String
i/p
Bhima shankar is a C programme
o/p
Bhima snkr is a C programme*/

#include <stdio.h>
#include <string.h>

int main() {
    char first[100], second[100];
    int charExists[256] = {0}; // Array to track all ASCII characters
    int i, j = 0;

    printf("Enter first string (characters to remove): ");
    gets(first); // Note: fgets is safer, but gets is used for basic logic

    printf("Enter second string (the target): ");
    gets(second);

    // 1. Mark all characters present in the first string
    for (i = 0; first[i] != '\0'; i++) {
        // Use the character's ASCII value as an index
        charExists[(unsigned char)first[i]] = 1;
    }

    // 2. Filter the second string
    char result[100];
    for (i = 0; second[i] != '\0'; i++) {
        // Only keep the character if it was NOT in the first string
        if (charExists[(unsigned char)second[i]] == 0) {
            result[j] = second[i];
            j++;
        }
    }
    result[j] = '\0'; // Don't forget the null terminator!

    printf("\nOutput: %s\n", result);

    return 0;
}