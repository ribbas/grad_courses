#include <iostream>

class MyArray {
public:
    // Default constructor
    MyArray(int sz) : data(new int[sz]), size(sz) {}

    // Copy constructor
    MyArray(const MyArray& p1) : MyArray(p1.size) {}

    // Default destructor
    ~MyArray() {
        if (data) {
            delete[] data;
            data = nullptr;
            size = 0;
        }
    }

    /* --------------- SETTERS/GETTERS --------------- */
    void assign(const int index, const int value) {
        if (index > -1 && index < size) {
            data[index] = value;
        } else {
            std::cout << "Index is out of range\n";
        }
    };

    int at(int index) {
        if (index > -1 && index < size) {
            return data[index];

        } else {
            std::cout << "Index is out of range\n";
            return 0;
        }
    }

    const int* get_array() {
        return data;
    }

    int get_size() {
        return size;
    }

private:
    int* data;
    int size;
};

int main() {
    MyArray existingObj(3);

    existingObj.assign(0, 50);
    existingObj.assign(1, 40);
    existingObj.assign(2, 60);
    std::cout << existingObj.get_size() << '\n';
    std::cout << existingObj.at(0) << '\n';
    std::cout << existingObj.at(1) << '\n';
    std::cout << existingObj.at(2) << '\n';

    MyArray newObj = existingObj;
    newObj.assign(2, 60000);
    std::cout << existingObj.get_size() << '\n';
    std::cout << existingObj.at(2) << '\n';
    std::cout << newObj.get_size() << '\n';
    std::cout << newObj.at(2) << '\n';
}
