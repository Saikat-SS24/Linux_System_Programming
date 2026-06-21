#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <iostream>
#include <cstring>
#include <cerrno>
#include <cstdlib>

// ─── Helper: decode and print exit status ────────────────────────────
void reportChildStatus(pid_t pid, int status) {
    std::cout << "[Parent] Child PID " << pid;
    if (WIFEXITED(status)) {
        std::cout << " exited normally with code "
                  << WEXITSTATUS(status) << "\n";
    } else if (WIFSIGNALED(status)) {
        std::cout << " killed by signal "
                  << WTERMSIG(status)
                  << " (" << strsignal(WTERMSIG(status)) << ")\n";
    } else if (WIFSTOPPED(status)) {
        std::cout << " stopped by signal "
                  << WSTOPSIG(status) << "\n";
    }
}

int main() {
    std::cout << "╔══════════════════════════════════════════╗\n";
    std::cout << "║   Process Management — Complete Demo     ║\n";
    std::cout << "╚══════════════════════════════════════════╝\n\n";

    // ── 1. Basic fork() ───────────────────────────────────────────────
    std::cout << "─── 1. Basic fork() ───\n";
    std::cout << "[Main] PID=" << getpid()
              << " PPID=" << getppid() << "\n";

    pid_t pid = fork();

    if (pid == -1) {
        perror("fork"); return 1;

    } else if (pid == 0) {
        // ── CHILD process ────────────────────────────────────────────
        std::cout << "[Child]  PID=" << getpid()
                  << " PPID=" << getppid()
                  << " (parent's PID)\n";

        // Child does some work
        sleep(1);
        std::cout << "[Child]  Work done. Exiting with code 42.\n";
        while(1);
        exit(42);

    } else {
        // ── PARENT process ────────────────────────────────────────────
        std::cout << "[Parent] PID=" << getpid()
                  << " forked child PID=" << pid << "\n";

        int status;
        waitpid(pid, &status, 0);   // wait for specific child
        reportChildStatus(pid, status);
    }

   

    std::cout << "\nAll done.\n";
    return 0;
}