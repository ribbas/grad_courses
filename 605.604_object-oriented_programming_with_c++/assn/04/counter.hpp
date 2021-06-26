/*
 * counter.hpp
 * Sabbir Ahmed
 * 605.604: Object-Oriented Programming Using C++
 * Week 4 Assignment
 *
 * This file provides the declaration and implementation of the Counter and
 * MemoryCounter classes. The MemoryCounter class is a composition of the
 * Counter class and utilizes all of its functionalities.
 *
 */

class Counter {

public:
    /*
     * Default constructor - initializes the member variables
     *
     * Params:
     *  None
     *
     */
    Counter() : count_(0) {}

    /* --------------- METHODS --------------- */

    /*
     * Return current count
     *
     * Params:
     *  None
     *
     * Returns:
     *  count_ <int>: current value of the counter
     *
     */
    int get_count() {
        return count_;
    }

    /*
     * Increment value of counter
     *
     * Params:
     *  None
     *
     * Returns:
     *  None
     *
     */
    void increment() {
        count_++;
    }

    /*
     * Decrement value of counter
     *
     * Params:
     *  None
     *
     * Returns:
     *  None
     *
     */
    void decrement() {
        count_--;
    }

    /*
     * Reset value of counter
     *
     * Params:
     *  None
     *
     * Returns:
     *  None
     *
     */
    void reset() {
        count_ = 0;
    }

private:
    /* --------------- MEMBER ATTRIBUTES --------------- */
    int count_;
};

class MemoryCounter {

public:
    /*
     * Default constructor - initializes the member variables
     *
     * Params:
     *  counter <Counter*>: counter object
     *
     */
    MemoryCounter(Counter* counter) : mem_value_(0), counter_(counter) {}

    /*
     * Destructor - frees up dynamically allocated attributes and resets all
     * variables
     *
     */
    ~MemoryCounter() {
        delete counter_;
        counter_ = nullptr;
    }

    /* --------------- METHODS --------------- */

    /*
     * Assign memory value
     *
     * Params:
     *  mem_value <int>: new value
     *
     */
    void add_mem(const int mem_value) {
        mem_value_ = mem_value;
    }

    /*
     * Return current value of counter
     *
     * Params:
     *  None
     *
     * Returns:
     *  count_ <int>: current value of the counter
     *
     */
    int current_value() {
        return mem_value_ + counter_->get_count();
    }

    /*
     * Increment value of counter object
     *
     * Params:
     *  None
     *
     * Returns:
     *  None
     *
     */
    void increment() {
        counter_->increment();
    }

    /*
     * Decrement value of counter object
     *
     * Params:
     *  None
     *
     * Returns:
     *  None
     *
     */
    void decrement() {
        counter_->decrement();
        if (current_value() < 0) {
            reset();
        }
    }

    /*
     * Reset value of counter object
     *
     * Params:
     *  None
     *
     * Returns:
     *  None
     *
     */
    void reset() {
        counter_->reset();
        reset_mem();
    }

    /*
     * Reset memory value
     *
     * Params:
     *  None
     *
     * Returns:
     *  None
     *
     */
    void reset_mem() {
        mem_value_ = 0;
    }

private:
    /* --------------- MEMBER ATTRIBUTES --------------- */
    int mem_value_;
    Counter* counter_;
};
