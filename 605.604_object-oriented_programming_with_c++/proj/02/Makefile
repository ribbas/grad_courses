CXX ?= g++
CFLAGS = -Wall -Wextra -fpermissive -std=c++17 -pedantic
DEP = rng.hpp
OBJ = rng.o
EXE = rng

all: $(EXE)

debug: CXXFLAGS += -DDEBUG -g
debug: $(EXE)

%.o: %.cpp %.hpp
	$(CXX) -c -o $@ $< $(CFLAGS)

$(EXE): $(OBJ)
	$(CXX) -o $@ $^ $(CFLAGS)

memcheck: $(EXE)
	valgrind ./$(EXE)

clean:
	@rm -f *.o
	@rm -rf $(EXE)
