CURRENT_MKFILE := ${realpath ${dir ${firstword ${MAKEFILE_LIST}}}}

SOURCES := ${wildcard ${CURRENT_MKFILE}/*.c}
OBJECTS := ${patsubst %.c, %.o, ${SOURCES}}

STATIC_EXE := static_z_table.exe
SHARED_EXE := shared_z_table.exe

install: ${STATIC_EXE} ${SHARED_EXE} | ${PREFIX}/bin
	cp $^ ${PREFIX}/bin

${STATIC_EXE}: ${OBJECTS}
	${CC} ${CFLAGS} -static -o $@ $^ ${LDFLAGS}

${SHARED_EXE}: ${OBJECTS}
	${CC} ${CFLAGS} -o $@ $^ ${LDFLAGS}

%.o: %.c
	${CC} ${CFLAGS} -c -o $@ $<

${PREFIX}/bin: | ${PREFIX}
	mkdir ${PREFIX}/bin

${PREFIX}:
	mkdir ${PREFIX}

.PHONY: install
