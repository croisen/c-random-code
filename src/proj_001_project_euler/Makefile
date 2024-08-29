CURRENT_MKFILE := ${realpath ${dir ${firstword ${MAKEFILE_LIST}}}}

#SOURCE_HEADERS := ${wildcard ${CURRENT_MKFILE}/*.h}
#HEADERS := ${foreach HEADER,${SOURCE_HEADERS},${PREFIX}/include/${notdir ${HEADER}}}
SOURCES := ${wildcard\
	${CURRENT_MKFILE}/*.c\
	${CURRENT_MKFILE}/solutions/*/*.c\
	${CURRENT_MKFILE}/utils/*.c\
}
OBJECTS := ${patsubst %.c, %.o, ${SOURCES}}

STATIC_EXE := static_001_project_euler.exe
SHARED_EXE := shared_001_project_euler.exe

LIBRARIES := -l_003_col_limited_printf

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
