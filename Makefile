ROOT_MKFILE := ${realpath ${dir ${firstword ${MAKEFILE_LIST}}}}
PREFIX := ${ROOT_MKFILE}/build

SUB_SOURCE_DIRS := ${filter %/, ${wildcard ${ROOT_MKFILE}/src/*/}}

AR := ar
CC := cc

CFLAGS := -Wall -Wpedantic -Wextra -O2 -g -fPIC -I${PREFIX}/include
LDFLAGS := -L${PREFIX}/lib -Wl,-rpath,${PREFIX}/lib

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
.EXPORT_ALL_VARIABLES:
