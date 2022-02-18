/*
 * conv_to_fahr.cpp
 *
 * Sabbir Ahmed
 * System Development in the Unix Environment (605.614)
 *
 * This file contains the driver for conv_to_fahr
 *
 */

#include "conv_to_fahr.hpp"
#include "arg.hpp"

#include <iostream>
#include <string>

int main() {

    // redirect user input (including newline) into std::cin
    std::cout << "Enter number of centigrade degrees: ";
    std::string user_input;
    getline(std::cin, user_input);

    // if user input is empty, return ERROR
    if (user_input.empty()) {
        std::cout << "No arguments provided\n";
        return ERROR;
    }

    double value = 0.0;
    // if user input can be converted to a double
    try {
        value = std::stod(user_input);

        // else, return ERROR
    } catch (std::exception& e) {

        std::cout << "Invalid arguments provided\n";
        return ERROR;
    }

    std::cout << value << " degrees centigrade is " << convert_to_fahr(value)
              << " degrees Fahrenheit\n";

    return OK;
}
