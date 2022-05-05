#include <fcntl.h>
#include <mqueue.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>

#define MESSAGE_PRIO 0

int main(void) {
    mqd_t MQDes;
    int ret;
    char Message[100];
    char MQName[10] = "/USER_MQ";

    MQDes = mq_open(MQName, O_RDWR | O_CREAT | O_EXCL, 777, NULL);
    if (MQDes == -1) {
        perror("server mq_open");
        return -1;
    }

    printf("Enter your inputs line by line.\nTo Exit, type 'EXIT' .\n");
    do {
        scanf("%s", Message);

        ret = mq_send(MQDes, Message, sizeof(Message), MESSAGE_PRIO);
        if (ret == -1) {
            perror("mq_send");
            return -1;
        }
    } while (strcasecmp(Message, "EXIT"));

    ret = mq_close(MQDes);
    if (ret == -1) {
        perror("mq_close");
        return -1;
    }

    ret = mq_unlink(MQName);
    if (ret == -1) {
        perror("mq_unlink");
        return -1;
    }

    return 0;
}