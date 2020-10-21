all: imgproc.e

imgproc.e: main.o lbp.o rotation.o histogram.o
	gcc -o imgproc.e main.o lbp.o rotation.o histogram.o

main.o: main.c lib.h
	gcc -o main.o -c main.c

lbp.o: lbp.c lib.h
	gcc -o lbp.o -c lbp.c

rotation.o: rotation.c lib.h
	gcc -o rotation.o -c rotation.c

histogram.o: histogram.c lib.h
	gcc -o histogram.o -c histogram.c

clear:
	rm -f imgproc.e *.o
