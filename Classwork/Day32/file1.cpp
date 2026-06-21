#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h>
#define MQ_NAME "/posix_mq"
int main() {
    mqd_t mq = mq_open(MQ_NAME, O_CREAT | O_WRONLY, 0644, NULL);
    mq_send(mq, "Hello POSIX IPC!", 16, 0);
    mq_close(mq);
    return 0;
}