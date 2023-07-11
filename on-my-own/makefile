CC = gcc
CFLAGS = -Wall -Wpedantic -Wextra -Werror -march=native -Ofast --static

all: clean tic_tac_toe munchausen making_the_z_table

tic_tac_toe:
	$(CC) $(CFLAGS) -o _build/tic_tac_toe.out c/tic_tac_toe.c

munchausen:
	$(CC) $(CFLAGS) -o _build/munchausen.out  c/munchausen.c -lm

making_the_z_table:
	$(CC) $(CFLAGS) -o _build/making_the_z_table.out c/making_the_z_table.c -lmpfr -lgmp

clean:
	-rm -f -v _build/*
