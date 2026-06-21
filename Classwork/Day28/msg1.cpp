#include "common.h"
#define MAX_BUF 1024
#define PERMS 0660

using namespace std;

typedef struct msg_buff
{
    long mtype;
    char mbuff[MAX_BUF];
}MSGBUF;

int main()
{
    int msgqid;
    MSGBUF msg;
    key_t key = ftok("/home/student/25SUB5936_U21", 2026);
    // cout<<"\nKey: "<<key<<endl;

    msgqid = msgget(key, PERMS | IPC_CREAT);
    cout<<"msgid: "<<msgqid<<endl;
    return 0;
}