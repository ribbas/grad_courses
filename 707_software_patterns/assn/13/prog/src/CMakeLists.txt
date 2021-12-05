cmake_minimum_required(VERSION 3.19)
project(Patterns CXX)
set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -Wall -Wextra")

FIND_PACKAGE(Boost COMPONENTS regex)

if(Boost_FOUND)

	add_executable(${CMAKE_PROJECT_NAME} test/Test.cpp)
	target_sources(${CMAKE_PROJECT_NAME} PUBLIC
		Attr.cpp
		Document.cpp
		DOMException.cpp
		Element.cpp
		Iterator.cpp
		NamedNodeMap.cpp
		Node.cpp
		Text.cpp
		ValidChildren.cpp
		XMLBuilder.cpp
		XMLDirector.cpp
		Flyweight.cpp
		XMLFacade.cpp
		XMLInterpreter.cpp
		XMLSerializer.cpp
		XMLTokenizer.cpp
		XMLValidator.cpp
		test/Test.cpp
		test/TestBuilder.cpp
		test/TestInterpreter.cpp
		test/TestIterator.cpp
		test/TestSerializer.cpp
		test/TestTokenizer.cpp
		test/TestValidator.cpp
	)

	target_link_libraries(${CMAKE_PROJECT_NAME} Boost::regex)
endif()
