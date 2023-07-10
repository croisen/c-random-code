CC = gcc
CFLAGS = -Wall -Wpedantic -Wextra -Werror -march=native -Ofast --static

EXE_MUN = ./_build/munchausen.out
EXE_MZT = ./_build/making_the_z_table.out
EXE_TTT = ./_build/tic_tac_toe.out

SOURCE_MUN = ./c/munchausen.c
SOURCE_MZT = ./c/making_the_z_table.c
SOURCE_TTT = ./c/tic_tac_toe.c

all: clean tic_tac_toe munchausen making_the_z_table

tic_tac_toe:
	$(CC) $(CFLAGS) -o $(EXE_TTT) $(SOURCE_TTT)

munchausen:
	$(CC) $(CFLAGS) -o $(EXE_MUN) $(SOURCE_MUN) -lm

making_the_z_table:
	$(CC) $(CFLAGS) -o $(EXE_MZT) $(SOURCE_MZT)

clean:
	-rm -f -v _build/*
