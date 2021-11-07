#ifndef TEST_HPP
#define TEST_HPP

#include "../Attr.hpp"
#include "../Document.hpp"
#include "../Element.hpp"
#include "../Text.hpp"
#include "../XMLBuilder.hpp"
#include "../XMLDirector.hpp"
#include "../XMLSerializer.hpp"
#include "../XMLTokenizer.hpp"
#include "../XMLValidator.hpp"
#include <iostream>

inline void printUsage() {
    printf("Usage:\n");
    printf("\tTest b [file1] [file2]\n");
    printf("\tTest c [file]\n");
    printf("\tTest i [file]\n");
    printf("\tTest t [file] ...\n");
    printf("\tTest s [file1] [file2]\n");
    printf("\tTest v [file]\n");
}

void testTokenizer(int, char**);
void testSerializer(int, char**);
void testValidator(int, char**);
void testBuilder(int, char**);
void testIterator(int, char**);
void testChainOfResponsibility(int, char**);

#endif // TEST_HPP
