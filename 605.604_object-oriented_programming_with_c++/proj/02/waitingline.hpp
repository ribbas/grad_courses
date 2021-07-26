#ifndef WAITING_LINE_HPP
#define WAITING_LINE_HPP

class WaitingLine {
public:
    WaitingLine() : capacity_(15) {}

    void add_to_line() {
        capacity_--;
    }

    bool is_empty() {
        return capacity_;
    }

private:
    int capacity_;
};

#endif
