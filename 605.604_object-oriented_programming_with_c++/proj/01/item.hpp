#ifndef ITEM_HPP
#define ITEM_HPP

#include <string>

class Item {

public:
    Item(std::string, float, int = 0);

    void set_name(std::string);

    void set_price(float);

    void set_count(int);

    void dec_count();

    std::string get_name();

    float get_price();

    int get_count();

private:
    std::string _name;
    float _price;
    int _count;
};

#endif
