#
# Requires boost regex library.
# Set the include_directories argument to the path to the root of your
# boost installation directory.  This is "./regexxp5" in my example.
# This implementation builds the regex source directly into the application
# instead of linking a separate libboost_regex.so.
#
cmake_minimum_required (VERSION 3.12)
project (Patterns)

add_definitions(-DBOOST_REGEX_STANDALONE)
include_directories(regexpp5)
add_executable(Patterns Test.C)
target_sources(Patterns PUBLIC
	Attr.C
	Attr.H
	Builder.C
	Builder.H
	Director.C
	Director.H
	Document.C
	Document.H
	Element.C
	Element.H
	NamedNodeMap.C
	NamedNodeMap.H
	Node.C
	Node.H
	NodeList.H
	Test.C
	Text.C
	Text.H
	XMLSerializer.C
	XMLSerializer.H
	XMLTokenizer.C
	XMLTokenizer.H
	XMLValidator.C
	XMLValidator.H
	ValidChildren.C
	ValidChildren.H
	WhitespaceStrategy.H
	regexpp5/libs/regex/src/posix_api.cpp
	regexpp5/libs/regex/src/regex.cpp
	regexpp5/libs/regex/src/regex_debug.cpp
	regexpp5/libs/regex/src/static_mutex.cpp
	regexpp5/libs/regex/src/wide_posix_api.cpp
	)
