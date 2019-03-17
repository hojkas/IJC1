// primes.c
// Řešení IJC-DU1, příklad a), 9.3.2019
// Autor: Iveta Strnadová (xstrna14), FIT
// Přeloženo: gcc 7.3.0

#include <stdio.h>
#include <stdlib.h>
#include "bit_array.h"
#include "eratosthenes.h"
#include "error.h"

int main() {
	bit_array_create(pole, 123000000L);
	Eratosthenes(pole);
	
	unsigned long last_index = 0;
	int primes_found = 0;
	for(unsigned long i = (bit_array_size(pole)) - 1; i > 1 && primes_found < 10; i--)
			if(bit_array_getbit(pole, i) == 0) {
				primes_found++;
				last_index = i;
			}
	
	for(unsigned long i = last_index; i < (bit_array_size(pole)); i++)
		if(bit_array_getbit(pole, i) == 0) printf("%lu\n", i);
	
    return 0;
}