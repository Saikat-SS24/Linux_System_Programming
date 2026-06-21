#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>

int main() {
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(9090);
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    connect(sock, (sockaddr*)&addr, sizeof(addr));
    write(sock, "10 20", 5);

    char buf[100];
	memset(buf,'\0',100);
    read(sock, buf, sizeof(buf));
    write(1, buf, strlen(buf));
    close(sock);
}
