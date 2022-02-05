// Ascii_KW.h
//
// by Allyn Shell
// 1/2018
//
// These tables combine to scan the following five keywords:
//     else  end  if  return  then

#ifndef ASCII_KW_H_
#define ASCII_KW_H_


// The KW_IND table maps the input characters into 
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

	0, 0, 0, 0, 1, 2, 3, 0, // d, e, f
	4, 5, 0, 0, 6, 0, 7, 0, // h, i, l, n
	0, 0, 8, 9,10,11, 0, 0, // r, s, t, u
	0, 0, 0, 0, 0, 0, 0, 0
};

// The KW_State table maps the next FSM state
// transition index. The first index is the
// current state. The second index is the
// index from the KW_IND table.
const char KW_State[20][12] = { // indexed by [state][index]
    //    d   e   f   h   i   l   n   r   s   t   u
    { 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 }, //  0 exit
    { 0,  0,  2,  0,  0,  8,  0,  0, 10,  0, 16,  0 }, //  1 state can match e i r t
    { 0,  0,  0,  0,  0,  0,  3,  6,  0,  0,  0,  0 }, //  2 state can match el en
    { 0,  0,  0,  0,  0,  0,  0,  0,  0,  4,  0,  0 }, //  3 state can match els
    { 0,  0,  5,  0,  0,  0,  0,  0,  0,  0,  0,  0 }, //  4 state can match else
    { 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 }, //  5 state can match else *
    { 0,  7,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 }, //  6 state can match end 
    { 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 }, //  7 state can match end *
    { 0,  0,  0,  9,  0,  0,  0,  0,  0,  0,  0,  0 }, //  8 state can match if
    { 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 }, //  9 state can match if *
    { 0,  0, 11,  0,  0,  0,  0,  0,  0,  0,  0,  0 }, // 10 state can match re
    { 0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 12,  0 }, // 11 state can match ret
    { 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 13 }, // 12 state can match retu
    { 0,  0,  0,  0,  0,  0,  0,  0, 14,  0,  0,  0 }, // 13 state can match retur
    { 0,  0,  0,  0,  0,  0,  0, 15,  0,  0,  0,  0 }, // 14 state can match return
    { 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 }, // 15 state can match return *
    { 0,  0,  0,  0, 17,  0,  0,  0,  0,  0,  0,  0 }, // 16 state can match th
    { 0,  0, 18,  0,  0,  0,  0,  0,  0,  0,  0,  0 }, // 17 state can match the
    { 0,  0,  0,  0,  0,  0,  0, 19,  0,  0,  0,  0 }, // 18 state can match then
    { 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 }  // 19 state can match then *
};

// The KW_Accept table identifies which states are
// accepting states and which keyword they produce.
// enum Keyword { UNKNOWN, ELSE, END, IF, RETURN, THEN };
const int KW_Accept[] = {
        0, //  0
        0, //  1
        0, //  2
        0, //  3
        0, //  4
        1, //  5 ELSE
        0, //  6
        2, //  7 END
        0, //  8
        3, //  9 IF
        0, // 10
        0, // 11
        0, // 12
        0, // 13
        0, // 14
        4, // 15 RETURN
        0, // 16
        0, // 17
        0, // 18
        5  // 19 THEN
};

#endif // ASCII_KW_H_
