/*
 * install_and_monitor.cpp
 *
 * Sabbir Ahmed
 * System Development in the Unix Environment (605.614)
 *
 * This file contains the driver for the install_and_monitor program
 *
 */

#include "log_mgr.hpp"
#include "thread_mgr.hpp"
#include <cstdlib>
#include <cstring>
#include <errno.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <sys/time.h>
#include <unistd.h>

#ifdef __linux__
// absaroka
const std::string FORTUNE_EXE = "~jcn/unix_class/fortune_absaroka/fortune";
#else
// dev4
const std::string FORTUNE_EXE = "~jcn/unix_class/fortune/fortune";
#endif

const short DELAY_LO = 1;
const short DELAY_HI = 8;

std::string exec_and_pipe(const char* cmd) {

    char buffer[1000];
    std::string result = "";
    FILE* pipe = popen(cmd, "r");
    if (!pipe) {
        fprintf(stderr, "popen: (%d) %s\n", errno, strerror(errno));
    }

    while (fgets(buffer, sizeof(buffer), pipe) != nullptr) {
        result += buffer;
    }

    pclose(pipe);
    return result;
}

void to_upper(std::string& piped_output) {
    for (int i = 0; i < piped_output.size(); i++) {
        piped_output.at(i) = toupper(piped_output.at(i));
    }
}

void rand_wait() {
    sleep(DELAY_LO + rand() % DELAY_HI);
}

int main() {

    srand(time(nullptr));

    fd_set rfds;
    int rc;
    struct timeval tv;
    tv.tv_sec = 0;
    tv.tv_usec = 0;

    char user_input = ' ';

    while (user_input != 'q') {

        // watch stdin (fd 0) to see when it has input
        FD_ZERO(&rfds);
        FD_SET(0, &rfds);
        rc = select(1, &rfds, nullptr, nullptr, &tv);

        if (rc == -1) {

            fprintf(stderr, "select: (%d) %s\n", errno, strerror(errno));

        } else if (rc) {

            user_input = getchar();
            if (user_input == 'q') {
                break;
            }

        } else {

            std::string fortune_output = exec_and_pipe(FORTUNE_EXE.c_str());
            to_upper(fortune_output);
            std::cout << fortune_output;
            rand_wait();
        }
    }

    return OK;
}
