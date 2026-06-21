#include "common.h"

using namespace std;

int main()
{
    int sfd;
    int csfd;
    struct sockaddr_in server_addr; //server info
    struct sockaddr_in client_addr; //accept system->client's info
    socklen_t len, client_len;

    len = sizeof(server_addr);
    client_len =  sizeof(client_addr);

    sfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if(sfd < 0)
    {
        perror("socket");
        exit(EXIT_FAILURE);
    }
    cout<<"[Server] Socket created successfully\n";

    bzero(&server_addr, sizeof(server_addr));
    
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    if(bind(sfd, (struct sockaddr *)&server_addr,
    sizeof(server_addr))<0)
    {
        perror("bind");
        exit(EXIT_FAILURE);
    }

    cout<<"[Server] bind done!"<<endl;

    char buff[MAX_BUFF];
    int ret = recvfrom(sfd,buff,MAX_BUFF, 0,
                        (struct sockaddr *)&client_addr, &client_len);
        
    if(ret < 0)
    {
        perror("recvfrom");
        exit(EXIT_FAILURE);
    }    
    cout<<"[+Server]: Client Message: "<<buff<<endl;
    //memset(&buff,'\0',MAX_BUFF);
    char temp[MAX_BUFF];
    strcpy(temp,"[Server] - ");
    strcat(temp,buff);
    memset(&buff,'\0',MAX_BUFF);
    ret = sendto(sfd,temp,strlen(temp), 0, 
                (struct sockaddr *)&client_addr,client_len);
    
    if(ret < 0)
    {
        perror("sendto");
        exit(EXIT_FAILURE);
    }
    cout<<"[+Server] Sent message to the client"<<endl;

    close(sfd);

    return 0;
}