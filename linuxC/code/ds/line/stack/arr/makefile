all: sqstack
cc = gcc
sqstack:main.o sqstack.o
	$(cc) $^ -o $@

clean:
	rm *.o main -rf