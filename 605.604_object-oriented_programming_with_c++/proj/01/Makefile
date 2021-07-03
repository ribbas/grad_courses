CXX = g++
CFLAGS = -Wall -fpermissive
DEP = item.hpp vendingmachine.hpp wallet.hpp
OBJ = item.o vendingmachine.o wallet.o proj1.o
EXE = proj1

all: $(EXE)

%.o: %.c $(DEPS)
	@$(CXX) -c -o $@ $< $(CFLAGS)

$(EXE): $(OBJ)
	@$(CXX) -o $@ $^ $(CFLAGS)

clean:
	@rm -f *.o
	@rm -rf $(EXE)
