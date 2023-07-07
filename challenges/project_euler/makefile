EXE = project_euler.out
SOURCE = main_file.c

CC = gcc
CFLAGS = -Wall -Wpedantic -Werror -march=native -O3 --static
LIBS = -lm

all:
	@echo "Cleaning the build directory"
	@echo "Now compiling the main program"
	$(CC) $(CFLAGS) -o build/$(EXE) $(SOURCE) $(LIBS)
	@echo "Done! Program is now in build/$(EXE)"

clean:
	-rm -f build/$(EXE)
