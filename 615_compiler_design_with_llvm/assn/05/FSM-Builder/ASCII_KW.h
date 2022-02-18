// ASCII_KW.h
// by Allyn Shell
// November 2018

#ifndef ASCII_KW_H
#define ASCII_KW_H

// The KW_Index table maps the input characters into
// the transitions to KW_FSM, the next state index.
const char KW_Index[128] = {
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,

    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,

    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,

    0, 1, 0, 0, 2, 3, 4, 0, // a d e f
    0, 0, 0, 0, 5, 0, 0, 0, // l
    0, 0, 6, 7, 8, 9, 0, 0, // r s t u
    0, 0, 0, 0, 0, 0, 0, 0
};

// The KW_FSM table maps the next FSM state
// transition index. The first index is the
// current state. The second index is the
// index from the KW_IND table.
const char KW_State[19][10] = { // indexed by [state][KW_IND]
    //    a   d   e   f   l   r   s   t   u
    { 0,  0,  0,  0,  0,  0,  0,  0,  0,  0 }, //  0 exit
    { 0,  0,  2,  0,  9,  0,  0,  0, 13,  0 }, //  1 state d f t
    { 0,  0,  0,  3,  0,  0,  0,  0,  0,  0 }, //  2 state de
    { 0,  0,  0,  0,  4,  0,  0,  0,  0,  0 }, //  3 state def
    { 0,  5,  0,  0,  0,  0,  0,  0,  0,  0 }, //  4 state defa
    { 0,  0,  0,  0,  0,  0,  0,  0,  0,  6 }, //  5 state defau
    { 0,  0,  0,  0,  0,  7,  0,  0,  0,  0 }, //  6 state defaul
    { 0,  0,  0,  0,  0,  0,  0,  0,  8,  0 }, //  7 state default
    { 0,  0,  0,  0,  0,  0,  0, 16,  0,  0 }, //  8 state defaults *
    { 0, 10,  0,  0,  0,  0,  0,  0,  0,  0 }, //  9 state fa
    { 0,  0,  0,  0,  0, 11,  0,  0,  0,  0 }, // 10 state fal
    { 0,  0,  0,  0,  0,  0,  0, 12,  0,  0 }, // 11 state fals
    { 0,  0,  0, 17,  0,  0,  0,  0,  0,  0 }, // 12 state false
    { 0,  0,  0,  0,  0,  0, 14,  0,  0,  0 }, // 13 state tr
    { 0,  0,  0,  0,  0,  0,  0,  0,  0, 15 }, // 14 state tru
    { 0,  0,  0, 18,  0,  0,  0,  0,  0,  0 }, // 15 state true
    { 0,  0,  0,  0,  0,  0,  0,  0,  0,  0 }, // 16 state (defaults) *
    { 0,  0,  0,  0,  0,  0,  0,  0,  0,  0 }, // 17 state (false) *
    { 0,  0,  0,  0,  0,  0,  0,  0,  0,  0 }  // 18 state (true) *
};

// The KW_accept table identifies which states are
// accepting states and which keyword they produce.
// enum TokenKind { ..., DEFAULTS, TRUE, FALSE, ... };
const int KW_Accept[] = {
        0, //  0
        0, //  1
        0, //  2
        0, //  3
        0, //  4 
        0, //  5 
        0, //  6 
        0, //  7
       12, //  8 DEFAULTS
        0, //  9
        0, // 10
        0, // 11 
        0, // 12 
        0, // 13
        0, // 14
        0, // 15 
       12, // 16 DEFAULTS
       14, // 17 FALSE
       13  // 18 TRUE
};

#endif // ASCII_KW_H
