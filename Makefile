all:main $

main:main.o parser.o utf8-rus.o utf8-io.o
	gcc main.o parser.o utf8-rus.o utf8-io.o -o main $

main.o:main.c
	gcc -c main.c -o main.o $

parser.o:parser.c
	gcc -c parser.c -o parser.o $

utf8-rus.o:utf8-rus.c
	gcc -c utf8-rus.c -o utf8-rus.o $

utf8-io.o:utf8-io.c
	gcc -c utf8-io.c -o utf8-io.o $
