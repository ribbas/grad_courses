#include "station.hpp"

VaccinationStation::VaccinationStation() {
    customers_in_stations_.fill(nullptr);
}

VaccinationStation::~VaccinationStation() {
    reset();
}

void VaccinationStation::reset() {
    for (int i = 0; i < NUM_STATIONS; i++) {
        delete customers_in_stations_[i];
        customers_in_stations_[i] = nullptr;
    }
}

void VaccinationStation::vaccinate(Customer* customer,
                                   int available_station_num) {
    customers_in_stations_[available_station_num] = customer;
}

int VaccinationStation::find_available_station() {
    for (int i = 0; i < NUM_STATIONS; i++) {
        if (!customers_in_stations_[i]) {
            return i;
        }
    }

    return -1;
}

bool VaccinationStation::check_station_time(int station_num, int tick) {
    return customers_in_stations_[station_num]->get_total_time() < tick;
}

void VaccinationStation::poll(int tick) {

    for (int i = 0; i < NUM_STATIONS; i++) {
        if (customers_in_stations_[i] && check_station_time(i, tick)) {
            delete customers_in_stations_[i];
            customers_in_stations_[i] = nullptr;
        }
    }
}
