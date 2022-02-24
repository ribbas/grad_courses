/*
 * fahr_convert.cpp
 *
 * Sabbir Ahmed
 * System Development in the Unix Environment (605.614)
 *
 * This file contains the implementations for convert_to_fahr
 *
 */

#include "conv_to_fahr.hpp"

double convert_to_fahr(double cent) {
    return cent * 9 / 5 + 32;
}
