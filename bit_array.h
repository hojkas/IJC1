// bit_array.h
// Řešení IJC-DU1, příklad a), 9.3.2019
// Autor: Iveta Strnadová (xstrna14), FIT
// Přeloženo: gcc 7.3.0

#ifndef BIT_ARRAY_H
#define BIT_ARRAY_H

#include <stdlib.h>
#include "error.h"
#include <assert.h>
#include <limits.h>

typedef unsigned long *bit_array_t;

//creates bit_array, sets all items to 0 and stores the size of array to jmeno_pole[0]
#define bit_array_create(jmeno_pole, velikost) unsigned long jmeno_pole[((velikost-1)/(8*sizeof(unsigned long)))+2];\
jmeno_pole[0] = (velikost);\
for(unsigned long i = 1; i < ((velikost-1)/(8*sizeof(unsigned long)))+2; i++) jmeno_pole[i] = 0;\
_Static_assert(((velikost) > 0 && (velikost) < (ULONG_MAX)), "bit_array_create: Velikost pole mimo povoleny rozsah")

//allocates nulled bit_array and stores the size of array to jmeno_pole[0]
#define bit_array_alloc(jmeno_pole, velikost) assert((velikost) > 0 && (velikost) < (ULONG_MAX));\
bit_array_t jmeno_pole = calloc((((velikost-1)/(8*sizeof(unsigned long)))+2), sizeof(unsigned long));\
if(jmeno_pole == NULL) error_exit("bit_array_alloc: Chyba alokace paměti\n");\
jmeno_pole[0] = (velikost);

//frees allocated bit_array
#define bit_array_free(jmeno_pole) free(jmeno_pole)

#ifndef USE_INLINE

	//reads size of array from jmeno_pole[0]	
	#define bit_array_size(jmeno_pole) (jmeno_pole[0])

	//sets bit on index position to value of vyraz(NOT counting first unsigned long with size value)
	#define bit_array_setbit(jmeno_pole, index, vyraz) (((unsigned long)(index) < (bit_array_size(jmeno_pole))) ?\
	((vyraz == 0) ?\
	(jmeno_pole[(index)/(sizeof(unsigned long)*8)+1] &= ~(1L << ((index)%(sizeof(unsigned long)*8)))) :\
	(jmeno_pole[(index)/(sizeof(unsigned long)*8)+1] |= (1L << ((index)%(sizeof(unsigned long)*8))))) \
	: (error_exit("bit_array_setbit: Index %lu mimo rozsah 0..%lu\n", index, bit_array_size(jmeno_pole)-1),0))

	//returns bit on index position (NOT counting first unsigned long with size value)
	#define bit_array_getbit(jmeno_pole, index) (((unsigned long)(index) < (bit_array_size(jmeno_pole))) ? (\
	(jmeno_pole[1+((index)/(sizeof(unsigned long)*8))] & (1L << ((index)%(sizeof(unsigned long)*8))))\
	? 1 : 0) : (error_exit("bit_array_getbit: Index %lu mimo rozsah 0..%lu\n", index, bit_array_size(jmeno_pole)-1),0))

#endif

#ifdef USE_INLINE
	
	inline unsigned long bit_array_size(bit_array_t jmeno_pole)
	{
		return jmeno_pole[0];
	}
	
	inline void bit_array_setbit(bit_array_t jmeno_pole, unsigned long index, int vyraz)
	{
		if((index < bit_array_size(jmeno_pole))) {
			if(vyraz == 0)
				jmeno_pole[(index)/(sizeof(unsigned long)*8)+1] &= ~(1L << ((index)%(sizeof(unsigned long)*8)));
			else
				jmeno_pole[(index)/(sizeof(unsigned long)*8)+1] |= (1L << ((index)%(sizeof(unsigned long)*8)));
		}
		else
			error_exit("bit_array_setbit: Index %lu mimo rozsah 0..%lu", index, bit_array_size(jmeno_pole)-1);
	}
	
	inline int bit_array_getbit(bit_array_t jmeno_pole, unsigned long index)
	{
		if((index < bit_array_size(jmeno_pole))) {
			if((jmeno_pole[1+((index)/(sizeof(unsigned long)*8))] & (1L << ((index)%(sizeof(unsigned long)*8)))) == 0)
				return 0;
			else return 1;
		}
		else {
			error_exit("bit_array_getbit: Index %lu mimo rozsah 0..%lu\n", index, bit_array_size(jmeno_pole)-1);
			return -1;
		}
	}

#endif

#endif
