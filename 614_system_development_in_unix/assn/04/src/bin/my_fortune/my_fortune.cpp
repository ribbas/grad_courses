/*
 * install_and_monitor.cpp
 *
 * Sabbir Ahmed
 * System Development in the Unix Environment (605.614)
 *
 * This file contains the driver for the install_and_monitor library
 *
 */

#include "log_mgr.hpp"
#include "thread_mgr.hpp"

#include <cstdlib>
#include <cstring>
#include <errno.h>
#include <iostream>
#include <signal.h>
#include <stdexcept>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <sys/time.h>
#include <unistd.h>

const short DELAY_LO = 1;
const short DELAY_HI = 2;

/*
 * This method utilizes setitimer and SIGALRM to implement sleep for `sec`
 * seconds. The number of seconds is a double and can therefore be fractional
 * increments of time.
 */
void sleep_sec(double sec) {

    struct itimerval new_it, old_it;
    struct sigaction catch_alarm, old_sig;

    // pass in a noop lambda as the handler
    catch_alarm.sa_handler = ([](int) {});

    // empty mask
    sigset_t empty;
    sigemptyset(&empty);
    catch_alarm.sa_mask = empty;

    // no flags
    catch_alarm.sa_flags = 0;

    if (sigaction(SIGALRM, &catch_alarm, &old_sig) < 0) {
        fprintf(stderr, "sigaction: (%d) %s\n", errno, strerror(errno));
    }

    // convert seconds to milliseconds for convenient computations
    int ms = sec * 1000;
    new_it.it_value.tv_sec = ms / 1000;
    new_it.it_value.tv_usec = 1000 * (ms % 1000);
    new_it.it_interval.tv_sec = 0;
    new_it.it_interval.tv_usec = 0;

    if (setitimer(ITIMER_REAL, &new_it, &old_it) < 0) {
        fprintf(stderr, "setitimer: (%d) %s\n", errno, strerror(errno));
        return;
    };

    pause();
    if (sigaction(SIGALRM, &old_sig, nullptr) < 0) {
        fprintf(stderr, "sigaction: (%d) %s\n", errno, strerror(errno));
    }
}

std::string exec(const char* cmd) {
    char buffer[128];
    std::string result = "";
    FILE* pipe = popen(cmd, "r");
    if (!pipe)
        throw std::runtime_error("popen() failed!");
    try {
        while (fgets(buffer, sizeof(buffer), pipe) != NULL) {
            result += buffer;
        }
    } catch (...) {
        pclose(pipe);
        throw;
    }
    pclose(pipe);
    return result;
}

int main() {

    srand(time(nullptr));

    fd_set rfds;
    struct timeval tv;
    int retval;

    char user_input;
    int random_delay = 0;

    while (user_input != 'q') {

        printf("user input %c\n", user_input);

        std::string fortune = exec("./fortune");
        for (int i = 0; i < fortune.size(); i++) {
            fortune.at(i) = toupper(fortune.at(i));
        }
        std::cout << fortune;

        /* Watch stdin (fd 0) to see when it has input. */
        FD_ZERO(&rfds);
        FD_SET(0, &rfds);
        /* Wait up to five seconds. */
        tv.tv_sec = 0;
        tv.tv_usec = 0;

        retval = select(1, &rfds, nullptr, nullptr, &tv);
        /* Don’t rely on the value of tv now! */

        if (retval == -1) {
            perror("select()");
        } else if (retval) {
            user_input = getchar();
            if (user_input == 'q') {
                break;
            }
        }

        random_delay = DELAY_LO + rand() % DELAY_HI;
        std::cout << "sleeping for " << random_delay << "s\n";
        sleep_sec(random_delay);
    }

    return OK;
}

/*

#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

struct Common {
    bool mRunning;
    float mCount;
};
void* Cruncher(void* info) {
    struct Common* cptr = (struct Common*)info;
    cptr->mCount = 0.0;
    while (cptr->mRunning) {
        sleep(1);
        cptr->mCount++;
    }

    return (void*)0;
}

void* PollKbd(void* info) {
    struct Common* cptr = (struct Common*)info;
    int ch;

    printf("Press q followed by return to quit\n");
    do {
        ch = getchar();

    } while (ch != 'q');
    cptr->mRunning = false;

    return (void*)0;
}

int main() {
    pthread_t crunchThread, pollThread;
    struct Common common = {true, 0.0};

    pthread_create(&pollThread, 0, PollKbd, &common);
    pthread_create(&crunchThread, 0, Cruncher, &common);

    pthread_join(pollThread, 0);
    pthread_join(crunchThread, 0);

    printf("Count got up to %f\n", common.mCount);

    return 0;
}


*/