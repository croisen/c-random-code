CURRENT_MKFILE := ${realpath ${dir ${firstword ${MAKEFILE_LIST}}}}

#SOURCE_HEADERS := ${wildcard ${CURRENT_MKFILE}/*.h}
#HEADERS := ${foreach HEADER,${SOURCE_HEADERS},${PREFIX}/include/${notdir ${HEADER}}}
SOURCES := ${wildcard\
	${CURRENT_MKFILE}/*.c\
}
OBJECTS := ${patsubst %.c, %.o, ${SOURCES}}

STATIC_EXE := static_002_fibonacci.exe
SHARED_EXE := shared_002_fibonacci.exe

LIBRARIES :=

install: ${STATIC_EXE} ${SHARED_EXE} | ${PREFIX}/include ${PREFIX}/bin
	cp $^ ${PREFIX}/bin

${STATIC_EXE}: ${OBJECTS}
	${CC} ${CFLAGS} -static -o ${CURRENT_MKFILE}/$@ $^ ${LDFLAGS} ${LIBRARIES}

${SHARED_EXE}: ${OBJECTS}
	${CC} ${CFLAGS} -o ${CURRENT_MKFILE}/$@ $^ ${LDFLAGS} ${LIBRARIES}

${HEADERS}: ${SOURCE_HEADERS} | ${PREFIX}/include
	cp ${CURRENT_MKFILE}/${notdir $@} ${PREFIX}/include

%.o: %.c ${HEADERS}
	${CC} ${CFLAGS} -c -o $@ $<

${PREFIX}/bin: | ${PREFIX}
	mkdir ${PREFIX}/bin

${PREFIX}/include: | ${PREFIX}
	mkdir ${PREFIX}/include

${PREFIX}:
	mkdir ${PREFIX}

.PHONY: install
