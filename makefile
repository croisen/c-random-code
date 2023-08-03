CC = gcc
CFLAGS = -Wall -Wpedantic -Wextra -Werror -march=native -O3

PROJECT_EULER_SRC  = $(wildcard sources/solutions/*.c)
PROJECT_EULER_MAIN = sources/project_euler.c
PROJECT_EULER_LIBS = -lm -lgmp -lcrypto -lssl

all: clean tic_tac_toe munchausen making_the_z_table project_euler

tic_tac_toe:
	$(CC) $(CFLAGS) -o build/tic_tac_toe.out sources/tic_tac_toe.c

munchausen:
	$(CC) $(CFLAGS) -o build/munchausen.out  sources/munchausen.c -lm

making_the_z_table:
	$(CC) $(CFLAGS) -o build/making_the_z_table.out sources/making_the_z_table.c -lmpfr -lgmp

project_euler:
	$(CC) $(CFLAGS) -o build/project_euler.out $(PROJECT_EULER_SRC) $(PROJECT_EULER_MAIN) $(PROJECT_EULER_LIBS)

clean:
	-rm -f -v build/*
