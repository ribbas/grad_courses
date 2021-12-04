#ifndef DOM_EXCEPTION_HPP
#define DOM_EXCEPTION_HPP

#include <string>

namespace dom {

class DOMException {
private:
    int reason;
    std::string description;

public:
    DOMException(int r, const std::string& d);

    virtual ~DOMException();

    int getReason();
    const std::string& getDescription();

    static const int WRONG_DOCUMENT_ERR = 0;
    static const int INUSE_ATTRIBUTE_ERR = 1;
    static const int INDEX_SIZE_ERR = 2;
    static const int NOT_FOUND_ERR = 3;
    static const int NO_MODIFICATION_ALLOWED_ERR = 4;
    static const int INVALID_CHARACTER_ERR = 5;
    static const int HIERARCHY_REQUEST_ERR = 6;
};
} // namespace dom

#endif