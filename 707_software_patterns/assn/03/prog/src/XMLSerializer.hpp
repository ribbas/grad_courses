#include <fstream>
#include <ios>
#include <string>

#include "Node.hpp"

class XMLSerializer {
private:
    std::fstream file;
    int indentationLevel;

    virtual void prettyIndentation();

public:
    XMLSerializer(const std::string& filename)
        : indentationLevel(0), file(filename.c_str(), std::ios_base::out) {}
    ~XMLSerializer() {}

    virtual void serializePretty(dom::Node*);
    virtual void serializeMinimal(dom::Node*);
};
