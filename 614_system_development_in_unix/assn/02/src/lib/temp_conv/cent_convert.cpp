/*
 * cent_convert.cpp
 *
 * Sabbir Ahmed
 * System Development in the Unix Environment (605.614)
 *
 * This file contains the implementations for convert_to_cent
 *
 */

#include "conv_to_cent.hpp"

double convert_to_cent(double fahr) {
    return (fahr - 32) * 5 / 9;
}
