/*
 * simple-loop-unswitch.c
 * This file demonstrates the simple-loop-unswitch optimization using the default
 * trivial parameter.
 * 
 * Sabbir Ahmed
 * 03/17/2022
 */

#include <stdio.h>

int main() {

    int i = 0;
    int j;
    scanf("%d", &j);
    int k = 0;
    int l = 0;
    while (i < 10) {

        // the optimization would switch the loop due to this conditional
        if (j == 10) {
            k++;
        } else {
            l++;
        }
        i++;
    }

    return k;
}
