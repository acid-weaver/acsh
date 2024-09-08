CC=gcc
ROOT=..

BUILDINS=ls hello

all:
	for func in $(BUILDINS); do \
	($(CC) "$$func.c" -o "$$func.o" -I $(ROOT)/include -L $(ROOT)/lib -lapue -g -Wall) \
	done

ls:
	gcc ls.c -o ls.o -I $(ROOT)/include -L $(ROOT)/lib -lapue

clean:
	rm -f *.o a.out temp.*

