CC=gcc
CFLAGS=-lncurses -std=c99

DEPS = *.h *.c

bingo: $(DEPS) 
	$(CC) $(CFLAGS) $(DEPS) -o bingo

.PHONY: clean

clean:
	rm -rf bingo vgcore.*
