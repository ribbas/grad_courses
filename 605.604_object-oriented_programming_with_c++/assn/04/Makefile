CXX ?= g++
CFLAGS = -Wall -Wextra -fpermissive -std=c++17 -pedantic
DEP =
OBJ = myarray.o
EXE = 01

all: $(EXE)

debug: CXXFLAGS += -DDEBUG -g
debug: $(EXE)

%.o: %.c $(DEPS)
	$(CXX) -c -o $@ $< $(CFLAGS)

$(EXE): $(OBJ)
	$(CXX) -o $@ $^ $(CFLAGS)

clean:
	@rm -f *.o
	@rm -rf $(EXE)
