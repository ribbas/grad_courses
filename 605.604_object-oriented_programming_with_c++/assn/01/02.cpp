#include <climits>
#include <iostream>

void swap_ptr(int* a, int* b) {

    if (*a > *b) {
        int temp = *a;
        *a = *b;
        *b = temp;
    }

}

void swap_ref(int& a, int& b) {

    if (a > b) {
        int temp = a;
        a = b;
        b = temp;
    }

}

int main() {

    int a = 10;
    int b = 5;

    std::cout << "Before swapping (as pointers): " << a << " " << b << '\n';
    swap_ptr(&a, &b);
    std::cout << "After swapping (as pointers): " << a << " " << b << '\n';

    int c = 10;
    int d = 5;

    std::cout << "Before swapping (as references): " << c << " " << d << '\n';
    swap_ptr(&c, &d);
    std::cout << "After swapping (as references): " << c << " " << d << '\n';

    return 0;

}
