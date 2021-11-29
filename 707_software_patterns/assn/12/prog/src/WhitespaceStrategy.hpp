#ifndef WHITESPACE_STRATEGY_HPP
#define WHITESPACE_STRATEGY_HPP

#include <fstream>

class WhitespaceStrategy {
public:
    virtual ~WhitespaceStrategy() {}

    virtual void prettyIndentation(std::fstream*) = 0;
    virtual void incrementIndentation() = 0;
    virtual void decrementIndentation() = 0;
    virtual void newLine(std::fstream*) = 0;
};

#endif // WHITESPACESTRATEGY_HPP
