// bit_array.c
// Řešení IJC-DU1, příklad a), 16.3.2019
// Autor: Iveta Strnadová (xstrna14), FIT
// Přeloženo: gcc 7.3.0

#include "bit_array.h"

#ifdef USE_INLINE

extern unsigned long bit_array_size(bit_array_t jmeno_pole);
extern void bit_array_setbit(bit_array_t jmeno_pole, unsigned long index, int vyraz);
extern int bit_array_getbit(bit_array_t jmeno_pole, unsigned long index);

#endif