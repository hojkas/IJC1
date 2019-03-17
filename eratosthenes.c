// eratosthenes.c
// Řešení IJC-DU1, příklad a), 9.3.2019
// Autor: Iveta Strnadová (xstrna14), FIT
// Přeloženo: gcc 7.3.0

#include <math.h>
#include "eratosthenes.h"
#include "bit_array.h"

void Eratosthenes(bit_array_t pole)
{
    bit_array_setbit(pole, 0, 1);
    bit_array_setbit(pole, 1, 1);
	
    for(unsigned long i = 2; i <= (sqrt(bit_array_size(pole))); i++) {
        if((bit_array_getbit(pole, i) == 0)) {
            for(unsigned long x = (i + i); x < (bit_array_size(pole)); x += i) 
				bit_array_setbit(pole, x, 1);}
	}
}