# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -Iinclude
LDFLAGS =

# Source and build configuration
SRC_DIR = src
OBJ_DIR = obj
BUILD_DIR = build
BIN = app

# Get all .c files and corresponding .o files
SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

# Default rule
all: $(BUILD_DIR) $(BUILD_DIR)/$(BIN)

# Link objects into the binary
$(BUILD_DIR)/$(BIN): $(OBJS)
	@$(CC) $(OBJS) -o $@ $(LDFLAGS)

# Compile each .c to .o
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

# Create the obj directory if it doesn't exist
$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

# Create the build directory if it doesn't exist
$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)

# Clean rule
clean:
	@rm -rf $(OBJ_DIR) $(BUILD_DIR)

.PHONY: all clean
