CC			=gcc
CFLAGS	=-Wall	-std=c11

all:	exercicios

exercicios:	helpers.o	ex1.o	ex2.o ex3.o	ex4.o main.o
	$(CC)	$(CFLAGS)	helpers.o	ex1.o	ex2.o ex3.o	ex4.o main.o	-o	exercicios

ex1.o: ex1.c
	$(CC)	$(CFLAGS)	-c	ex1.c

ex2.o:	ex2.c
	$(CC)	$(CFLAGS)	-c	ex2.c

ex3.o:	ex3.c
	$(CC)	$(CFLAGS)	-c	ex3.c

ex4.o:	ex4.c
	$(CC)	$(CFLAGS)	-c	ex4.c

helpers.o:	helpers.c
	$(CC)	$(CFLAGS)	-c	helpers.c

main.o:	main.c
	$(CC)	$(CFLAGS)	-c	main.c

clean:
	rm	-f	*.o	exercicios