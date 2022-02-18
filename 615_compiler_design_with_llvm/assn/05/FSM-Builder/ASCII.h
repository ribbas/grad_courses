// ASCII.h
// by Allyn Shell
// Feb 2018

#ifndef ASCII_H_
#define ASCII_H_

// The 6 character categories in the ASCII alphabet are:
//enum categ {
    //WS,  // 0  White Space
    //CON, // 1  Control Characters
    //SYM, // 2  Special Symbols
    //DGT, // 3  Numeric Digit
    //UC,  // 4  Upper Case Alpha
    //LC   // 5  Lower Case Alpha
//};

const char ASCtok[] = {
    // this array is used to switch the getToken to the right category
    1, 1, 1, 1, 2, 1, 1, 1, // END_FILE is treated as a special symbol
    1, 0, 0, 0, 0, 2, 1, 1, // CR is treated as a special symbol
    1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1,

    0, 2, 2, 2, 2, 2, 2, 2,
    2, 2, 2, 3, 2, 3, 2, 2, // INT can start with '+' or '-'
    3, 3, 3, 3, 3, 3, 3, 3,
    3, 3, 2, 2, 2, 2, 2, 2,

    2, 4, 4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4, 6, 4, // N for getNAMELIST
    4, 4, 4, 4, 4, 4, 4, 4,
    4, 4, 4, 2, 2, 2, 2, 2,

    2, 5, 5, 5, 7, 5, 7, 5, // d f for getKeyword
    5, 5, 5, 5, 5, 5, 5, 5,
    5, 5, 5, 5, 7, 5, 5, 5, // t for getKeyword
    5, 5, 5, 2, 2, 2, 2, 2
};

const char ASCII[] = {
    1, 1, 1, 1, 1, 1, 1, 1,
    1, 0, 0, 0, 0, 0, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1,

    0, 2, 2, 2, 2, 2, 2, 2,
    2, 2, 2, 2, 2, 2, 2, 2,
    3, 3, 3, 3, 3, 3, 3, 3,
    3, 3, 2, 2, 2, 2, 2, 2,

    2, 4, 4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4, 4, 4,
    4, 4, 4, 2, 2, 2, 2, 2,

    2, 5, 5, 5, 5, 5, 5, 5,
    5, 5, 5, 5, 5, 5, 5, 5,
    5, 5, 5, 5, 5, 5, 5, 5,
    5, 5, 5, 2, 2, 2, 2, 2
};

#endif // ASCII_H_
