# Compiler
CC = gcc

# Compiler flags
CFLAGS = -std=c99 -Wall -O3 -fopenmp

# Include directories
INCLUDES = -Iinclude

# Source files
SRCS = src/main.c src/array.c src/memory.c

# Object files
OBJS = $(SRCS:.c=.o)

# Executable name
TARGET = main

# Default rule
all: $(TARGET)

# Rule to link the executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) -o $(TARGET) $(OBJS)

# Rule to compile source files into object files
%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Rule to clean the build
clean:
	rm -f $(OBJS) $(TARGET)

# Phony targets
.PHONY: all clean
