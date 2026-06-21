#include <iostream>
#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h>
#define MQ_NAME "/posix_mq"
#define MAX_BUFF 8192

using namespace std;
int main() {
    mqd_t mq = mq_open(MQ_NAME, O_RDONLY);

    unsigned int priority;
    char buff[MAX_BUFF] = {'\0',};
    
    if(mq < 0)
    {
        cout<<"\nError: mq_open"<<endl;
        exit(EXIT_FAILURE);
    }

    if(mq_receive(mq, buff,sizeof(buff), &priority)==-1)
        {
            perror("mq_receive");
            exit(EXIT_FAILURE);
        }
    cout<<buff<<endl;
    mq_close(mq);
    return 0;
}