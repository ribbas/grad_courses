CC = gcc
CFLAGS = -Wall -Wextra -lrt
EXE = server listener

all: $(EXE)


$(EXE):
	$(CC) $@.c -o $@ $^ $(CFLAGS)

timeit: $(EXE)
	./$(EXE) 2> times.txt 1> /dev/null

clean:
	@rm -f *.o
	@rm -rf $(EXE)
