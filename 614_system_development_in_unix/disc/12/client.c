#include <fcntl.h>
#include <mqueue.h>
#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#define MESSAGE_PRIO 0

mqd_t MQDes;
int ret;
char Message[100];
char MQName[10] = "/USER_MQ";
ssize_t NoOfBytesRx;
struct mq_attr MQStat;
int quit;
struct sigevent SIGNAL;

static void RxMessage() {
    ret = mq_getattr(MQDes, &MQStat);
    if (ret == -1) {
        perror("mq_getattr");
        return;
    }
    printf("On Entering MQStat.mq_curmsgs: %ld\n", MQStat.mq_curmsgs);
    NoOfBytesRx = mq_receive(MQDes, Message, (MQStat.mq_msgsize), MESSAGE_PRIO);

    if (NoOfBytesRx == -1) {
        perror("mq_receive");
        return;
    }

    printf("%s", Message);

    if (strcasecmp(Message, "EXIT") == 0) {
        printf("\n");
        quit = 1;
    } else {
        ret = mq_getattr(MQDes, &MQStat);
        if (ret == -1) {
            perror("mq_getattr");
            return;
        }
        printf("On Exiting MQStat.mq_curmsgs: %ld\n", MQStat.mq_curmsgs);
        ret = mq_notify(MQDes, &SIGNAL);
        if (ret == -1) {
            perror("mq_notify");
            return;
        }
    }

    return;
}

int main(void) {
    MQDes = mq_open(MQName, O_RDONLY);
    if (MQDes == -1) {
        perror("mq_open");
        return -1;
    }

    ret = mq_getattr(MQDes, &MQStat);
    if (ret == -1) {
        perror("mq_getattr");
        return -1;
    }
    printf("MQ_MAXMSG:%ld\n", MQStat.mq_maxmsg);
    printf("MQ_MSGSIZE:%ld\n", MQStat.mq_msgsize);

    printf("These are the messages from the server:\n");

    SIGNAL.sigev_notify = SIGEV_THREAD;
    SIGNAL.sigev_notify_function = RxMessage;
    SIGNAL.sigev_notify_attributes = NULL;

    ret = mq_notify(MQDes, &SIGNAL);
    if (ret == -1) {
        perror("mq_notify");
        return -1;
    }

    while (quit != 1)
        ;

    return 0;
}