#include <stdio.h>
#include "lib.h"

void rotation(unsigned char *h) {
	int i;
	unsigned char lowerVal = *h;

	for(i=0; i<8; i++) {
		lowerVal = (lowerVal & 0x01) ? (lowerVal>>1) | 0x80 : (lowerVal>>1);
		if(lowerVal < *h) *h = lowerVal;
	}
}