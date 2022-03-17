/*
 * simple-loop-unswitch.c
 * This file demonstrates the simple-loop-unswitch optimization using the default
 * trivial parameter.
 * 
 * Sabbir Ahmed
 * 03/17/2022
 */

int main() {

    int j = 0;
    for (int i = 0; i < 10; i++) {
        j += 1;
        // the optimization would switch the loop due to this conditional
        if (i == 5) {
            j = 0;
        }
    }
    return 0;
}
