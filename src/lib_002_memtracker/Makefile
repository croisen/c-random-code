CURRENT_MKFILE := ${realpath ${dir ${firstword ${MAKEFILE_LIST}}}}

HEADERS := ${wildcard ${CURRENT_MKFILE}/*.h}

install: ${HEADERS} | ${PREFIX}/include ${PREFIX}/lib
	echo ${CURRENT_MKFILE}

%.o: %.c
	${CC} ${CFLAGS} -c -o $@ $<

${HEADERS}: | ${PREFIX}/include
	cp $@ ${PREFIX}/include

${PREFIX}/lib: | ${PREFIX}
	mkdir ${PREFIX}/lib

${PREFIX}/include: | ${PREFIX}
	mkdir ${PREFIX}/include

${PREFIX}:
	mkdir ${PREFIX}

.PHONY: install
