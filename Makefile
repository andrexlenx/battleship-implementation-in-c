# Makefile for Battleship Game

CC = gcc
CFLAGS = -Wall -Wextra -std=c99
TARGET = battleship
TEST_TARGET = test_battleship
SRC = battleship.c
TEST_SRC = test_battleship.c

# Default target
all: $(TARGET)

# Build the executable
$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

# Build the test executable
$(TEST_TARGET): $(TEST_SRC)
	$(CC) $(CFLAGS) -o $(TEST_TARGET) $(TEST_SRC)

# Run tests
test: $(TEST_TARGET)
	./$(TEST_TARGET)

# Clean build artifacts
clean:
	rm -f $(TARGET) $(TARGET).exe $(TEST_TARGET) $(TEST_TARGET).exe

# Run the game
run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run test
