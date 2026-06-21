#pragma once
#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <signal.h>

#define MAX_BUFF 1024
#define PORT 4005

typedef struct sockaddr_in SA_IN;


class MySocket
{
private:
    int sfd;
    int csfd;
    int portNo;
    char ipaddr[30];
    struct sockaddr_in server_addr;
    struct sockaddr_in client_addr;
    socklen_t len, client_len;

public:
    MySocket();
    ~MySocket();

    int conn_s(char **); //server syscalls for socket creation is done
    int conn_c(char **); //client syscalls for socket creation is done

    int CAccept();

    SA_IN getServerAddr();
    SA_IN getClientAddr();
    socklen_t getLengthAddr();
    int readFromS(char *);
    int writeToS(char *);
    int readFromC(char *);
    int writeToC(char *);
    int getClientSFD();

    void closeSFD();
    void closeCSFD();

};