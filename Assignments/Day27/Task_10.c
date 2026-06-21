#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>    // For fork(), execvp(), and getpid()
#include <sys/wait.h>  // For wait()
#include <sys/types.h> // For pid_t

int main() {
    pid_t pid;

    // Use fork() to create a child process
    // fork() returns the Child's PID to the parent and 0 to the child
    pid = fork();

    if (pid < 0) {
        // Forking failed
        perror("Fork failed");
        exit(1);
    } 
    else if (pid == 0) {
        // --- CHILD PROCESS ---
        printf("Child Process (PID: %d) is starting...\n", getpid());
        
        // Execute an external program (ls command) using execvp()
        // "ls" is the command, "-l" is the argument (long format)
        char *args[] = {"ls", "-l", NULL};
        
        printf("Child executing 'ls -l':\n");
        if (execvp(args[0], args) == -1) {
            perror("Exec failed");
            exit(1);
        }
        
        // This line is NEVER reached if execvp is successful
    } 
    else {
        // --- PARENT PROCESS ---
        int status;
        printf("Parent Process (PID: %d) waiting for Child (PID: %d)...\n", getpid(), pid);
        
        // 3. Wait for the child process to complete
        waitpid(pid, &status, 0);
        
        if (WIFEXITED(status)) {
            printf("\nParent: Child process terminated with status %d.\n", WEXITSTATUS(status));
        }
    }

    return 0;
}
