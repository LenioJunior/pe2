CC=gcc
CFLAGS=-Wall	-std=c11

all:	agenda

agenda:	agenda.o	helpers.o	main.o
	$(CC)	$(CFLAGS)	agenda.o	helpers.o	main.o	-o	main

agenda.o:	agenda.c	agenda.h
	$(CC)	$(CFLAGS)	-c	agenda.c

helpers.o:	helpers.c	helpers.h
	$(CC)	$(CFLAGS)	-c	helpers.c

main.o:	main.c
	$(CC)	$(CFLAGS)	-c	main.c

clean:
	rm	-f	*.o	main