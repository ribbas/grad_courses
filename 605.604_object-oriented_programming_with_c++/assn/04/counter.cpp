#include <iostream>

#include "counter.hpp"

int main() {

    auto memory_counter = new MemoryCounter(new Counter);

    for (int i = 0; i < 5; i++) {
        memory_counter->increment();
    }
    std::cout << memory_counter->current_value() << '\n';

    memory_counter->add_mem(10);
    for (int i = 0; i < 5; i++) {
        memory_counter->increment();
    }
    std::cout << memory_counter->current_value() << '\n';

    for (int i = 0; i < 10; i++) {
        memory_counter->decrement();
    }
    std::cout << memory_counter->current_value() << '\n';

    for (int i = 0; i < 200; i++) {
        memory_counter->decrement();
    }
    std::cout << memory_counter->current_value() << '\n';

    delete memory_counter;
    memory_counter = nullptr;
}
