CC				= gcc
OPTS			= -Wall -Wpedantic -Wextra -Werror
RELEASE_OPTS	= -O3 -s
DEBUG_OPTS		= -Og -g

TOURNEY_IMPL	= -D'___0003_CROI_C_RANDOM_CODE_IMPL___'

ALL				= ${patsubst %.c,%.exe,${wildcard *.c}}

default: all

clean:
	-rm -fv *.exe

${ALL}:
	${CC} ${OPTS} ${RELEASE_OPTS} ${TOURNEY_IMPL}\
		-o $@ ${patsubst %.exe,%.c,$@}

${patsubst %,%_DEBUG,${ALL}}:
	${CC} ${OPTS} ${RELEASE_OPTS} ${TOURNEY_IMPL}\
		-o ${patsubst %.exe_DEBUG,%.exe,$@} ${patsubst %.exe_DEBUG,%.c,$@}

all: ${ALL}
debug: ${patsubst %,%_DEBUG,${ALL}}
.PHONY: all debug
