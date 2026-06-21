#include <common.h>
#include <emp.h>

using namespace std;

int main(int argc, char *argv[])
{
    MySocket S;
    Employee e;
    int sfd = S.conn_c(argv);

    /*
    char buff[MAX_BUFF];
    memset(buff, '\0', MAX_BUFF);
    read(sfd, buff, MAX_BUFF);
    cout<<"Client Received: "<<buff<<endl;
    memset(buff, '\0', MAX_BUFF);
    cout<<"\nEnter a msg: ";
    fgets(buff,MAX_BUFF,stdin);
    write(sfd,buff,strlen(buff)+1);
    */

    // e.input();
    // string str1 = e.serialization();
    string str1 = "101|bhimashankar|10002";
    char buff[MAX_BUFF];
    memset(buff, '\0', MAX_BUFF);
    read(sfd, buff, MAX_BUFF);
    cout<<"Client Received: "<<buff<<endl;
    cout<<"serial: "<<str1<<endl;
    write(sfd,str1.c_str(),str1.size());
    S.closeSFD();
    return 0;
}