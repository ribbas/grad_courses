cmake_minimum_required(VERSION 3.13)
project(Patterns CXX)
set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -Wall -Wextra")

FIND_PACKAGE(Boost COMPONENTS regex)

if(Boost_FOUND)

	add_executable(${CMAKE_PROJECT_NAME} Test.cpp)
	target_sources(${CMAKE_PROJECT_NAME} PUBLIC
		Attr.cpp
		Document.cpp
		Element.cpp
		ElementProxy.cpp
		Iterator.cpp
		NamedNodeMap.cpp
		Node.cpp
		Test.cpp
		Text.cpp
		ValidChildren.cpp
		XMLBuilder.cpp
		XMLDirector.cpp
		XMLSerializer.cpp
		XMLTokenizer.cpp
		XMLValidator.cpp
	)
	
	target_link_libraries(${CMAKE_PROJECT_NAME} Boost::regex)
endif()
