#ifndef WHITESPACESTRATEGY_H
#define WHITESPACESTRATEGY_H

#include <fstream>

//
// Whitespace Strategy
//
class WhitespaceStrategy {
public:
    virtual void prettyIndentation(std::fstream*) = 0;
    virtual void incrementIndentation() = 0;
    virtual void decrementIndentation() = 0;
    virtual void newLine(std::fstream*) = 0;
    virtual ~WhitespaceStrategy() {}
};

#endif // WHITESPACESTRATEGY_H
