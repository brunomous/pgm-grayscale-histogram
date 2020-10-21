#include <stdio.h>
#include <stdlib.h>
#include "lib.h"

void treshold(unsigned char *imgMtr, int rows, int cols, unsigned char *lbpMtr) {
	register int i, j;
	unsigned char hold;

	for (i=0; i<rows-2; i++) {
		for (j=0; j<cols-2; j++) {
			hold = 0;
			hold = (*(imgMtr+(i*cols)+j) >= *(imgMtr+((i+1)*cols)+(j+1))) ? (hold + 0x80) : (hold);
			hold = (*(imgMtr+(i*cols)+(j+1)) >= *(imgMtr+((i+1)*cols)+(j+1))) ? (hold + 0x40) : (hold);
			hold = (*(imgMtr+(i*cols)+(j+2)) >= *(imgMtr+((i+1)*cols)+(j+1))) ? (hold + 0x20) : (hold);
			hold = (*(imgMtr+((i+1)*cols)+(j+2)) >= *(imgMtr+((i+1)*cols)+(j+1))) ? (hold + 0x10) : (hold);
			hold = (*(imgMtr+((i+2)*cols)+(j+2)) >= *(imgMtr+((i+1)*cols)+(j+1))) ? (hold + 0x08) : (hold);
			hold = (*(imgMtr+((i+2)*cols)+(j+1)) >= *(imgMtr+((i+1)*cols)+(j+1))) ? (hold + 0x04) : (hold);
			hold = (*(imgMtr+((i+2)*cols)+j) >= *(imgMtr+((i+1)*cols)+(j+1))) ? (hold + 0x02) : (hold);
			hold = (*(imgMtr+((i+1)*cols)+j) >= *(imgMtr+((i+1)*cols)+(j+1))) ? (hold + 0x01) : (hold);

			rotation(&hold);

			*(lbpMtr+(i*cols)+j) = hold;
		}
	}
}
