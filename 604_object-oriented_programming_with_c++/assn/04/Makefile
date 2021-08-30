CXX ?= g++
CFLAGS = -Wall -Wextra -fpermissive -std=c++17 -pedantic
EXE = myarray counter

all: $(EXE)

debug: CXXFLAGS += -DDEBUG -g
debug: $(EXE)

%.o: %.cpp %.hpp
	$(CXX) -c -o $@ $< $(CFLAGS)

counter: counter.o
	$(CXX) -o $@ $^ $(CFLAGS)

myarray: myarray.o
	$(CXX) -o $@ $^ $(CFLAGS)

clean:
	@rm -f *.o
	@rm -rf $(EXE)
