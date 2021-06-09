#ifndef ITEM_HPP
#define ITEM_HPP

#include <string>

class Item {

public:
    Item();

    Item(std::string, float, int = 0);

    void set_name(std::string);

    void set_price(float);

    void set_count(int);

    void inc_count();

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
