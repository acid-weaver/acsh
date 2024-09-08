CC=gcc
ROOT=.
DIRS=bin buildins

all:
	($(CC) acsh.c -o main -I $(ROOT)/include -L $(ROOT)/lib -lapue -g -Wall)

clean:
	rm -f *.o a.out temp.*

