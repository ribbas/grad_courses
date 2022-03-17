/*
 * argpromotion.c
 * This file demonstrates the argpromotion optimization.
 * 
 * Sabbir Ahmed
 * 03/17/2022
 */

/* 
 * This function takes in integer pointers as parameters and returns the
 * sum of the values they point to. The arguments are only used to load
 * the values they point to and they are never modified.
 */
int add(int* a, int* b) {
    return *a + *b;
}

int main() {

    int a = 10;
    int b = 20;
    // pass in references to the integers
    int c = add(&a, &b);
    return 0;
}
