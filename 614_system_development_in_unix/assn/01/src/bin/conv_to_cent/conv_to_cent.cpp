#include "conv_to_cent.hpp"
#include <cstdlib>
#include <iostream>

int main(int argc, char* argv[]) {

    if (argc < 2) {
        return -1;
    } else {
        std::cout << convert_to_cent(std::atof(argv[1])) << '\n';
    }

    return 0;
}
