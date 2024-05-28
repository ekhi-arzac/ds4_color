# Makefile for compiling ds4_rainbow.c

# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -lm

# Target executable
TARGET = ds4_color

# Source file
SRC = src/ds4_color.c

# Default rule
all: $(TARGET)

# Rule to build the target executable
$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

# Rule to clean up the build
clean:
	rm -f $(TARGET)

# Phony targets
.PHONY: all clean

