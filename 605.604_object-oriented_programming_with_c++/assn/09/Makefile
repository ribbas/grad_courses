CXX ?= g++
CFLAGS = -Wall -Wextra -fpermissive -std=c++17 -pedantic
EXE = 01

all: $(EXE)

debug: CXXFLAGS += -DDEBUG -g
debug: $(EXE)

%.o: %.cpp %.hpp
	$(CXX) -c -o $@ $< $(CFLAGS)

01: 01.o movierank.o
	$(CXX) -o $@ $^ $(CFLAGS)

memcheck: $(EXE)
	valgrind ./$(EXE)

clean:
	@rm -f *.o
	@rm -rf $(EXE)
