CC=gcc
CFLAGS=-Wall -lpthread -D_FILE_OFFSET_BITS=64

all: main.c
	$(CC) main.c -o main $(CFLAGS)

.PHONY: clean

clean:
	rm main
