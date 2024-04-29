# Makefile

# Compiler and compiler flags
CC = gcc
CFLAGS = -Wall 

# Define directories
SRC_DIR = src
BIN_DIR = bin

# Find all .c files in the src directory
SOURCES = $(wildcard $(SRC_DIR)/*.c)

# Replace the src directory and .c extension with the bin directory and no extension for binaries
EXECUTABLES = $(patsubst $(SRC_DIR)/%.c,$(BIN_DIR)/%,$(SOURCES))

# Default target
all: $(EXECUTABLES)

# Rule to create the bin directory
$(BIN_DIR):
	mkdir -p $@

# Rule to compile the source files into executables
$(BIN_DIR)/%: $(SRC_DIR)/%.c | $(BIN_DIR)
	$(CC) $(CFLAGS) $< -o $@

# Clean target
clean:
	rm -rf $(BIN_DIR)

.PHONY: all clean
