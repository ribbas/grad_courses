#
# Requires boost regex library.
# Set the include_directories argument to the path to the root of your
# boost installation directory.  This is "./regexxp5" in my example.
# This implementation builds the regex source directly into the application
# instead of linking a separate libboost_regex.so.
#
cmake_minimum_required(VERSION 3.12)
project(Patterns)

FIND_PACKAGE(Boost COMPONENTS regex)

if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})

	add_executable(Patterns Test.cpp)
	target_sources(Patterns PUBLIC
		Attr.cpp
		Attr.hpp
		Document.cpp
		Document.hpp
		Element.cpp
		Element.hpp
		NamedNodeMap.cpp
		NamedNodeMap.hpp
		Node.cpp
		Node.hpp
		NodeList.hpp
		Test.cpp
		Text.cpp
		Text.hpp
		XMLSerializer.cpp
		XMLSerializer.hpp
		XMLTokenizer.cpp
		XMLTokenizer.hpp
		XMLValidator.cpp
		XMLValidator.hpp
	)
	
	target_link_libraries(Patterns Boost::regex)
endif()

