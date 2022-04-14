/*
 * ID_List.cpp
 * Allyn Shell
 * July 2019
 *
 * Modified by:
 * Sabbir Ahmed
 * April 2022
 *
 * The ID_List class provides list functions
 * addID, dropID, matchLists, diffList
 * inList, std::ostream << of List
 *
 */

#include "ID_List.h"

const unsigned char ID_List::addMask[6] = {1, 2, 4, 8, 16, 32}; // | to add
const unsigned char ID_List::dropMask[6] = {254, 253, 251,
                                            247, 239, 223}; // & to drop

void ID_List::clear() {
    for (int i = 0; i < 10; ++i)
        list[i] = 0;
}

void ID_List::addID(const std::string id) {
    int row = (int)id[1] - (int)'0';
    int col = (int)id[0] - (int)'A';
    addID(row, col);
}

void ID_List::addID(const int row, const int col) {
    list[row] = list[row] | addMask[col];
}

void ID_List::dropID(const std::string id) {
    int row = (int)id[1] - (int)'0';
    int col = (int)id[0] - (int)'A';
    dropID(row, col);
}

void ID_List::dropID(const int row, const int col) {
    list[row] = list[row] & dropMask[col];
}

bool ID_List::contains(const std::string id) {
    int row = (int)id[1] - (int)'0';
    int col = (int)id[0] - (int)'A';
    return contains(row, col);
}

bool ID_List::contains(const int row, const int col) {
    return (list[row] & addMask[col]) > 0;
}

ID_List ID_List::operator&(const ID_List& rtlst) {
    ID_List retList;
    for (int row = 0; row < 10; ++row) {
        retList.list[row] = this->list[row] & rtlst.list[row];
    }
    return retList;
}

ID_List ID_List::operator-(const ID_List& rtlst) {
    ID_List retList;
    for (int row = 0; row < 10; ++row) {
        retList.list[row] = this->list[row] & ~rtlst.list[row];
    }
    return retList;
}

std::ostream& operator<<(std::ostream& os, const ID_List& lst) {
    os << "{";
    bool empty = true;
    for (int r = 0; r < 10; ++r) {
        unsigned char row = lst.list[r];
        for (int col = 0; col < 6; ++col) {
            if (row & ID_List::addMask[col]) {
                if (empty)
                    empty = false;
                else
                    os << ',';
                os << ' ' << (char)('A' + col) << r;
            }
        }
    }
    if (empty)
        os << " EMPTY";
    os << " }";
    return os;
}

std::vector<std::string> ID_List::getList() {
    if (!idVec.size()) {
        for (int r = 0; r < 10; ++r) {
            unsigned char row = list[r];
            for (int col = 0; col < 6; ++col) {
                if (row & addMask[col]) {
                    std::string item(1, (char)('A' + col));
                    item += std::to_string(r);
                    idVec.push_back(item);
                }
            }
        }
    }
    return idVec;
}
