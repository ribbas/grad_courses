CXX ?= g++
CFLAGS = -Wall -Wextra -fpermissive -std=c++17 -pedantic
SRC = rng.cpp customer.cpp station.cpp proj2.cpp
OBJ = $(SRC:.cpp=.o)
EXE = proj2

all: $(EXE)

debug: CXXFLAGS += -DDEBUG -g
debug: $(EXE)

$(%.o): %.cpp %.hpp
	$(CXX) -c -o $@ $< $(CFLAGS)

$(EXE): $(OBJ)
	$(CXX) -o $@ $^ $(CFLAGS)

memcheck: $(EXE)
	valgrind ./$(EXE)

clean:
	@rm -f *.o
	@rm -rf $(EXE)
