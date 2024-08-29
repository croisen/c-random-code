CURRENT_MKFILE := ${realpath ${dir ${firstword ${MAKEFILE_LIST}}}}

SOURCE_HEADERS := ${wildcard ${CURRENT_MKFILE}/*.h}
HEADERS := ${foreach HEADER,${SOURCE_HEADERS},${PREFIX}/include/${notdir ${HEADER}}}
SOURCES := ${wildcard ${CURRENT_MKFILE}/*.c}
OBJECTS := ${patsubst %.c, %.o, ${SOURCES}}

STATIC_LIB = lib_003_col_limited_printf.a
SHARED_LIB = lib_003_col_limited_printf.so

install: ${STATIC_LIB} ${SHARED_LIB} | ${PREFIX}/include ${PREFIX}/lib
	cp $^ ${PREFIX}/lib

${STATIC_LIB}: ${OBJECTS}
	${AR} rcs ${CURRENT_MKFILE}/$@ $^

${SHARED_LIB}: ${OBJECTS}
	${CC} ${CFLAGS} -shared -o ${CURRENT_MKFILE}/$@ $^ ${LDFLAGS}

${HEADERS}: ${SOURCE_HEADERS} | ${PREFIX}/include
	cp ${CURRENT_MKFILE}/${notdir $@} ${PREFIX}/include

%.o: %.c ${HEADERS}
	${CC} ${CFLAGS} -c -o $@ $<

${PREFIX}/lib: | ${PREFIX}
	mkdir ${PREFIX}/lib

${PREFIX}/include: | ${PREFIX}
	mkdir ${PREFIX}/include

${PREFIX}:
	mkdir ${PREFIX}

.PHONY: install
