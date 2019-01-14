#makefile for count.c (CSE 5462 Lab 1)

CC = gcc
CFlags = -g -Wall

all: count

count: count.c
	$(CC) $(CFLAGS) -o count count.c

clean:
	rm count
