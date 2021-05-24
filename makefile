all:search.c search.o
	gcc search.c search.o -o main

search.o: search.h fun.c
	gcc -c fun.c -o search.o

clean:
	rm -f search.o main data1 data2 data3 query1 query2 query3
