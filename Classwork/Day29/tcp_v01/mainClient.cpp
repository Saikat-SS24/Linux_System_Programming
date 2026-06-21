#include "common.h"

using namespace std;

int main()
{
    int sfd;
    struct sockaddr_in server_addr;
    socklen_t len;

    len = sizeof(server_addr);

    sfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sfd < 0)
    {
        perror("socket");
        exit(EXIT_FAILURE);
    }
    cout<<"[Client] Socket created successfully\n";

    bzero(&server_addr, sizeof(server_addr));
    
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1"); //server's IP address

    if(connect(sfd,(struct sockaddr *)&server_addr, 
    sizeof(struct sockaddr_in))<0)
    {
        perror("connect");
        exit(EXIT_FAILURE);
    }

    cout<<"[Client] connected successfully!"<<endl;

    char buff[MAX_BUFF];
    memset(&buff,'\0',sizeof(MAX_BUFF));
    read(sfd,buff,MAX_BUFF-1);
    
    cout<<"[Client]\n"<<buff<<endl;
    memset(&buff,'\0',sizeof(MAX_BUFF));
    strcpy(buff,"Hello From Client");
    write(sfd,buff, strlen(buff));
    while(1);
    close(sfd);
}