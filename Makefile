ROOT_MKFILE := ${realpath ${dir ${firstword ${MAKEFILE_LIST}}}}
PREFIX := ${ROOT_MKFILE}/build

LIB_SOURCE_DIRS := ${filter %/, ${wildcard ${ROOT_MKFILE}/src/lib*/}}
PROJ_SOURCE_DIRS := ${filter %/, ${wildcard ${ROOT_MKFILE}/src/proj*/}}

AR := ar
CC := cc

CFLAGS := -Wall -Wpedantic -Wextra -O2 -g -fPIC -I${PREFIX}/include
LDFLAGS := -L${PREFIX}/lib -Wl,-rpath,${PREFIX}/lib

install: ${LIB_SOURCE_DIRS} ${PROJ_SOURCE_DIRS} | ${PREFIX}/bin

${PROJ_SOURCE_DIRS}: ${LIB_SOURCE_DIRS}
	${MAKE} -C $@ install

${LIB_SOURCE_DIRS}:
	${MAKE} -C $@ install

${PREFIX}/bin: | ${PREFIX}/lib ${PREFIX}/include ${PREFIX}
	mkdir ${PREFIX}/bin

${PREFIX}/lib: | ${PREFIX}
	mkdir ${PREFIX}/lib

${PREFIX}/include: | ${PREFIX}
	mkdir ${PREFIX}/include

${PREFIX}:
	mkdir ${PREFIX}

.PHONY : install ${LIB_SOURCE_DIRS} ${PROJ_SOURCE_DIRS}
.EXPORT_ALL_VARIABLES:
