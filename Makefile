# Compiler
CC = gcc

# Compiler flags
CFLAGS = -std=c99 -Wall -O3 -fopenmp

# Include directories
INCLUDES = -Iinclude

# Source files
SRCS = src/main.c src/array.c src/memory.c tests/test_array.c

# Object files
OBJS = $(SRCS:.c=.o)

# Executable names
TARGET = main
TEST_TARGET = test_array

# Default rule
all: $(TARGET) $(TEST_TARGET)

# Rule to link the main executable
$(TARGET): src/main.o src/array.o src/memory.o
	$(CC) $(CFLAGS) $(INCLUDES) -o $(TARGET) src/main.o src/array.o src/memory.o

# Rule to link the test executable
$(TEST_TARGET): tests/test_array.o src/array.o src/memory.o
	$(CC) $(CFLAGS) $(INCLUDES) -o $(TEST_TARGET) tests/test_array.o src/array.o src/memory.o

# Rule to compile source files into object files
%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Rule to clean the build
clean:
	rm -f src/*.o tests/*.o $(TARGET) $(TEST_TARGET)

# Phony targets
.PHONY: all clean
