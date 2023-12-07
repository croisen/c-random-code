CC 					= gcc
CFLAGS 				= -Wall -Wextra -Wpedantic -Werror -O3 -D'SOME_DEBUG_FLAG'
CFLAGS_DEBUG 		= -Wall -Wextra -Wpedantic -Og -g -D'SOME_DEBUG_FLAG'

MAIN 				= dyn_arr.c
OUT 				= ../../custom_objects/0001_$(patsubst %.c,%.o,$(MAIN))


default:
	$(CC) $(CFLAGS) -c $(MAIN) -o $(OUT)

debug:
	$(CC) $(CFLAGS_DEBUG) -c $(MAIN) -o $(OUT)
