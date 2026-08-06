CC=gcc
CFLAGS=-Wall	-std=c11

all:	calculadora

calculadora:	operacoes.o	helpers.o	calculadora.o
	$(CC)	$(CFLAGS)	operacoes.o	helpers.o	calculadora.o	-o	calculadora

operacoes.o:	operacoes.c	operacoes.h
	$(CC)	$(CFLAGS)	-c	operacoes.c

helpers.o:	helpers.c	helpers.h
	$(CC)	$(CFLAGS)	-c	helpers.c

calculadora.o:	calculadora.c
	$(CC)	$(CFLAGS)	-c	calculadora.c

clean:
	rm	-f	*.o	calculadora
	rm arquivo_vazio

start:
	print	oi

validate:
	touch 'arquivo_vazio'