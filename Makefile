# llxcc

VERSION = 0.0.1

# includes and libs
LIBS = 

# flags
CFLAGS = -Wall -O3 ${LIBS} -DVERSION=\"${VERSION}\" -I./include -m32

SRC = src/main.c src/libelfparts.a
BIN = llxcc

all:
	gcc -o $(BIN) $(SRC) $(CFLAGS)

clean:
	rm -f $(BIN)

install: all
	cp -f $(BIN) /usr/local/bin/
