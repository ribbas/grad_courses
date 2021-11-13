#include "Command.hpp"
#include "Node.hpp"
#include "XMLBuilder.hpp"
#include "XMLDirector.hpp"
#include "XMLSerializer.hpp"

void ParseFileCommand::execute() {
    dom::Document* document = new Document_Impl;
    XMLBuilder* builder = new XMLBuilder();

    XMLDirector director(builder, fileName);
    rootNode = document;
}

void SerializeCommand::execute() {
    XMLSerializer xmlSerializer(file);
    xmlSerializer.serializePretty(node);
}

void AddAttributeCommand::execute() {
    node->setAttribute(attrName, attrValue);
}