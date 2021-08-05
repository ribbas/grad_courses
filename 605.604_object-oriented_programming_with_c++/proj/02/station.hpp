#ifndef STATION_HPP
#define STATION_HPP

#include "customer.hpp"
#include <array>

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

    void vaccinate(Customer* customer) {
        int available_station_num = find_available_station();
        if (available_station_num != -1) {
            customers_in_stations_[available_station_num] = customer;
        }
    }

    int find_available_station() {
        for (int i = 0; i < NUM_STATIONS; i++) {
            if (!customers_in_stations_[i]) {
                return i;
            }
        }

        return -1;
    }

    bool check_station_time(int station_num, int tick) {
        return customers_in_stations_[station_num]->get_total_time() < tick;
    }

    void send_home(int tick) {

        for (int i = 0; i < NUM_STATIONS; i++) {
            if (customers_in_stations_[i] && check_station_time(i, tick)) {
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
