#include <fcntl.h>
#include <mqueue.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>

int main() {

    mqd_t mqd = mq_open("/USER_MQ", O_RDWR | O_CREAT | O_EXCL, 777, NULL);
    if (mqd == -1) {
        perror("server mq_open");
        return -1;
    }

    char msg[16];
    printf("Notify the client with a message (under 16 chars)\n");
    while (1) {

        scanf("%s", msg);
        if (mq_send(mqd, msg, sizeof(msg), 0) == -1) {
            perror("mq_send");
            return -1;
        }

        if (strcasecmp(msg, "q") == 0) {
            printf("Server is done sending messages\n");
            break;
        }
    }

    if (mq_close(mqd) == -1) {
        perror("mq_close");
        return -1;
    }

    if (mq_unlink("/USER_MQ") == -1) {
        perror("mq_unlink");
        return -1;
    }

    return 0;
}