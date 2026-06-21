#include "common.h"

using namespace std;

int main()
{
    int sfd;
    struct sockaddr_in server_addr;
    socklen_t len;

    len = sizeof(server_addr);

    sfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
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

    
    char buff[MAX_BUFF];
    memset(&buff,'\0',sizeof(MAX_BUFF));
    strcpy(buff,"Hi, From the client");
    int ret = sendto(sfd, buff, strlen(buff)+1,0,
                (struct sockaddr*)&server_addr,len);

    if(ret < 0)
    {
        perror("sendto");
        exit(EXIT_FAILURE);
    }

    cout<<"\n[Client] Sent the message with connection req"<<endl;
    memset(buff,'\0',MAX_BUFF);
    ret = recvfrom(sfd,buff,MAX_BUFF, 0,
                    (struct sockaddr *)&server_addr,&len);
    
    if(ret < 0)
    {
        perror("recvfrom");
        exit(EXIT_FAILURE);
    }

    cout<<"\n[Client] - Received Msg from Server: \n"<<buff<<endl;
    
    close(sfd);
    
    return 0;
}