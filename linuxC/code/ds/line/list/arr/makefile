all:main
cc=gcc
CFLAGS+=-c -Wall -g
main:main.o sqlist.o
	$(cc) $^ -o $@
sqlist.o:sqlist.c
	$(cc) sqlist.c -c 	-o	sqlist.o
main.o:main.c
	$(cc) main.c -c -o main.o

clean:
	rm *.o main -rf