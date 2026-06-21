#include <common.h>

using namespace std;

int main(int argc, char * argv[])
{
    MySocket S;
    int sfd = S.conn_s(argv);
    while(1) //multi client
    {
        int csfd = S.CAccept();

        char buff[MAX_BUFF];
        strcpy(buff, "Welcome to the Server");
        write(csfd, buff, strlen(buff));
        memset(buff,'\0',MAX_BUFF);
        read(csfd, buff, MAX_BUFF);
        cout<<"[Client]["<<ntohs(S.getClientAddr().sin_port)<<"] - ";
        cout<<buff<<endl;
        S.closeCSFD();
    }

    S.closeSFD();

    return 0;
}