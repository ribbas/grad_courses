/*
 * mqex3.c
 * 
 * This file is a modification of 'rbotty1/mqex2.c'. It adds support for an optional
 * path to a user-defined filesystem for message queues.
 *
 */

#include <mqueue.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

int main(int argc, char* argv[]) {

    mqd_t mqd;
    mqd = mq_open("/USER_MQ", O_CREAT | O_EXCL | O_WRONLY, 0600, NULL);

    if (errno == EEXIST) {

        mq_unlink("/USER_MQ");

    } else if (mqd == -1) {

        perror("mq_open()");
        exit(1);

    }

    char mq_dir[50];

    if (argc > 1) {
        strcpy(mq_dir, argv[1]);
    } else {
        strcpy(mq_dir, "/dev/mqueue");
    }
    char* mq_file_path = strcat(mq_dir, "/USER_MQ");

    FILE *file;
    if ((file = fopen(mq_file_path, "r"))) {
        fclose(file);
        printf("\n%s exists!\n", mq_file_path);
    } else {
        printf("\n%s does not appear as a file...\n", mq_file_path);
    }

    printf("Press any key to continue\n");
    getchar();
    mq_close(mqd);
    mq_unlink("/USER_MQ");

}
