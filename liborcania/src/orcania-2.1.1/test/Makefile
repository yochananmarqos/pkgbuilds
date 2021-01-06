#
# Public domain, no copyright. Use at your own risk.
#

CC=gcc
CFLAGS+=-Wall -D_REENTRANT -DDEBUG -g -O0 -I$(INCLUDE_LOCATION) $(CPPFLAGS)
ORCANIA_LOCATION=../src
INCLUDE_LOCATION=../include
ORCANIA_LIBRARY=$(ORCANIA_LOCATION)/liborcania.so
LIBS=-lc -lorcania $(shell pkg-config --libs check) -L$(ORCANIA_LOCATION)
VALGRIND_COMMAND=valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all

all: test

clean:
	rm -f *.o str_test split_test memory_test pointer_list_test valgrind-*.txt

liborcania.so:
	cd $(ORCANIA_LOCATION) && $(MAKE) debug

str_test: str_test.c
	$(CC) $(CFLAGS) str_test.c -o str_test $(LIBS)

test_str_test: liborcania.so str_test
	-LD_LIBRARY_PATH=$(ORCANIA_LOCATION):${LD_LIBRARY_PATH} ./str_test

split_test: split_test.c
	$(CC) $(CFLAGS) split_test.c -o split_test $(LIBS)

test_split_test: liborcania.so split_test
	-LD_LIBRARY_PATH=$(ORCANIA_LOCATION):${LD_LIBRARY_PATH} ./split_test

memory_test: memory_test.c
	$(CC) $(CFLAGS) memory_test.c -o memory_test $(LIBS)

test_memory_test: liborcania.so memory_test
	-LD_LIBRARY_PATH=$(ORCANIA_LOCATION):${LD_LIBRARY_PATH} ./memory_test

pointer_list_test: pointer_list_test.c
	$(CC) $(CFLAGS) pointer_list_test.c -o pointer_list_test $(LIBS)

test_pointer_list_test: liborcania.so pointer_list_test
	-LD_LIBRARY_PATH=$(ORCANIA_LOCATION):${LD_LIBRARY_PATH} ./pointer_list_test

test: test_str_test test_split_test test_memory_test test_pointer_list_test

check: test

memcheck: $(ORCANIA_LIBRARY) str_test split_test memory_test pointer_list_test
	-CK_FORK=no LD_LIBRARY_PATH=$(ORCANIA_LOCATION):${LD_LIBRARY_PATH} $(VALGRIND_COMMAND) ./str_test 2>valgrind-str_test.txt
	-CK_FORK=no LD_LIBRARY_PATH=$(ORCANIA_LOCATION):${LD_LIBRARY_PATH} $(VALGRIND_COMMAND) ./split_test 2>valgrind-split_test.txt
	-CK_FORK=no LD_LIBRARY_PATH=$(ORCANIA_LOCATION):${LD_LIBRARY_PATH} $(VALGRIND_COMMAND) ./memory_test 2>valgrind-memory_test.txt
	-CK_FORK=no LD_LIBRARY_PATH=$(ORCANIA_LOCATION):${LD_LIBRARY_PATH} $(VALGRIND_COMMAND) ./pointer_list_test 2>valgrind-pointer_list_test.txt
