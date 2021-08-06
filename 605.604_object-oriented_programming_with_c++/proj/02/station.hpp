#ifndef STATION_HPP
#define STATION_HPP

#include "customer.hpp"
#include <array>

const int NUM_STATIONS = 3;

class VaccinationStation {
public:
    VaccinationStation();

    ~VaccinationStation();

    void reset();

    void vaccinate(Customer*);

    int find_available_station();

    void poll(int);

private:
    std::array<Customer*, NUM_STATIONS> customers_in_stations_;
    int capacity_;

    bool check_station_time(int, int);
};

#endif
