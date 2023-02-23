# Simple Makefile for static library construction and testing

#all: library test

#library:
#	gcc -c geohash.c -o geohash.o
#	ar rcs libgeohash.a geohash.o
#	rm geohash.o
	
#test:
#	gcc geohash_test.c geohash.c 	
#	./a.out
#	rm a.out
	
#clean: 
#	rm -rf *.a *.o

all:
	gcc geohash.c -o geohash.o -c
	gcc geohash_test.c -o geohash_test.o -c
	gcc -o exegeo geohash.o geohash_test.o
	rm geohash.o geohash_test.o
	chmod +x exegeo
	echo "\n\n"
	time ./exegeo
