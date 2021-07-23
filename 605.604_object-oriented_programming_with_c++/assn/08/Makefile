CXX ?= g++
CFLAGS = -Wall -Wextra -fpermissive -std=c++17 -pedantic
DEP = templatearray.hpp date.hpp
OBJ = templatearray.o date.o 08.o 
EXE = 08

all: $(EXE)

debug: CXXFLAGS += -DDEBUG -g
debug: $(EXE)

%.o: %.cpp %.hpp
	$(CXX) -c -o $@ $< $(CFLAGS)

$(EXE): $(OBJ)
	$(CXX) -o $@ $^ $(CFLAGS)

clean:
	@rm -f *.o
	@rm -rf $(EXE)
