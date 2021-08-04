#ifndef STATION_HPP
#define STATION_HPP

#include <array>
#include <iostream>

#include "customer.hpp"

const int NUM_STATIONS = 3;

class VaccinationStation {
public:
    VaccinationStation() {
        customers_in_stations_.fill(nullptr);
    }

    ~VaccinationStation() {
        for (int i = 0; i < NUM_STATIONS; i++) {
            delete customers_in_stations_[i];
            customers_in_stations_[i] = nullptr;
        }
    }

    bool vaccinate(Customer* customer) {
        for (int i = 0; i < NUM_STATIONS; i++) {
            std::cout << "checking station " << i << '\n';
            if (!customers_in_stations_[i]) {
                customers_in_stations_[i] = customer;
                std::cout << "putting " << customers_in_stations_[i]
                          << " in station " << i << '\n';
                return true;
            }
        }

        return false;
    }

    bool check_station_time(int station_num, int tick) {
        return customers_in_stations_[station_num]->get_total_time() < tick;
    }

    void send_home(int tick) {

        for (int i = 0; i < NUM_STATIONS; i++) {
            if (customers_in_stations_[i] && check_station_time(i, tick)) {
                std::cout << "found someone " << customers_in_stations_[i]
                          << ' ' << customers_in_stations_[i]->get_total_time()
                          << ' ' << tick << '\n';
                delete customers_in_stations_[i];
                customers_in_stations_[i] = nullptr;
            }
        }
    }

private:
    std::array<Customer*, NUM_STATIONS> customers_in_stations_;
    int capacity_;
};

#endif
