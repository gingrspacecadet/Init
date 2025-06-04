# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -std=c99
LDFLAGS = -lncurses

# Source and build configuration
SRC_DIR = src
OBJ_DIR = obj
BIN = app

# Get all .c files and corresponding .o files
SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

# Default rule
all: $(BIN)

# Link objects into the binary
$(BIN): $(OBJS)
	@$(CC) $(OBJS) -o $@ $(LDFLAGS)

# Compile each .c to .o
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

# Create the obj directory if it doesn't exist
$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

# Clean rule
clean:
	@rm -rf $(OBJ_DIR) $(BIN)

.PHONY: all clean
