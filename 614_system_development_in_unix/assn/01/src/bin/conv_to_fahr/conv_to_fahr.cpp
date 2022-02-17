#include "conv_to_fahr.hpp"
#include "arg.hpp"

#include <iostream>

int main() {

    double value = 0.0;

    std::cout << "Enter number of centigrade degrees: ";
    std::cin >> value;
    double converted_value = convert_to_fahr(value);
    std::cout << value << " degrees centigrade is " << converted_value
              << " degrees Fahrenheit\n";

    return 0;
}
