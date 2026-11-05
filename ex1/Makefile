CC = gcc
CFLAGS = -Wall -Wextra -Wpedantic -g -O2
INCLUDES = -I./include
SRC_DIR = src
BIN_DIR = bin

OBJS = $(BIN_DIR)/hybrid_sort.o $(BIN_DIR)/quick_sort.o \
       $(BIN_DIR)/selection_sort.o $(BIN_DIR)/records.o

UNITY_OBJ = $(BIN_DIR)/unity.o

all: $(BIN_DIR) $(BIN_DIR)/main_ex1 $(BIN_DIR)/test_ex1

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

$(BIN_DIR)/main_ex1: $(SRC_DIR)/main_ex1.c $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) $^ -o $@

$(BIN_DIR)/test_ex1: $(SRC_DIR)/test_ex1.c $(OBJS) $(UNITY_OBJ)
	$(CC) $(CFLAGS) $(INCLUDES) $^ -o $@

$(BIN_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -rf $(BIN_DIR)/*