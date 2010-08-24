# llxcc

VERSION = 0.0.1

# includes and libs
LIBS = -lelfparts

# flags
CFLAGS = -Wall -O3 ${LIBS} -DVERSION=\"${VERSION}\" -I./include

SRC = src/main.c
BIN = llxcc

all:
	gcc -o $(BIN) $(SRC) $(CFLAGS)

clean:
	rm -f $(BIN)

install: all
	cp -f $(BIN) /usr/local/bin/
