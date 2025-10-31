CC = gcc
CFLAGS = -Wall -Wextra -Werror -Wpedantic -std=c11 -fsanitize=address -g

TARGET = lab4
TEST_RUNNER = tests

SOURCES = main.c operations.c
HEADERS = operations.h
TEST_SOURCES = tests.c operations.c

.PHONY: all clean test

all: $(TARGET)

$(TARGET): $(SOURCES) $(HEADERS)
	$(CC) $(CFLAGS) -o $(TARGET) $(SOURCES) -lm

test: $(TEST_RUNNER)
	@echo "=== Running all tests ==="
	./$(TEST_RUNNER)
	@echo "========================="

$(TEST_RUNNER): $(TEST_SOURCES) $(HEADERS)
	$(CC) $(CFLAGS) -o $(TEST_RUNNER) $(TEST_SOURCES) -lm

clean:
	rm -f $(TARGET) $(TEST_RUNNER) *.o *.txt core
