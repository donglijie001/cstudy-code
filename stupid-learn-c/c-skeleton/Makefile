CFLAGS=-g -O2 -Wall -Wextra -Isrc -rdynamic -DNDEBUG $(OPTFLAGS)
#用于链接库的选项，同样也允许其它人使用 OPTFLAGS 变量扩展链接选项。
LIBS=-ldl $(OPTLIBS)
#可选变量，它只在没有 PREFIX 设置的平台上运行Makefile时有效
PREFIX?=/usr/local
#wildcard 搜索在 src/ 中所有 *.c 文件来动态创建 SOURCES 变量。
SOURCES=$(wildcard src/**/*.c src/*.c)
#一旦你创建了源文件列表，你可以使用 patsubst 命令获取 *.c 文件的 SOURCES 来创建目标文件的新列表。
#你可以告诉 patsubst 把所有 %.c 扩展
#为 %.o ，并将它们赋给 OBJECTS 。
OBJECTS=$(patsubst %.c,%.o,$(SOURCES))
#再次使用 wildcard 来寻找所有用于单元测试的测试源文件。它们存放在不同的目录中。
TEST_SRC=$(wildcard tests/*_tests.c)
#使用patsubst来动态获得所有 TEST 目标
TESTS=$(patsubst %.c,%,$(TEST_SRC))
# 最终目标设置为 build/libYOUR_LIBRARY.a
TARGET=build/libYOUR_LIBRARY.a
SO_TARGET=$(patsubst %.a,%.so,$(TARGET))

# The Target Build
all: $(TARGET) $(SO_TARGET) tests

dev: CFLAGS=-g -Wall -Isrc -Wall -Wextra $(OPTFLAGS)
dev: all

$(TARGET): CFLAGS += -fPIC
$(TARGET): build $(OBJECTS)
	ar rcs $@ $(OBJECTS)
	ranlib $@
$(SO_TARGET): $(TARGET) $(OBJECTS)
	$(CC) -shared -o $@ $(OBJECTS)
build:
	@mkdir -p build
	@mkdir -p bin
# The Unit Tests
.PHONY: tests
tests: CFLAGS += $(TARGET)
tests: $(TESTS)
	sh ./tests/runtests.sh
valgrind:
VALGRIND="valgrind --log-file=/tmp/valgrind-%p.log" $(MAKE)
# The Cleaner
clean:
	rm -rf build $(OBJECTS) $(TESTS)
	rm -f tests/tests.log
	find . -name "*.gc*" -exec rm {} \;
	rm -rf `find . -name "*.dSYM" -print`
# The Install
install: all
	install -d $(DESTDIR)/$(PREFIX)/lib/
	install $(TARGET) $(DESTDIR)/$(PREFIX)/lib/

# The Checker
BADFUNCS='[^_.>a-zA-Z0-9](str(n?cpy|n?cat|xfrm|n?dup|str|pbrk|tok|_)|stpn?cpy|a?sn?printf|byte_)'
check:
	@echo Files with potentially dangerous functions.
	@egrep $(BADFUNCS) $(SOURCES) || true