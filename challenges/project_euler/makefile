EXE = project_euler.out

MAIN = $(wildcard *.c)
HEADERS = $(wildcard helper/*.h)
SOURCES = $(wildcard helper/*.c)

CC = gcc
CFLAGS = -Wall -Wpedantic -Wextra -Werror -march=native -Ofast --static
LIBS = -lm -lgmp

all: clean $(EXE)

$(EXE): $(MAIN) $(HEADERS) $(SOURCES)
	@echo "This program depends on the following libraries:"
	@echo "-lm: C Math Library"
	@echo -e "-lgmp: GNU Big Arithmetic Library\n"
	@echo -e "\nNow compiling the main program\n\n"
	$(CC) $(CFLAGS) -o build/$(EXE) $(MAIN) $(SOURCES) $(LIBS)
	@echo -e "\n\nDone! Program is now in build/$(EXE)"

clean:
	@echo "Cleaning the build directory"
	-rm -f build/$(EXE)
