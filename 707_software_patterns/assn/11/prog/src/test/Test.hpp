#ifndef TEST_HPP
#define TEST_HPP

#include "../Attr.hpp"
#include "../Document.hpp"
#include "../Element.hpp"
#include "../Text.hpp"
#include "../XMLBuilder.hpp"
#include "../XMLDirector.hpp"
#include "../XMLInvoker.hpp"
#include "../XMLSerializer.hpp"
#include "../XMLTokenizer.hpp"
#include "../XMLValidator.hpp"
#include <iostream>

inline void printUsage() {
    printf("Usage:\n");
    printf("\tTest b [file1] [file2]\n");
    printf("\tTest c [file] [file2]\n");
    printf("\tTest e [file]\n");
    printf("\tTest i [file]\n");
    printf("\tTest t [file] ...\n");
    printf("\tTest s [file1] [file2]\n");
    printf("\tTest v [file]\n");
}

void testBuilder(int, char**);
void testCommand(int, char**);
void testChainOfResponsibility(int, char**);
void testIterator(int, char**);
void testSerializer(int, char**);
void testTokenizer(int, char**);
void testValidator(int, char**);

#endif // TEST_HPP
