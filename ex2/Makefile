CC = gcc
CFLAGS = -Wall -Wextra -Werror -Iinclude -g
all: bin/main_ex2 bin/test_ex2
bin/main_ex2: src/main_ex2.c src/hash.c
	@mkdir -p bin
	$(CC) $(CFLAGS) -o bin/main_ex2 src/main_ex2.c src/hash.c

bin/test_ex2: tests/test_ex2.c src/hash.c src/unity.c
	@mkdir -p bin
	$(CC) $(CFLAGS) -o bin/test_ex2 tests/test_ex2.c src/hash.c src/unity.c

clean:
	rm -rf bin/