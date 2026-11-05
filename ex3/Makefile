CC = gcc
CFLAGS = -Wall -Wextra -Iinclude -O2
BIN_DIR = bin
SRC_DIR = src

OBJS = $(SRC_DIR)/hash.o $(SRC_DIR)/priority_queue.o

UNITY_OBJ = $(SRC_DIR)/unity.o

all: $(BIN_DIR)/main_ex3 $(BIN_DIR)/test_ex3

$(BIN_DIR)/main_ex3: $(OBJS) $(SRC_DIR)/main_ex3.c
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) -o $@ $(SRC_DIR)/main_ex3.c $(OBJS)

$(BIN_DIR)/test_ex3: $(OBJS) $(UNITY_OBJ) $(SRC_DIR)/test_ex3.c
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) -o $@ $(SRC_DIR)/test_ex3.c $(OBJS) $(UNITY_OBJ)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(SRC_DIR)/*.o
	rm -rf $(BIN_DIR)