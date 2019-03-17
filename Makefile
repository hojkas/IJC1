# Makefile
# Řešení IJC-DU1, 9.3.2019
# Autor: Iveta Strnadová (xstrna14), FIT

SHELL = /bin/bash

CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -pedantic -O2

all: primes primes-i steg-decode

primes: primes.o eratosthenes.o error.o bit_array.o
	$(CC) $(CFLAGS) primes.o eratosthenes.o error.o bit_array.o -o primes -lm
primes.o: primes.c
	$(CC) $(CFLAGS) -c primes.c -o primes.o
eratosthenes.o: eratosthenes.c eratosthenes.h
	$(CC) $(CFLAGS) -c eratosthenes.c -o eratosthenes.o
error.o: error.c error.h
	$(CC) $(CFLAGS) -c error.c -o error.o
bit_array.o: bit_array.c bit_array.h
	$(CC) $(CFLAGS) -c bit_array.c -o bit_array.o

primes-i: primes-i.o eratosthenes-i.o error.o bit_array-i.o
	$(CC) $(CFLAGS) primes-i.o eratosthenes-i.o error.o bit_array-i.o -DUSE_INLINE -o primes-i -lm
primes-i.o: primes.c bit_array.h
	$(CC) $(CFLAGS) -c primes.c -DUSE_INLINE -o primes-i.o
eratosthenes-i.o: eratosthenes.c bit_array.h eratosthenes.h
	$(CC) $(CFLAGS) -c eratosthenes.c -DUSE_INLINE -o eratosthenes-i.o
bit_array-i.o: bit_array.c bit_array.h
	$(CC) $(CFLAGS) -c bit_array.c -DUSE_INLINE -o bit_array-i.o

steg-decode: steg-decode.o ppm.o error.o eratosthenes.o bit_array.o
	$(CC) $(CFLAGS) steg-decode.o ppm.o error.o eratosthenes.o bit_array.o -o steg-decode -lm
steg-decode.o: steg-decode.c ppm.h
	$(CC) $(CFLAGS) -c steg-decode.c -o steg-decode.o
ppm.o: ppm.c ppm.h
	$(CC) $(CFLAGS) -c ppm.c -o ppm.o

clean:
	rm -f *.o primes primes-i steg-decode

run: primes primes-i
	time ./primes
	time ./primes-i
