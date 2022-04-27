CC = gcc
CFLAGS = -Wall -Wextra
DEP = vm.h
OBJ = vm.o vm_test.o
EXE = vm

all: $(EXE)

%.o: %.c vm.h
	$(CC) -c -o $@ $< $(CFLAGS)

$(EXE): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

report: $(EXE)
	./$(EXE) 2> times.txt 1> /dev/null

clean:
	@rm -f *.o
	@rm -rf $(EXE)
