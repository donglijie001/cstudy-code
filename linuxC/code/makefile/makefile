OBJS= main.o tool1.o tool2.o
cc=gcc
CFLAGS+=-c -Wall -g
mytool:$(OBJS)
	$(cc) $^ -o $@
main.o:main.c
	$(cc) $^	$(CFLAGS) -o $@
tool1.o:tool1.c
	$(cc) $^	$(CFLAGS) -o $@
tool2.o:tool2.c
	$(cc) $^	$(CFLAGS) -o $@
clean:
	rm *.o mytool -rf