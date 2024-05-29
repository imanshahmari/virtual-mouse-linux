CC = gcc
CFLAGS = -Wall

all: virtual_mouse

virtual_mouse: virtual_mouse.c
	$(CC) $(CFLAGS) -o $@ $<

clean:
	rm -f virtual_mouse