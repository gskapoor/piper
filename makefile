#
# Clauded Makefile : )
#

CC = gcc
CFLAGS = -Wall -Wextra -std=c2x
LDFLAGS = -lraylib -lm -lpthread -ldl -lX11

TARGET = piper
SRC_DIR = src
OBJ_DIR = obj
TEST_DIR = test
TEST_OBJ_DIR = $(OBJ_DIR)/test

SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

LIB_OBJS = $(filter-out $(OBJ_DIR)/piper.o, $(OBJS))

TEST_SRCS = $(wildcard $(TEST_DIR)/*.c)
TEST_BINS = $(patsubst $(TEST_DIR)/%.c, $(TEST_OBJ_DIR)/%, $(TEST_SRCS))

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET) $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(TEST_OBJ_DIR):
	mkdir -p $(TEST_OBJ_DIR)

$(TEST_OBJ_DIR)/%: $(TEST_DIR)/%.c $(LIB_OBJS) | $(TEST_OBJ_DIR)
	$(CC) $(CFLAGS) $< $(LIB_OBJS) -o $@

test: $(TEST_BINS)
	@for t in $(TEST_BINS); do \
		echo "Running $$t..."; \
		./$$t && echo "PASS" || echo "FAIL"; \
	done

.PHONY: all clean run debug release test
clean:
	rm -rf $(OBJ_DIR) $(TARGET)
run: $(TARGET)
	./$(TARGET)
debug: CFLAGS += -g -DDEBUG
debug: $(TARGET)
release: CFLAGS += -O2
release: $(TARGET)