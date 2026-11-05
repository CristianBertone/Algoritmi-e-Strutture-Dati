CC = gcc
CFLAGS = -Wall -Wextra -Werror -Iinclude -g


all: bin/main_ex4 bin/test_ex4


bin/main_ex4: src/main_ex4.c src/graph.c src/hash.c
	@mkdir -p bin
	$(CC) $(CFLAGS) -o bin/main_ex4 src/main_ex4.c src/graph.c src/hash.c


bin/test_ex4: src/test_ex4.c src/graph.c src/hash.c src/unity.c
	@mkdir -p bin
	$(CC) $(CFLAGS) -o bin/test_ex4 src/test_ex4.c src/graph.c src/hash.c src/unity.c


clean:
	rm -rf bin/