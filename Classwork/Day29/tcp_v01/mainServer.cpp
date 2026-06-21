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

    sfd = socket(AF_INET, SOCK_STREAM, 0);
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

    if(listen(sfd,5) == 0)
        cout<<"[Server] Liesting...."<<endl;
    else
        cout<<"[Server] Error in Listening..."<<endl;
    
    while(1){
        csfd = accept(sfd, (struct sockaddr *)&client_addr, &client_len);
        
        if(csfd < 0)
        {
            perror("accept");
            exit(EXIT_FAILURE);
        }

        cout<<"[Server] Accepted Client Successfully!"<<endl;
        cout<<"[Server] Client IP: "<<inet_ntoa(client_addr.sin_addr)<<endl;
        cout<<"[Server] Client PORTNO: "<<ntohs(client_addr.sin_port)<<endl;
        
        char buff[MAX_BUFF];
        memset(&buff,'\0',MAX_BUFF);
        strcpy(buff, "\n======Welcome to the Wipro Server=======\n");
        write(csfd,buff,strlen(buff));
        memset(&buff,'\0',MAX_BUFF);
        read(csfd,buff,MAX_BUFF-1);
        cout<<"[Server][Client] - msg - "<<buff<<endl;

    }

    close(sfd);
}