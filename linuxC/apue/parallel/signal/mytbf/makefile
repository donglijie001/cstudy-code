all:mytbf
mytbf:main.o mytbf.o
	gcc $^ -o $@
clean:
	rm -rf *.o mytbf
# 出现的第一条命令all，就是默认的编译命令，在编译的时候，可以直接输入make就可以了