void treshold(unsigned char *imgMtr, int rows, int cols, unsigned char *lbpMtr);
void rotation(unsigned char *h);
void histogram(unsigned char *lbpMtr, int rows, int cols, FILE *hFile);
typedef struct {
	char key[3];
	unsigned short int rows, cols;
	unsigned char max, *imgMtr;
} PGM;