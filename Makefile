# Makefile for Sorting Algorithm Visualizer

CC = gcc
CFLAGS = -Wall -Wextra -O2
TARGET = sorting_visualizer
SRC = sorting_visualizer.c

# Windows specific
ifeq ($(OS),Windows_NT)
    TARGET := $(TARGET).exe
    RM = del /Q
else
    RM = rm -f
endif

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

clean:
	$(RM) $(TARGET)

run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run
