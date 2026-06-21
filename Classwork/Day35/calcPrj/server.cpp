#include <iostream>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    int server_fd, client_fd;
    struct sockaddr_in addr;
    char buffer[1024];

    server_fd = socket(AF_INET, SOCK_STREAM, 0);

    addr.sin_family = AF_INET;
    addr.sin_port = htons(9090);
    addr.sin_addr.s_addr = INADDR_ANY;

    bind(server_fd, (struct sockaddr*)&addr, sizeof(addr));
    listen(server_fd, 1);   // ⚠️ only 1 connection

    std::cout << "Calculator server running...\n";

    while (1) {
        client_fd = accept(server_fd, NULL, NULL);
        memset(buffer, 0, sizeof(buffer));

        read(client_fd, buffer, sizeof(buffer));

        int a, b;
        sscanf(buffer, "%d %d", &a, &b);

        int result = a + b;
        sprintf(buffer, "Result: %d\n", result);

        write(client_fd, buffer, strlen(buffer));
        close(client_fd);

        sleep(2); // ⚠️ simulate slow processing
    }
}