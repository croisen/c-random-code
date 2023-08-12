CC = gcc
CFLAGS = -Wall -Wpedantic -Wextra -Werror -march=native -mtune=native -O3

TIC_TAC_TOE_SRC    = sources/tic_tac_toe.c
TIC_TAC_TOE_EXE    = build/tic_tac_toe.out

MUNCHAUSEN_SRC     = sources/munchausen.c
MUNCHAUSEN_EXE     = build/munchausen.out
MUNCHAUSEN_LIBS    = -lm

Z_TABLE_SRC        = sources/making_the_z_table.c
Z_TABLE_EXE        = build/making_the_z_table.out
Z_TABLE_LIBS       = -lmpfr -lgmp

PROJECT_EULER_SRC  = $(wildcard sources/project_euler_solutions/*.c)
PROJECT_EULER_EXE  = build/project_euler.out
PROJECT_EULER_MAIN = sources/project_euler.c
PROJECT_EULER_LIBS = -lm -lgmp -lcrypto -lssl

all: clean tic_tac_toe munchausen making_the_z_table project_euler
	@echo "The executables are now in the build folder"

tic_tac_toe:
	$(CC) $(CFLAGS) -o $(TIC_TAC_TOE_EXE) $(TIC_TAC_TOE_SRC)

munchausen:
	$(CC) $(CFLAGS) -o $(MUNCHAUSEN_EXE) $(MUNCHAUSEN_SRC) $(MUNCHAUSEN_LIBS)

making_the_z_table:
	$(CC) $(CFLAGS) -o $(Z_TABLE_EXE) $(Z_TABLE_SRC) $(Z_TABLE_LIBS)

project_euler:
	$(CC) $(CFLAGS) -o $(PROJECT_EULER_EXE) $(PROJECT_EULER_MAIN) $(PROJECT_EULER_SRC) $(PROJECT_EULER_LIBS)

clean:
	-rm -f build/*.out
