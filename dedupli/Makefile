CC=gcc
CFLAGS=-Wall -O2 -lpthread -D_FILE_OFFSET_BITS=64

all: socket.c socket.h main.c
	$(CC) socket.c main.c -o main $(CFLAGS)

.PHONY: clean

clean:
	rm main
