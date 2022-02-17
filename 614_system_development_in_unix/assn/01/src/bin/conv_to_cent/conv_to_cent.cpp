#include "conv_to_cent.hpp"
#include "arg.hpp"

#include <iostream>

int main(int argc, char* argv[]) {

    double value = 0.0;

    int arg_status = get_argument(argc, argv, &value);

    if (!arg_status) {
        double converted_value = convert_to_cent(value);
        std::cout << value << " degrees Fahrenheit is " << converted_value
                  << " degrees centigrade\n";
    } else {
        std::cout << "No args\n";
    }

    return arg_status;
}
