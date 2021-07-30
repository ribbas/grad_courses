#ifndef WAITING_LINE_HPP
#define WAITING_LINE_HPP

#include "customer.hpp"

class VaccinationStation {
public:
    VaccinationStation() : capacity_(3) {}

    void vaccinate(Customer* customer) {
        if (capacity_) {
            capacity_--;
            customers_in_stations[capacity_] = customer;
        }
    }

    bool is_empty() {
        return capacity_;
    }

private:
    Customer* customers_in_stations[3];
    int capacity_;
};

#endif
