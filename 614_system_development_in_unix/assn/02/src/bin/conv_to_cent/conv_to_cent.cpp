/*
 * conv_to_cent.cpp
 *
 * Sabbir Ahmed
 * System Development in the Unix Environment (605.614)
 *
 * This file contains the driver for conv_to_cent
 *
 */

#include "conv_to_cent.hpp"
#include "arg.hpp"

#include <iostream>

int main(int argc, char* argv[]) {

    double value = 0.0;

    int arg_status = get_argument(argc, argv, &value);

    // if return value is OK
    if (!arg_status) {
        double converted_value = convert_to_cent(value);
        std::cout << value << " degrees Fahrenheit is " << converted_value
                  << " degrees centigrade\n";
    }

    return arg_status;
}
