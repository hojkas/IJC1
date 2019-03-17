// ppm.c
// Řešení IJC-DU1, příklad b), 11.3.2019
// Autor: Iveta Strnadová (xstrna14), FIT
// Přeloženo: gcc 7.3.0

#include "ppm.h"
#include "error.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct ppm * ppm_read(const char * filename)
{
	int allocated = 0;
	
	if(filename == NULL) {
		warning_msg("ppm_read: Invalid filename\n");
		return NULL;
	}
	
	FILE* f = fopen(filename, "r");
	if(f == NULL) {
		warning_msg("ppm_read: File %s could not be opened\n", filename);
		return NULL;
	}
	
	unsigned x, y;
	char line[5];
	
	if(fgets(line, 4, f) == NULL) goto error;
	if(strcmp(line, "P6\n") != 0) goto error;
	
	if(fscanf(f, "%u %u\n", &x, &y) == 0) goto error;
	if(x == 0 || y == 0 || x > 8000 || y > 8000) goto error; //restricted to max 8000*8000
	
	if(fgets(line, 5, f) == NULL) goto error;
	if(strcmp(line, "255\n") != 0) goto error;
	
	allocated = -1;
	struct ppm *photo = malloc (sizeof(struct ppm) + x*y*3);
	if(photo == NULL) goto error;
	
	allocated = 1;
	
	photo->xsize = x;
	photo->ysize = y;
	
	int loaded;
	unsigned i;
	for(i = 0; ((loaded = fgetc(f)) != EOF) && (i < x*y*3); i++) {
		if(loaded != '\n') photo->data[i] = loaded;
	}
	
	if(loaded != EOF || i != x*y*3) goto error;
	
	fclose(f);
	return photo;
	
	error:
		if(allocated == 1) free(photo);
		fclose(f);
		if(allocated == -1) warning_msg("ppm_read: Allocation error\n");
		else warning_msg("ppm_read: File %s not in ppm format\n", filename);
		return NULL;
}

void ppm_free(struct ppm *p)
{
	free(p);
}