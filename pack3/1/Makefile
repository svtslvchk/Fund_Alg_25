CC = gcc
CFLAGS = -Wall -Werror -Wextra -Wpedantic -fsanitize=address -std=c11 -g
TARGET = lab1
SOURCES = main.c operations.c
HEADERS = operations.h

TEST_RUNNER = tests
TEST_SOURCES = tests.c operations.c

.PHONY: all clean test

all: $(TARGET)

$(TARGET): $(SOURCES) $(HEADERS)
	$(CC) $(CFLAGS) -o $(TARGET) $(SOURCES) -lm

test: $(TEST_RUNNER)
	@echo "--- Running Internal Tests ---"
	./$(TEST_RUNNER)
	@echo "-------------------------------"

$(TEST_RUNNER): $(TEST_SOURCES) $(HEADERS)
	$(CC) $(CFLAGS) -o $(TEST_RUNNER) $(TEST_SOURCES) -lm

clean:
	rm -f $(TARGET) $(TEST_RUNNER)