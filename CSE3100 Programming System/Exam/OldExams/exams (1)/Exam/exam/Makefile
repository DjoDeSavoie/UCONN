CC=gcc
CFLAGS=-Wall -g -std=c99
TARGETS=match

all: $(TARGETS)

match: match.c linked_list.c linked_list.h stack.c stack.h
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f *.o *~ $(TARGETS) a.out