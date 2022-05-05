CC = gcc
CFLAGS = -Wall -Wextra -lrt
# DEP = vm.h
OBJ = server.o client.o
EXE = server client

all: $(EXE)

# %.o: %.c
# 	$(CC) -c -o $@ $< $(CFLAGS)

$(EXE):
	$(CC) $@.c -o $@ $^ $(CFLAGS)

timeit: $(EXE)
	./$(EXE) 2> times.txt 1> /dev/null

clean:
	@rm -f *.o
	@rm -rf $(EXE)
