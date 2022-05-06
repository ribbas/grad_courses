/*
 * listener.c
 * 
 * This file is the client portion of the simple example for mq_notify.
 *
 */

#include <ctype.h>
#include <mqueue.h>
#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

mqd_t Mqd;
struct mq_attr Mq_Struct;
int Quit_Flag = 0;
struct sigevent Signal;

void recv_msg() {

    if (mq_getattr(Mqd, &Mq_Struct) == -1) {
        perror("mq_getattr");
        return;
    }

    char msg[16];
    if (mq_receive(Mqd, msg, Mq_Struct.mq_msgsize, 0) == -1) {
        perror("mq_receive");
        return;
    }

    if (strcasecmp(msg, "q") == 0) {

        printf("Server is done sending messages\n");
        Quit_Flag = 1;

    } else {

        size_t i;
        for (i = 0; i < strlen(msg); i++) {
            msg[i] = toupper(msg[i]);
        }
        printf("%s\n", msg);

        if (mq_getattr(Mqd, &Mq_Struct) == -1) {
            perror("mq_getattr");
            return;
        }

        if (mq_notify(Mqd, &Signal) == -1) {
            perror("mq_notify");
            return;
        }
    }

    return;
}

int main() {

    Mqd = mq_open("/USER_MQ", O_RDONLY);
    if (Mqd == -1) {
        perror("mq_open");
        return -1;
    }

    if (mq_getattr(Mqd, &Mq_Struct) == -1) {
        perror("mq_getattr");
        return -1;
    }

    printf("Messages from the notifier:\n");
    Signal.sigev_notify = SIGEV_THREAD;
    Signal.sigev_notify_function = recv_msg;

    if (mq_notify(Mqd, &Signal) == -1) {
        perror("mq_notify");
        return -1;
    }

    while (Quit_Flag != 1);

    return 0;
}