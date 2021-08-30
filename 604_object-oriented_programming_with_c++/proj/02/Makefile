CXX ?= g++
CXXFLAGS = -Wall -Wextra -fpermissive -std=c++17 -pedantic
SRC = rng.cpp customer.cpp station.cpp simulation.cpp proj2.cpp
OBJ = $(SRC:.cpp=.o)
EXE = proj2

all: $(EXE)

verbose: CXXFLAGS += -DVERBOSE -g
verbose: $(EXE)

%.o: %.cpp %.hpp
	$(CXX) -c -o $@ $< $(CXXFLAGS)

$(EXE): $(OBJ)
	$(CXX) -o $@ $^ $(CXXFLAGS)

memcheck: $(EXE)
	valgrind ./$(EXE)

clean:
	@rm -f *.o
	@rm -rf $(EXE)
