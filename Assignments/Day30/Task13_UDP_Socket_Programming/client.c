#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define PORT 8080
#define MAXLINE 1024

int main() {
    int sockfd;
    char buffer[MAXLINE];
    struct sockaddr_in servaddr;

    // Create UDP socket
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("socket creation failed");
        exit(1);
    }

    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT);
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");  // localhost

    const char *msg = "Hello from Client";
    sendto(sockfd, (const char *)msg, strlen(msg), 0,
           (const struct sockaddr *)&servaddr, sizeof(servaddr));
    printf("Message sent to server.\n");

    int n = recvfrom(sockfd, (char *)buffer, MAXLINE,
                     MSG_WAITALL, NULL, NULL);
    buffer[n] = '\0';
    printf("Server reply: %s\n", buffer);

    close(sockfd);
    return 0;
}