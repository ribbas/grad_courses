// ID_List.h
// by Allyn Shell
// July 2019
// the ID_List class provides list functions
// addID, dropID, matchLists, diffList
// inList, ostream << of List

#ifndef ID_LIST_H
#define ID_LIST_H

#include <ostream>
#include <string>

using namespace std;

class ID_List {
    static const unsigned char addMask[6];  // value of bit to represent ID
    static const unsigned char dropMask[6]; // complement of addMask

    // each of low order 6 bits in a byte represents a column
    // each byte represents a row
    unsigned char list[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

public:
    ID_List() {}
    ~ID_List() {}
    int size();
    ID_List& operator=(const ID_List& rtlst) = default;

    void clear();

    void addID(const string ID);
    void addID(const int row, const int col);

    void dropID(const string ID);
    void dropID(const int row, const int col);

    bool contains(const string ID);
    bool contains(const int row, const int col);

    // gives list of IDs that appear in both lists
    ID_List operator&(const ID_List& rtlst);

    // gives list of IDs that appear only in left list
    ID_List operator-(const ID_List& rtlst);

    friend ostream& operator<<(ostream& os, const ID_List& lst);
};

#endif // ID_LIST_H
