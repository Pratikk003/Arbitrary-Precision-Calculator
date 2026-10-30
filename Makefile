CC     = gcc
CFLAGS = -Wall -Wextra -std=c99 -g
SRC    = main.c list.c validate.c sign.c add.c sub.c mul.c div.c
OBJ    = $(SRC:.c=.o)

apc: $(OBJ)
	$(CC) $(CFLAGS) -o $@ $(OBJ)

%.o: %.c apc.h
	$(CC) $(CFLAGS) -c $<

# Quick demo of every operation
demo: apc
	./apc 123 + 456
	./apc 100 - 250
	./apc 99999999999999999999 x 99999999999999999999
	./apc 1000 / 7

clean:
	rm -f $(OBJ) apc

.PHONY: clean demo
