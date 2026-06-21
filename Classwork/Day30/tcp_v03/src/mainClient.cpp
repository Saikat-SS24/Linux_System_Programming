#include <common.h>

using namespace std;

int main(int argc, char *argv[])
{
    MySocket S;
    int sfd = S.conn_c(argv);

    char buff[MAX_BUFF];
    memset(buff, '\0', MAX_BUFF);
    read(sfd, buff, MAX_BUFF);
    cout<<"Client Received: "<<buff<<endl;
    memset(buff, '\0', MAX_BUFF);
    cout<<"\nEnter a msg: ";
    fgets(buff,MAX_BUFF,stdin);
    write(sfd,buff,strlen(buff)+1);
    S.closeSFD();
    return 0;
}