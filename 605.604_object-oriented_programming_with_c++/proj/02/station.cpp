/*
 * station.cpp
 * Sabbir Ahmed
 * 605.604: Object-Oriented Programming Using C++
 * Mini-project 2
 *
 * This file contains the implementation for the VaccinationStation class.
 *
 */

#include "station.hpp"

/*
 * Default constructor
 *
 * Params:
 *  None
 *
 * Returns:
 *  None
 */
VaccinationStation::VaccinationStation() {
    // prefill array with nullptr
    stations_.fill(nullptr);
}

/*
 * Default destructor
 *
 * Params:
 *  None
 *
 * Returns:
 *  None
 */
VaccinationStation::~VaccinationStation() {
    // clear out the contents of the array
    reset();
}

/*
 * Clear out the contents of the stations_ array
 *
 * Params:
 *  None
 *
 * Returns:
 *  None
 */
void VaccinationStation::reset() {
    for (unsigned int i = 0; i < NUM_STATIONS; i++) {
        delete stations_[i];
        stations_[i] = nullptr;
    }
}

/*
 * Assign the Customer object to the specified index of the stations_ array
 *
 * Params:
 *  customer <Customer*>: pointer to the Customer object
 *  available_station_num <int>: index of the stations_ array
 *
 * Returns:
 *  None
 */
void VaccinationStation::vaccinate(Customer* customer,
                                   int available_station_num) {
    // the bounds for the array index are predetermined to always be valid
    stations_[available_station_num] = customer;
}

/*
 * Check for the first available index of the stations_ array that is not
 * storing a Customer object
 *
 * Params:
 *  None
 *
 * Returns:
 *  <int>: index to the first available index in the station array
 */
int VaccinationStation::find_available_station() {

    for (unsigned int i = 0; i < NUM_STATIONS; i++) {
        // if the i-th index of the array is nullptr, it can hold a new Customer
        // object
        if (!stations_[i]) {
            return i;
        }
    }

    // an invalid index indicating the stations_ array is full
    return -1;
}

/*
 * Check if the predetermined total time of the Customer at the specified index
 * is less than the current clock
 *
 * Params:
 *  station_num <int>: specified index of the stations_ array
 *  tick <int>: current tick of the simulation clock
 *
 * Returns:
 *  <bool>: if the Customer is ready to exit
 */
bool VaccinationStation::is_customer_done(int station_num, int tick) {
    return stations_[station_num]->get_total_time() < tick;
}

/*
 * Poll the stations_ array to check for an available station
 *
 * Params:
 *  tick <int>: current tick of the simulation clock
 *
 * Returns:
 *  None
 */
void VaccinationStation::poll(int tick) {

    for (unsigned int i = 0; i < NUM_STATIONS; i++) {
        // if the i-th index has a Customer object and the Customer is ready to
        // exit
        if (stations_[i] && is_customer_done(i, tick)) {
            delete stations_[i];
            stations_[i] = nullptr;
        }
    }
}
