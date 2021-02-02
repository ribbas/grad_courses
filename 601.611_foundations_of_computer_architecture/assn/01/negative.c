#include <stdio.h>

int negative(int);

int negative(int integer) {

    printf("%d\n", (~integer + 1));
    return (~integer + 1);

}

int main() {

    negative(20);
    negative(200);
    negative(200000000);
    negative(2);
    negative(-69);
    negative(0);
    return 0;
}
