#ifndef STATION_HPP
#define STATION_HPP

#include "customer.hpp"
#include <array>

const unsigned int NUM_STATIONS = 3;

class VaccinationStation {
public:
    VaccinationStation();

    ~VaccinationStation();

    void reset();

    void vaccinate(Customer*, int);

    int find_available_station();

    void poll(int);

private:
    bool is_customer_done(int, int);

    std::array<Customer*, NUM_STATIONS> stations_;
    int capacity_;
};

#endif
