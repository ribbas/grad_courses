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

    // if wrong number of arguments
    if (argc != 2) {

        std::cout << "No arguments provided\n";
        return ERROR;

    } else {

        double value = std::atof(argv[1]);
        // if user input is non-zero and atof returns 0 (conversion failed),
        // return ERROR
        if (argv[1] != std::string("0") && value == 0) {

            std::cout << "Invalid arguments provided\n";
            return ERROR;

        } else {

            // successful conversion
            *return_value = value;
            return OK;
        }
    }
}
