CC = gcc
CFLAGS = -Wall -Wextra -lrt
EXE = notifier listener

all: $(EXE)

$(EXE):
	$(CC) $@.c -o $@ $^ $(CFLAGS)

clean:
	@rm -f *.o
	@rm -rf $(EXE)
