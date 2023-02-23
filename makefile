CC = gcc
CFLAGS = -Wall -Wextra -pedantic -std=c99 `sdl2-config --cflags`
LDFLAGS = `sdl2-config --libs`

pong: pong.c
	$(CC) $(CFLAGS) -o $@ $< $(LDFLAGS)

clean:
	rm -f pong
