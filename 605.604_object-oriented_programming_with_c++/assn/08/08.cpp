#include "date.hpp"
#include "templatearray.hpp"

int main() {

    int seed = 10;
    int size = 5;

    // seed the RNG
    srand(seed);

    // instantiate a TemplateArray of type 'int'
    TemplateArray<int> int_array(size);

    for (int i = 0; i < int_array.size(); i++) {
        int_array[i] = (rand() % 10);
    }

    for (int i = 0; i < int_array.size(); i++) {
        std::cout << int_array[i] << '\n';
    }

    // instantiate a TemplateArray of type 'float'
    TemplateArray<float> float_array(size);

    for (int i = 0; i < float_array.size(); i++) {
        float_array[i] = (rand() % 10) + (rand() % 10 + 1) / 10.0;
    }

    for (int i = 0; i < float_array.size(); i++) {
        std::cout << float_array[i] << '\n';
    }

    // instantiate a TemplateArray of type 'string'
    TemplateArray<std::string> str_array(size);

    for (int i = 0; i < str_array.size(); i++) {
        str_array[i] = std::string((rand() % 10 + 1), 'd');
    }

    for (int i = 0; i < str_array.size(); i++) {
        std::cout << str_array[i] << '\n';
    }

    // instantiate a TemplateArray of type 'Date'
    TemplateArray<Date*> date_array(size);

    for (int i = 0; i < str_array.size(); i++) {
        date_array[i] =
            new Date(rand() % 10 + 2010, rand() % 12 + 1, rand() % 29 + 1);
    }

    for (int i = 0; i < date_array.size(); i++) {
        std::cout << *date_array[i] << '\n';
    }

    for (int i = 0; i < date_array.size(); i++) {
        delete date_array[i];
    }

    return 0;
}
