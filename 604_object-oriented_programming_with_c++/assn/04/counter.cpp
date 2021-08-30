/*
 * counter.cpp
 * Sabbir Ahmed
 * 605.604: Object-Oriented Programming Using C++
 * Week 4 Assignment
 *
 * Driver file for the MemoryCounter and Counter classes
 *
 */

#include <iostream>

#include "counter.hpp"

int main() {

    std::cout << "Creating MemoryCounter object memory_counter with default "
                 "memory value\n";
    auto memory_counter = new MemoryCounter(new Counter);

    std::cout << "Incrementing memory counter 5 times. Current value: ";
    for (int i = 0; i < 5; i++) {
        memory_counter->increment();
    }
    std::cout << memory_counter->current_value() << '\n';

    std::cout << "Setting memory value to 10\n";
    memory_counter->add_mem(10);
    std::cout << "Incrementing memory counter 5 times. Current value: ";
    for (int i = 0; i < 5; i++) {
        memory_counter->increment();
    }
    std::cout << memory_counter->current_value() << '\n';

    std::cout << "Decrementing memory counter 10 times. Current value: ";
    for (int i = 0; i < 10; i++) {
        memory_counter->decrement();
    }
    std::cout << memory_counter->current_value() << '\n';

    std::cout << "Decrementing memory counter 200 times. Current value: ";
    for (int i = 0; i < 200; i++) {
        memory_counter->decrement();
    }
    std::cout << memory_counter->current_value() << '\n';

    delete memory_counter;
    memory_counter = nullptr;
}
