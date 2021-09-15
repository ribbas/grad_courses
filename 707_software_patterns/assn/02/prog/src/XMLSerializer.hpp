#include <fstream>
#include <ios>
#include <string>

#include "Node.hpp"

class XMLSerializer {
private:
    int indentationLevel;
    std::fstream file;

    virtual void prettyIndentation();

public:
    XMLSerializer(const std::string& filename)
        : indentationLevel(0), file(filename.c_str(), std::ios_base::out) {}
    ~XMLSerializer() {}

    virtual void serializePretty(dom::Node*);
    virtual void serializeMinimal(dom::Node*);
};
