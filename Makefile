CC=gcc
CFLAGS=-Wall -std=c99

DEPS = board.c generator.c options.c main.c

bingo: $(DEPS) 
	$(CC) $(CFLAGS) $(DEPS) -o bingo

.PHONY: clean

clean:
	rm -rf bingo vgcore.*
