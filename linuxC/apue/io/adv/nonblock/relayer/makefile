CFLAGS+=-pthread -Wall -g
LDFLAGS+=-pthread
all:relayer
relayer:main.o relayer.o
	gcc $^ -o $@ $(CFLAGS) $(LDFLAGS)
clean:
	rm -rf *.o relayer