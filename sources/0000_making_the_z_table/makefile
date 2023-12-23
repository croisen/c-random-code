CC 					= gcc
CFLAGS 				= -Wall -Wextra -Wpedantic -Werror -O3
CFLAGS_DEBUG 		= -Wall -Wextra -Wpedantic -Og -g -D'SOME_DEBUG_FLAG'

MAIN 				= making_the_z_table.c
LIBS 				= other_stuff/*.c -lmpfr -lgmp
EXEC 				= ../../build/$(patsubst %.c,%.elf,$(MAIN))


default:
	$(CC) $(CFLAGS) -o $(EXEC) $(MAIN) $(LIBS)

debug:
	$(CC) $(CFLAGS_DEBUG) -o $(EXEC) $(MAIN) $(LIBS)
