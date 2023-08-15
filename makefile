CC = gcc
CFLAGS = -Wall -Wpedantic -Wextra -Werror -march=native -mtune=native -O3

LEZI_SRC           = sources/lezi_player.c
LEZI_EXE           = build/lezi.out
LEZI_LIBS          = -lraylib

MUNCHAUSEN_SRC     = sources/munchausen.c
MUNCHAUSEN_EXE     = build/munchausen.out
MUNCHAUSEN_LIBS    = -lm

PROJECT_EULER_SRC  = $(wildcard sources/project_euler_solutions/*.c)
PROJECT_EULER_EXE  = build/project_euler.out
PROJECT_EULER_MAIN = sources/project_euler.c
PROJECT_EULER_LIBS = -lm -lgmp -lcrypto -lssl

SNAKE_GAME_EXE     = build/snake_game.out
SNAKE_GAME_SRC     = sources/snake_game.c
SNAKE_GAME_LIBS    = -lraylib

TIC_TAC_TOE_SRC    = sources/tic_tac_toe.c
TIC_TAC_TOE_EXE    = build/tic_tac_toe.out

Z_TABLE_SRC        = sources/making_the_z_table.c
Z_TABLE_EXE        = build/making_the_z_table.out
Z_TABLE_LIBS       = -lmpfr -lgmp

all: clean tic_tac_toe munchausen making_the_z_table project_euler snake_game lezi_player
	@echo "The executables are now in the build folder"

lezi_player:
	$(CC) $(CFLAGS) -o $(LEZI_EXE) $(LEZI_SRC) $(LEZI_LIBS)

munchausen:
	$(CC) $(CFLAGS) -o $(MUNCHAUSEN_EXE) $(MUNCHAUSEN_SRC) $(MUNCHAUSEN_LIBS)

making_the_z_table:
	$(CC) $(CFLAGS) -o $(Z_TABLE_EXE) $(Z_TABLE_SRC) $(Z_TABLE_LIBS)

project_euler:
	$(CC) $(CFLAGS) -o $(PROJECT_EULER_EXE) $(PROJECT_EULER_MAIN) $(PROJECT_EULER_SRC) $(PROJECT_EULER_LIBS)

snake_game:
	$(CC) $(CFLAGS) -o $(SNAKE_GAME_EXE) $(SNAKE_GAME_SRC) $(SNAKE_GAME_LIBS)

tic_tac_toe:
	$(CC) $(CFLAGS) -o $(TIC_TAC_TOE_EXE) $(TIC_TAC_TOE_SRC)

clean:
	-rm -f build/*.out
