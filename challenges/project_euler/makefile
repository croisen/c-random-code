EXE = project_euler.out

MAIN = $(wildcard *.c)
HEADERS = $(wildcard helper/*.h)
SOURCES = $(wildcard helper/*.c)

CC = gcc
CFLAGS = -Wall -Wpedantic -Wextra -Werror -march=native -Ofast --static
LIBS = -lm -lgmp

all: clean $(EXE)

$(EXE): $(MAIN) $(HEADERS) $(SOURCES)
	@echo "Now compiling the main program"
	@echo "Depending on the following headers: $(HEADERS)"
	@echo "Depending on the following sources: $(SOURCES)"
	$(CC) $(CFLAGS) -o build/$(EXE) $(MAIN) $(SOURCES) $(LIBS)
	@echo "Done! Program is now in build/$(EXE)"

clean:
	@echo "Cleaning the build directory"
	-rm -f build/$(EXE)
