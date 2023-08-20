all: llist
cc = gcc
llist:main.o llist.o
	$(cc) $^ -o $@

clean:
	rm *.o main -rf