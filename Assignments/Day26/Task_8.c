#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *fptr;
    char buffer[100];

    // "w+" allows reading and writing. It creates the file if it's missing.
    fptr = fopen("data.txt", "w+");

    if (fptr == NULL) {
        printf("Error opening/creating file!\n");
        return 1;
    }

    // 2. Writing the string to the file
    fprintf(fptr, "Hello, File Handling in C!");
    printf("Successfully written to the file.\n");

    // 3. Moving the file pointer to the beginning
    // rewind(fptr) is equivalent to fseek(fptr, 0, SEEK_SET)
    rewind(fptr);

    // 4. Read the contents back
    // fgets reads up to the newline or 99 characters
    if (fgets(buffer, 100, fptr) != NULL) {
        // 5. Print the contents to the console
        printf("Contents of 'data.txt': %s\n", buffer);
    }

    // 6. Close the file
    fclose(fptr);

    return 0;
}
