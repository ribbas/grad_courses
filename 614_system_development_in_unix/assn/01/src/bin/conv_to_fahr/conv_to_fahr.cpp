#include "conv_to_fahr.hpp"
#include <cstdlib>
#include <iostream>

int main(int argc, char* argv[]) {

    if (argc < 2) {
        return -1;
    } else {
        std::cout << "fahr\n";
        std::cout << convert_to_fahr(std::atof(argv[1])) << '\n';
    }

    return 0;
}
