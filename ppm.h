// ppm.h
// Řešení IJC-DU1, příklad b), 11.3.2019
// Autor: Iveta Strnadová (xstrna14), FIT
// Přeloženo: gcc 7.3.0

#ifndef PPM_H
#define PPM_H

struct ppm {
	unsigned xsize;
	unsigned ysize;
	char data[];
};

struct ppm * ppm_read(const char * filename);

void ppm_free(struct ppm *p);

#endif