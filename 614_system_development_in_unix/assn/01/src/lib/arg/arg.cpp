#include "arg.hpp"
#include <cstdlib>

#define ERROR -1
#define OK 0

int get_argument(int argc, char* argv[], double* return_value) {
    if (argc < 2) {
        return ERROR;
    } else {
        *return_value = std::atof(argv[1]);
        return OK;
    }

    return 0;
}
