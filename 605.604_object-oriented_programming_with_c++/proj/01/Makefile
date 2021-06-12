CXX = g++
CFLAGS = -Wall -fpermissive
DEP = item.hpp vendingmachine.hpp
OBJ = item.o vendingmachine.o proj.o
EXE = proj

all: $(EXE)

%.o: %.c $(DEPS)
	@$(CXX) -c -o $@ $< $(CFLAGS)

$(EXE): $(OBJ)
	@$(CXX) -o $@ $^ $(CFLAGS)

clean:
	@rm -f *.o
	@rm -rf $(EXE)
