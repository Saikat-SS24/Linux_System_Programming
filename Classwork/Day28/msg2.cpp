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
    if(msgqid < 0)
    {
        perror("msgget");
        exit(EXIT_FAILURE);
    }

    int bytes=0;
    memset(&msg,0,sizeof(msg));
    if((bytes = msgrcv(msgqid, &msg, sizeof(msg.mbuff),1,0)) < 0)
    {
        perror("msgrcv");
        exit(EXIT_FAILURE);
    }
     cout<<"\nReceived data: "<<msg.mbuff<<endl;
        cout<<"\nType: "<<msg.mtype<<endl;
    // while(msgrcv(msgqid, &msg, sizeof(msg.mbuff),1,0)<0)
    // {
    //     cout<<"\nReceived data: "<<msg.mbuff<<endl;
    //     cout<<"\nType: "<<msg.mtype<<endl;
    //    // memset(&msg,0,sizeof(msg));
    // }


    msgctl(msgqid, IPC_RMID,NULL);


    

    


    
    return 0;
}