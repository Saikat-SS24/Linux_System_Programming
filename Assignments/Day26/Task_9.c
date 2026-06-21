#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>   // For directory stream operations
#include <unistd.h>   // For chdir()
#include <sys/stat.h> // For mkdir()
#include <errno.h>    // For error handling

int main() {
    struct dirent *entry;
    DIR *dp;

    //  List all files and directories in the current working directory
    printf("Listing contents of current directory:\n");
    dp = opendir(".");
    if (dp == NULL) {
        perror("opendir");
        return 1;
    }

    while ((entry = readdir(dp)) != NULL) {
        printf("  %s\n", entry->d_name);
    }
    closedir(dp);

    // 2. Change the current working directory to "/tmp"
    printf("\nChanging directory to /tmp...\n");
    if (chdir("/tmp") != 0) {
        perror("chdir");
        return 1;
    }

    // 3. Create a new directory named "testdir" with permissions 755
    // 0755: Owner (Read/Write/Execute), Group (Read/Execute), Others (Read/Execute)
    printf("Creating 'testdir' with 755 permissions...\n");
    if (mkdir("testdir", 0755) != 0) {
        if (errno == EEXIST) {
            printf("Note: 'testdir' already exists.\n");
        } else {
            perror("mkdir");
            return 1;
        }
    } else {
        printf("Successfully created /tmp/testdir\n");
    }

    return 0;
}