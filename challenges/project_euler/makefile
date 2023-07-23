EXE = project_euler.out

MAIN = $(wildcard *.c)
HEADERS = $(wildcard helper/*.h)
SOURCES = $(wildcard helper/*.c)

CC = gcc
CFLAGS = -Wall -Wpedantic -Wextra -Werror -march=native -Ofast
# No static for now, I have no static libraries :(
LIBS = -lm -lssl -lcrypto -lgmp

all: clean $(EXE)

$(EXE): $(MAIN) $(HEADERS) $(SOURCES)
	@echo "This program depends on the following libraries:"
	@echo "-lm: C Math Library"
	@echo "-lgmp: GNU Big Arithmetic Library"
	@echo "-lssl, -lcrypto: OpenSSL Lib"
	@echo "Now compiling the main program..."
	@$(CC) $(CFLAGS) -o build/$(EXE) $(MAIN) $(SOURCES) $(LIBS)
	@echo "Done! Program is now in build/$(EXE)"

clean:
	@echo "Cleaning the build directory"
	@-rm -f build/$(EXE)
