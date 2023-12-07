CC 					= gcc
CFLAGS 				= -Wall -Wextra -Wpedantic -Werror -O3
CFLAGS_DEBUG 		= -Wall -Wextra -Wpedantic -Og -g -D'SOME_DEBUG_FLAG'

MAIN 				= project_euler.c
LIBS 				= extras/*.c -lm -lgmp -lcrypto -lssl
EXEC 				= ../../build/$(patsubst %.c,%.elf,$(MAIN))


default:
	$(CC) $(CFLAGS) -o $(EXEC) $(MAIN) $(LIBS)

debug:
	$(CC) $(CFLAGS_DEBUG) -o $(EXEC) $(MAIN) $(LIBS)
