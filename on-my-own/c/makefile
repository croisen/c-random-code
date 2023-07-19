CC = gcc
CFLAGS = -Wall -Wpedantic -Wextra -Werror -march=native -Ofast --static

all: clean tic_tac_toe munchausen making_the_z_table

tic_tac_toe:
	$(CC) $(CFLAGS) -o build/tic_tac_toe.out sources/tic_tac_toe.c

munchausen:
	$(CC) $(CFLAGS) -o build/munchausen.out  sources/munchausen.c -lm

making_the_z_table:
	$(CC) $(CFLAGS) -o build/making_the_z_table.out sources/making_the_z_table.c -lmpfr -lgmp

clean:
	-rm -f -v build/*
