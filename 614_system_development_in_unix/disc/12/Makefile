CC = gcc
CFLAGS = -Wall -Wextra
# DEP = vm.h
OBJ = msgq_send.o msgq_recv.o
EXE = msgq_send msgq_recv

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
