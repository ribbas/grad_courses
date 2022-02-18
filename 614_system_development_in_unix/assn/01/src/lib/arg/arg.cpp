/*
 * arg.cpp
 *
 * Sabbir Ahmed
 * System Development in the Unix Environment (605.614)
 *
 * This file contains the implementations for arg
 *
 */

#include "arg.hpp"

#include <cstdlib>
#include <iostream>
#include <string>

int get_argument(int argc, char* argv[], double* return_value) {

    if (argc != 2) {

        std::cout << "No arguments provided\n";
        return ERROR;

    } else {

        try {

            *return_value = std::stod(argv[1]);
            return OK;

        } catch (std::exception& e) {

            std::cout << "Invalid arguments provided\n";
            return ERROR;
        }
    }
}
