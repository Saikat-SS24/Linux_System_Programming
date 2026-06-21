#include <stdio.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <string.h>
#define SHM_NAME "/posix_shm"

int main() {
    int fd = shm_open(SHM_NAME, O_CREAT | O_RDWR, 0666);
    ftruncate(fd, 1024);
    char *ptr = (char *) mmap(NULL, 1024, PROT_WRITE, MAP_SHARED, fd, 0);
    strcpy(ptr, "POSIX Shared Memory Example");
    printf("Data written: %s\n", ptr);
    munmap(ptr, 1024);
    close(fd);

    return 0;
}