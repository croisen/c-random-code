EXE = project_euler.out
SOURCE = main_file.c

CC = gcc
CFLAGS = -Wall -Wpedantic -Werror -march=native -Ofast --static
LIBS = -lm

LOCAL_HEADERS = $(wildcard helper/*.h)

all: $(LOCAL_HEADERS)
	@echo "Cleaning the build directory"
	@echo "Now compiling the main program"
	@echo "Depending on the following headers: $(LOCAL_HEADERS)"
	$(CC) $(CFLAGS) -o build/$(EXE) $(SOURCE) $(LIBS)
	@echo "Done! Program is now in build/$(EXE)"

clean:
	-rm -f build/$(EXE)
