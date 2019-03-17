// steg-decode.c
// Řešení IJC-DU1, příklad b), 16.3.2019
// Autor: Iveta Strnadová (xstrna14), FIT
// Přeloženo: gcc 7.3.0

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bit_array.h"
#include "ppm.h"
#include "error.h"
#include "eratosthenes.h"

int main(int argc, char* argv[])
{
	if(argc != 2) error_exit("Wrong number of arguments\n");
	char filename[strlen(argv[1])];
	strcpy(filename, argv[1]);
	
	struct ppm *photo = ppm_read(filename);
	if(photo == NULL) error_exit("steg-decode: Photo was not loaded correctly\n");
	
	unsigned long data_size = photo->xsize * photo->ysize *3;
	bit_array_alloc(primes, data_size);
	
	Eratosthenes(primes);
	
	bit_array_create(message_char, 8); //Using the bit_array_t for char so I could use bit_array_getbit macro correctly
	unsigned long msg_index = 0;
	
	
	for(unsigned long i = 19; i < data_size; i++) {
		if(bit_array_getbit(primes, i) == 0) {
			int value = photo->data[i] & 1; //value now stores the value of LSB of photo->data[i]
			bit_array_setbit(message_char, msg_index, value);
			msg_index++;
			if(msg_index == 8) {
				if(message_char[1] == '\0') {
					printf("\n");
					bit_array_free(primes);
					ppm_free(photo);
					return 0;
				}
				else printf("%c", (char) message_char[1]);
				msg_index = 0;
			}
		}
	}
	
	bit_array_free(primes);
	ppm_free(photo);
	error_exit("The message isn't ended with \'0\'\n");
}