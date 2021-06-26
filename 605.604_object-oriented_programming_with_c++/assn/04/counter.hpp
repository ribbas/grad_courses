class Counter {

public:
    Counter() : count_(0) {}

    int get_count() {
        return count_;
    }

    void increment() {
        count_++;
    }

    void decrement() {
        count_--;
    }

    void reset() {
        count_ = 0;
    }

private:
    int count_;
};

class MemoryCounter {

public:
    MemoryCounter(Counter* counter) : mem_value_(0), counter_(counter) {}

    ~MemoryCounter() {
        delete counter_;
        counter_ = nullptr;
    }

    void add_mem(const int mem_value) {
        mem_value_ = mem_value;
    }

    int current_value() {
        return mem_value_ + counter_->get_count();
    }

    void increment() {
        counter_->increment();
    }

    void decrement() {
        counter_->decrement();
        if (current_value() < 0) {
            reset();
        }
    }

    void reset() {
        counter_->reset();
        reset_mem();
    }

    void reset_mem() {
        mem_value_ = 0;
    }

private:
    int mem_value_;
    Counter* counter_;
};
