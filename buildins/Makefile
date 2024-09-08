CC=gcc
ROOT=..

BUILDINS=ls

all:
	for func in $(BUILDINS); do \
	($(CC) "$$func.c" -o "$$func.o" -I $(ROOT)/include -L $(ROOT)/lib -lapue -g -Wall) \
	done

clean:
	rm -f *.o a.out temp.*

