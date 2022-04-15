// Ascii_SYM.h
//
// by Sabbir Ahmed
// 2/2022
//
// These tables combine to scan the following five keywords:
//     else  end  if  return  then

#ifndef ASCII_SYM_H_
#define ASCII_SYM_H_
// clang-format off

// The SYM_IND table maps the input characters into 
// the transitions to SYM_FSM, the next state index.
const char SYM_Index[128] = {
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,

	0, 0, 1, 2, 0, 0, 0, 0,  // ”, #
	3, 4, 5, 6, 0, 7, 0, 8,  // (, ), *, +, –, /
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 9,10,11,12, 0,  // <, =, >

	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,

	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0
};

// The SYM_State table maps the next FSM state
// transition index. The first index is the
// current state. The second index is the
// index from the SYM_index table.
// the comments next to the state arrays indicate the corresponding states
// $ indicates end of string 
const char SYM_State[20][13] = { // indexed by [state][index]
    //   ”  #  (  )  *  +  -  /  ;  <  =  >
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, //  0 exit
    { 0, 2, 3, 4, 5, 6, 8, 9,10,13,14,16,18 }, //  1 state can match
                                               // { ” | # | ( | ) | * | + | – | / | < | = | > }
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, //  2 state can match { ”$ }
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, //  3 state can match { #$ }
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, //  4 state can match { ($ }
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, //  5 state can match { )$ }
    { 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0 }, //  6 state can match { *$ | */ }
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, //  7 state can match { */$ }
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, //  8 state can match { +$ }
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, //  9 state can match { –$ }
    { 0, 0, 0, 0, 0,11, 0, 0,12, 0, 0, 0, 0 }, // 10 state can match { /$ | // | /* }
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, // 11 state can match { /* }
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, // 12 state can match { // }
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, // 13 state can match { ;$ }
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,15, 0 }, // 14 state can match { <$ | <= }
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, // 15 state can match { <=$ }
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,17, 0 }, // 16 state can match { =$ | == }
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, // 17 state can match { ==$ }
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,19, 0 }, // 18 state can match { >$ | >= }
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }  // 19 state can match { >=$ }
};

// The SYM_Accept table identifies which states are
// accepting states and which keyword they produce.
const int SYM_Accept[] = {
        0,  //  0
        0,  //  1
        1,  //  2 ”
        2,  //  3 #
        3,  //  4 (
        4,  //  5 )
        5,  //  6 *
        6,  //  7 */
        7,  //  8 +
        8,  //  9 –
        9,  // 10 /
        10, // 11 /*
        11, // 12 //
        12, // 13 ;
        13, // 14 <
        14, // 15 <=
        15, // 16 =
        16, // 17 ==
        17, // 18 >
        18  // 19 >=
};

// clang-format on
#endif // ASCII_SYM_H_
