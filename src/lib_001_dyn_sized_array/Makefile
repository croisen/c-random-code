CURRENT_MKFILE := ${realpath ${dir ${firstword ${MAKEFILE_LIST}}}}

SOURCE_HEADERS := ${wildcard ${CURRENT_MKFILE}/*.h}
HEADERS := ${foreach HEADER,${SOURCE_HEADERS},${PREFIX}/include/${notdir ${HEADER}}}

install: ${HEADERS} | ${PREFIX}/include

${HEADERS}: ${SOURCE_HEADERS} | ${PREFIX}/include
	cp ${CURRENT_MKFILE}/${notdir $@} ${PREFIX}/include

${PREFIX}/include: | ${PREFIX}
	mkdir ${PREFIX}/include

${PREFIX}:
	mkdir ${PREFIX}

.PHONY: install
