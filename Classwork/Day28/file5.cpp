#include "common.h"

using namespace std;

int main()
{

    std::cout << "\n─── 5. Named pipe (FIFO) ───\n";
    const char* fifoPath = "demo_fifo";

    // Create the FIFO (like a special file on disk)
    unlink(fifoPath);                       // remove if exists
    if (mkfifo(fifoPath, 0666) == -1) {
        perror("mkfifo"); return 1;
    }
    std::cout << "Created FIFO at: " << fifoPath << "\n";

    pid_t fifoPid = fork();
    if (fifoPid == 0) {
        // CHILD (reader): opens FIFO for reading
        // open() BLOCKS until someone opens the write end
        std::cout << "[FIFO Reader] Opening FIFO...\n";
        int rfd = open(fifoPath, O_RDONLY);
        char rBuf[256] = {0};
        ssize_t n = read(rfd, rBuf, sizeof(rBuf) - 1);
        std::cout << "[FIFO Reader] Read " << n
                  << " bytes: \"" << rBuf << "\"\n";
        close(rfd);
        exit(0);

    } else {
        // PARENT (writer): opens FIFO for writing
        // open() BLOCKS until someone opens the read end
        std::cout << "[FIFO Writer] Opening FIFO...\n";
        int wfd = open(fifoPath, O_WRONLY);
        const char* data = "FIFO message from writer process!";
        write(wfd, data, strlen(data));
        //std::cout << "[FIFO Writer] Wrote: \"" << data << "\"\n";
        close(wfd);
        waitpid(fifoPid, nullptr, 0);
    }

    unlink(fifoPath);
    std::cout << "FIFO demo complete.\n";
    return 0;

}