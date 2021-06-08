CXX = g++
CFLAGS = -Wall -fpermissive
DEP = date.h
OBJ = date.o 01.o
EXE = 01

all: $(EXE)

%.o: %.c $(DEPS)
	@$(CXX) -c -o $@ $< $(CFLAGS)

$(EXE): $(OBJ)
	@$(CXX) -o $@ $^ $(CFLAGS)

clean:
	@rm -f *.o
	@rm -rf $(EXE)
