#include "SS_Cell.h"

// Table of Cells constructor
// sets ID for each cell
TableOfCells::TableOfCells() {

    if (!SS_Cell::TOC) {
        SS_Cell::TOC = this;
    }

    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 6; ++j) {
            cell[i][j].setID(i, j);
        }
    }

    badCell.id = "XX";
    badCell.row = -1;
    badCell.col = -1;
    badCell.error = true;
    badCell.kind = DEAD;
}

SS_Cell* TableOfCells::getCell(const std::string id) {
    if (id.length() != 2) {
        return &badCell;
    }
    int row = (int)id[1] - (int)'0';
    int col = (int)id[0] - (int)'A';
    return getCell(col, row);
}

SS_Cell* TableOfCells::getCell(CellArrayColumn ac, int row) {
    int col = (int)ac;
    return getCell(col, row);
}

SS_Cell* TableOfCells::getCell(char ch, int row) {
    int col = (int)ch - (int)'A';
    return getCell(col, row);
}

SS_Cell* TableOfCells::getCell(int col, int row) {
    if (row < 0 || row > 9) {
        return &badCell;
    }
    if (col < 0 || col > 5) {
        return &badCell;
    }
    return &cell[row][col];
}

void TableOfCells::printTable(std::ostream& os) {
    const char tab = '\t'; // assumed to be 8 spaces
    const char dash[] = "-------+";
    os << tab;
    os << "|   A" << tab << "|   B" << tab;
    os << "|   C" << tab << "|   D" << tab;
    os << "|   E" << tab << "|   F" << tab;
    os << "|" << std::endl;
    for (int i = 0; i < 10; ++i) {
        os << ' ' << dash << dash << dash << dash << dash << dash << dash
           << std::endl;
        os << "    " << i << tab << '|';
        for (int j = 0; j < 6; ++j) {
            os << cell[i][j].display;
            if (cell[i][j].display.size() < 7) {
                os << tab;
            }
            os << '|';
        }
        os << std::endl;
    }
    os << ' ' << dash << dash << dash << dash << dash << dash << dash
       << std::endl;
    os << std::endl;
}
