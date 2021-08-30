CXX ?= g++
CFLAGS = -Wall -Wextra -fpermissive -std=c++17 -pedantic
DEP = date.hpp
OBJ = date.o 01.o
EXE = 01

all: $(EXE)

debug: CXXFLAGS += -DDEBUG -g
debug: $(EXE)

%.o: %.cpp $(DEPS)
	$(CXX) -c -o $@ $< $(CFLAGS)

$(EXE): $(OBJ)
	$(CXX) -o $@ $^ $(CFLAGS)

clean:
	@rm -f *.o
	@rm -rf $(EXE)
