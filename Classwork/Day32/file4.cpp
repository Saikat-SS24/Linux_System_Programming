#include <stdio.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <string.h>
#define SHM_NAME "/posix_shm"

int main() {
    int fd = shm_open(SHM_NAME, O_RDONLY,0666);
    //ftruncate(fd, 1024);
    char *ptr = (char *) mmap(NULL, 1024, PROT_READ, MAP_SHARED, fd, 0);
    printf("Data received: %s\n", ptr);
    munmap(ptr, 1024);
    close(fd);

    return 0;
}