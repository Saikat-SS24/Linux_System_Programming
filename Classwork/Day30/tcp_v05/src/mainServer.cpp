#include <common.h>
#include <emp.h>

using namespace std;


int server_fd;
void sigHandler(int sigNum)
{
    if(sigNum == SIGINT)
    {
        cout<<"\nClosing Server socket"<<endl;
        close(server_fd);
        exit(EXIT_SUCCESS);
    }
}

int main(int argc, char * argv[])
{
    MySocket S;
    
    signal(SIGINT, sigHandler);
    int sfd = S.conn_s(argv);
    server_fd = sfd;
    while(1) //multi client
    {
        int csfd = S.CAccept();

        if(fork() == 0){
            S.closeSFD();
            Employee e;
            char buff[MAX_BUFF];
            strcpy(buff, "Welcome to the Server");
            write(csfd, buff, strlen(buff));
            memset(buff,'\0',MAX_BUFF);
            cout<<"[Client]["<<ntohs(S.getClientAddr().sin_port)<<"] - ";
            read(csfd,(char *)&e, sizeof(e));
            e.display();
            S.closeCSFD();
            exit(EXIT_SUCCESS);
        }
        close(csfd);
    }

    S.closeSFD();

    return 0;
}