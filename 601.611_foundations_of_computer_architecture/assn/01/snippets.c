/*
 * snippets.c
 * 
 * Author: Sabbir Ahmed
 * Date: 02/03/2021
 * 
 * A collection of functions implementing the requirements outlined by several
 * problems in 605.611 - Foundations of Computer Architecture: Assignment 1.
 * 
 * This file includes all of the code required to complete the problems 9, 13, 14,
 * and 15 of the assignment. The functions corresponding to the problems are:
 * - int to_negative(int);
 * - char to_upper_case(char);
 * - char to_lower_case(char);
 * - int to_int(char*);
 * respectively.
 * 
 * This C file can be compiled with any popular compilers.
 */

#include <stdio.h>  // for printing return values to stdout
#include <stdlib.h>  // for rand(), srand()

/* Returns the negative value of an integer.
 * 
 *  @params:
 *      (int) integer: integer argument to be negated
 * 
 * This function accepts a single integer argument and returns its negative
 * value by computing its bitwise complement and adding 1.
 *
 * This function corresponds to Problem 9 of Assignment 1.
 */
int to_negative(int integer) {

    return (~integer + 1);

}

/* Returns the lower case of a character.
 * 
 *  @params:
 *      (char) character: character argument to be converted to lower case
 * 
 * This function accepts a single character argument and converts it to its
 * lower case by computing its bitwise disjunction (using the OR operator)
 * with 0x20. This function does not distinguish between already converted
 * characters.
 *
 * This function corresponds to Problem 13 of Assignment 1.
 */
char to_lower_case(char character) {

    return (character | 0x20);

}

/* Returns the upper case of a character.
 * 
 *  @params:
 *      (char) character: character argument to be converted to upper case
 * 
 * This function accepts a single character argument and converts it to its
 * upper case by computing its bitwise conjunction (using the AND operator)
 * with the negated value of 0x20 (which is -33 in decimal). This function
 * does not distinguish between already converted characters.
 *
 * This function corresponds to Problem 14 of Assignment 1.
 */
char to_upper_case(char character) {

    return (character & 0xDF);

}

/* Returns the integer value of a numeric string.
 * 
 *  @params:
 *      (char*) input_number: numeric string
 * 
 * This function accepts a numeric string and converts it into an integer.
 * 
 * `input_number` must be a valid null-terminated string.
 * 
 * `input_number` must be a valid decimal value and must be equal to or less
 * than INT_MAX (2147483647 or 0x7FFFFFFF). If the value exceeds INT_MAX, the
 * overflowed value will be returned.
 * 
 * `input_number` must be a positive decimal and must not contain any sign
 * characters i.e. '+' or '-'. Furthermore, the argument must not contain
 * any non-numeric characters as the function will still compute their ASCII
 * values and return the results.
 *
 * This function corresponds to Problem 15 of Assignment 1.
 */
int to_int(char* input_number) {

    int ret_val = 0;

    // loop until the character array finds the NULL value
    for (int c = 0; input_number[c] != '\0'; c++) {
        ret_val *= 10;
        ret_val += (input_number[c] - '0');
    }

    return ret_val;

}

/* Entry point of the file serving as a driver for all the functions
 * implemented above.
 */
int main() {

    srand(0);  // seed the RNG

    // the following loop will generate 10 random numbers under 100 and their
    // negative values will be computed
    for (int i = 0; i < 10; i++) {
        unsigned int rand_int = rand() % 100;
        printf("Negating %d to %d\n", rand_int, to_negative(rand_int));
    }

    // ------------------------------------------------------------------------

    const char* test_string = "hElLO woRLd";

    // the following loop will print out "hello world"
    printf("Converting '%s' to lower case: ", test_string);
    for (int i = 0; i < 11; i++) {
        printf("%c", to_lower_case(test_string[i]));
    }
    printf("\n");

    // ------------------------------------------------------------------------

    // the following loop will print out "HELLOWORLD"
    printf("Converting '%s' to upper case: ", test_string);
    for (int i = 0; i < 11; i++) {
        printf("%c", to_upper_case(test_string[i]));
    }
    printf("\n");

    // ------------------------------------------------------------------------

    // the following function call will convert the numeric string into an
    // integer
    char* test_numeric_string = "687435634";
    printf("%d\n", to_int(test_numeric_string));

    return 0;

}
