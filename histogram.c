#include <stdio.h>
#include "lib.h"

void histogram(unsigned char *lbpMtr, int rows, int cols, FILE *hFile) {
	register int i, j;
	unsigned short int k = 0;
	unsigned int frq = 0;

	for(k=0; k<256; k++) {
		frq = 0;
		for(i=0; i<(rows-2); i++) {
			for(j=0; j<(cols-2); j++) {
				if(*(lbpMtr+(i*cols)+j) == k) frq++;
			}
		}
		if(frq == 0) continue;
		fprintf(hFile, "[%3hu]: %d\n", k, frq);
	}
}