#include <common.h>

using namespace std;


MySocket::MySocket()
{
    sfd = 0;
    csfd = 0;
    portNo = 0;
    strcpy(ipaddr, "0.0.0.0");
}

MySocket::~MySocket()
{

}

SA_IN MySocket::getServerAddr()
{
    return server_addr;
}

SA_IN MySocket::getClientAddr()
{
    return client_addr;
}

socklen_t MySocket::getLengthAddr()
{
    return len;
}

int MySocket::getClientSFD()
{
    return csfd;
}

int MySocket::conn_s(char **argv)
{
    len = sizeof(server_addr);
    client_len = sizeof(client_addr);

    sfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sfd < 0)
    {
        perror("socket");
        exit(EXIT_FAILURE);
    }
    cout<<"[Server] Socket created successfully\n";

    bzero(&server_addr, sizeof(server_addr));
    
    portNo = atoi(argv[2]);
    strcpy(ipaddr,argv[1]);

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(portNo);
    server_addr.sin_addr.s_addr = inet_addr(ipaddr);

    if(bind(sfd, (struct sockaddr *)&server_addr,
    sizeof(server_addr))<0)
    {
        perror("bind");
        exit(EXIT_FAILURE);
    }

    cout<<"[Server] bind done!"<<endl;

    if(listen(sfd,5) == 0)
        cout<<"[Server] Liesting...."<<endl;
    else
        cout<<"[Server] Error in Listening..."<<endl;

    return sfd;
}


int MySocket::CAccept()
{
    int csfd = accept(sfd, (struct sockaddr *)&client_addr, &client_len);
        
    if(csfd < 0)
    {
        perror("accept");
        exit(EXIT_FAILURE);
    }

    cout<<"[Server] Accepted Client Successfully!"<<endl;
    cout<<"[Server] Client IP: "<<inet_ntoa(client_addr.sin_addr)<<endl;
    cout<<"[Server] Client PORTNO: "<<ntohs(client_addr.sin_port)<<endl;
        
    return csfd;
}


int MySocket::conn_c(char **argv)
{
    len = sizeof(server_addr);
    client_len = sizeof(client_addr);
    sfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sfd < 0)
    {
        perror("socket");
        exit(EXIT_FAILURE);
    }
    cout<<"[Client] Socket created successfully\n";

    bzero(&server_addr, sizeof(server_addr));

    portNo = atoi(argv[2]);
    strcpy(ipaddr, argv[1]); 
    
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(portNo);
    server_addr.sin_addr.s_addr = inet_addr(ipaddr); //server's IP address

    if(connect(sfd,(struct sockaddr *)&server_addr, 
    sizeof(struct sockaddr_in))<0)
    {
        perror("connect");
        exit(EXIT_FAILURE);
    }

    cout<<"[Client] connected successfully!"<<endl;

    return sfd;
}


void MySocket::closeSFD()
{
    close(sfd);
}

void MySocket::closeCSFD()
{
    close(csfd);
}