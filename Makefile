ROOT_MKFILE := ${realpath ${dir ${firstword ${MAKEFILE_LIST}}}}
PREFIX := ${ROOT_MKFILE}/build

SUB_SOURCE_DIRS := ${filter %/, ${wildcard ${ROOT_MKFILE}/src/*/}}

install: ${SUB_SOURCE_DIRS} | ${PREFIX}/bin

${SUB_SOURCE_DIRS}:
	${MAKE} -C $@ install

${PREFIX}/bin: | ${PREFIX}/lib ${PREFIX}/include ${PREFIX}
	mkdir ${PREFIX}/bin

${PREFIX}/lib: | ${PREFIX}
	mkdir ${PREFIX}/lib

${PREFIX}/include: | ${PREFIX}
	mkdir ${PREFIX}/include

${PREFIX}:
	mkdir ${PREFIX}

.PHONY : install ${SUB_SOURCE_DIRS}
