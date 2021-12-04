#include "XMLFacade.hpp"
#include "XMLBuilder.hpp"
#include "XMLDirector.hpp"
#include "XMLSerializer.hpp"
#include "XMLTokenizer.hpp"
#include "XMLValidator.hpp"
#include <iostream>

dom::Document* XMLFacade::document = new Document_Impl;

void XMLFacade::setDocument(dom::Document* document_) {
    document = document_;
}

void XMLFacade::serialize(const std::string& fileName, bool minimal) {

    std::fstream* file = nullptr;
    XMLSerializer xmlSerializer(
        file = new std::fstream(fileName.c_str(), std::ios_base::out));

    if (minimal) {
        xmlSerializer.serializeMinimal(document);
    } else {
        xmlSerializer.serializePretty(document);
    }

    delete file;
}

void XMLFacade::parse(const std::string& fileName) {

    if (document) {
        delete document;
    }

    XMLBuilder* builder = new XMLBuilder();
    XMLDirector director(builder, fileName);
    director.construct();
    document = director.getResult();
}

void XMLFacade::tokenize(const std::string& fileName) {

    XMLTokenizer tokenizer(fileName.c_str());
    XMLTokenizer::XMLToken* token = nullptr;

    printf("File:  '%s'\n", fileName.c_str());

    do {
        delete token;
        token = tokenizer.getNextToken();

        printf("\tLine %d:  %s = '%s'\n", tokenizer.getLineNumber(),
               token->toString(),
               token->getToken().size() == 0 ? "" : token->getToken().c_str());

    } while (token->getTokenType() != XMLTokenizer::XMLToken::NULL_TOKEN);

    delete token;
}

void XMLFacade::printToStdout(dom::Node* node) {
    if (dynamic_cast<dom::Document*>(node) != 0) {
        std::cout << " (document)";
    } else if (dynamic_cast<dom::Element*>(node) != 0) {
        std::cout << " (element) "
                  << dynamic_cast<dom::Element*>(node)->getTagName();
    } else if (dynamic_cast<dom::Attr*>(node) != 0) {
        std::cout << " (attr) " << dynamic_cast<dom::Attr*>(node)->getName()
                  << ' ' << dynamic_cast<dom::Attr*>(node)->getValue();
    } else if (dynamic_cast<dom::Text*>(node) != 0) {
        std::cout << " (text) " << dynamic_cast<dom::Text*>(node)->getValue();
    }
}

void XMLFacade::iterateToStdout() {
    dom::Iterator* it = document->createIterator();
    dom::Node* currentNode;
    for (it->first(); !it->isDone(); it->next()) {

        currentNode = it->currentItem();
        std::cout << currentNode;
        printToStdout(currentNode);
        std::cout << std::endl;
    }

    delete it;
}