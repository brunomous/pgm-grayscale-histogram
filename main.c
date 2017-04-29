#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "lib.h"

int main(int argc, char **argv) {
	clock_t start, end;
	double cpu_time_used;

	FILE *arq;
	PGM img;
	register int i, j;
	unsigned char *lbpMtr;
	FILE *arqHist;
	char comment[200];

	start = clock();

	if(argc!=2) {
		printf("Use: %s image_name.pgm\n", *argv);
		exit(1);
	}
	if(!(arq = fopen(*(argv+1), "rb"))) {
		printf("Unavailable image.\n");
		exit(1);
	}
	if(!(arqHist = fopen("histogram.txt", "w"))) {
		printf("Unavailable histogram file.\n");
		exit(1);
	}

	fgets(img.key, 3, arq);
	fseek(arq, 3, SEEK_SET);
	fgets(comment, sizeof(comment), arq);
	if(comment[0] == '#') {
		fscanf(arq, "%hu %hu %hhu", &img.rows, &img.cols, &img.max);        	
	} else {
		fseek(arq, 2, SEEK_SET);
		fscanf(arq, "%hu %hu %hhu", &img.rows, &img.cols, &img.max);
	}

	lbpMtr = (unsigned char *) malloc((img.rows-2)*(img.cols-2)*sizeof(unsigned char));
	img.imgMtr = (unsigned char *) malloc(img.rows*img.cols*sizeof(unsigned char));
	
	if(!(lbpMtr) || !(img.imgMtr)) {
		printf("Impossible allocation.\n");
		exit(1);
	}

	if(!strcmp(img.key, "P2")) {
		for (i=0; i<img.rows; i++){
	    	for(j=0; j<img.cols; j++){
	        	fscanf(arq, "%hhu", (img.imgMtr+(i*img.cols)+j));
	    	} 
		}
	}
	if(!strcmp(img.key, "P5")) {
		for (i=0; i<img.rows; i++){
	    	for(j=0; j<img.cols; j++){
	    		fread((img.imgMtr+(i*img.cols)+j), 1, 1, arq);
	    	}
		}
	}

	treshold(img.imgMtr, img.rows, img.cols, lbpMtr);
	histogram(lbpMtr, img.rows, img.cols, arqHist);

	//if needed, prints the lbp matrix
	/*printf("\nLBP MATRIX:\n");
	for(i=0; i<(img.rows-2); i++) {
		for(j=0; j<(img.cols-2); j++) {
			printf("%3d ", *(lbpMtr+(i*img.cols)+j));
		}
		printf("\n");
	}
	printf("\n");*/

	fclose(arq);
	img.imgMtr = NULL;
	free(img.imgMtr);
	lbpMtr = NULL;
	free(lbpMtr);
	fclose(arqHist);

	end = clock();

	cpu_time_used = ((double)(end-start))/CLOCKS_PER_SEC;
	printf("\nExecution time: %f s.\n\n", cpu_time_used);

	return 0;
}