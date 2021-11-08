#include "Test.hpp"

void testTokenizer(int argc, char** argv) {

    dom::Document* document = new Document_Impl;

    dom::Element* element = document->createElement("NewElement");
    dom::Text* text = document->createTextNode("Text Data");
    dom::Attr* attr = document->createAttribute("NewAttribute");

    printf("Element Tag = '%s'\n", element->getTagName().c_str());
    printf("Text Data = '%s'\n", text->getValue().c_str());
    printf("Attr Name = '%s'\n", attr->getName().c_str());

    element->setAttributeNode(attr);
    printf("Element attribute '%s'='%s'\n", element->getTagName().c_str(),
           element->getAttribute("NewAttribute").c_str());

    delete element;
    delete text;
    delete document;

    for (int i = 2; i < argc; i++) {
        XMLTokenizer tokenizer(argv[i]);

        XMLTokenizer::XMLToken* token = nullptr;

        printf("File:  '%s'\n", argv[i]);

        do {
            delete token;
            token = tokenizer.getNextToken();

            printf("\tLine %d:  %s = '%s'\n", tokenizer.getLineNumber(),
                   token->toString(),
                   token->getToken().size() == 0 ? ""
                                                 : token->getToken().c_str());

        } while (token->getTokenType() != XMLTokenizer::XMLToken::NULL_TOKEN);

        delete token;
    }
}
