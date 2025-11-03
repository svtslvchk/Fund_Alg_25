CC = gcc
CFLAGS = -Wall -Werror -Wextra -Wpedantic -fsanitize=address -std=c11 -g
TARGET = lab1
SOURCES = main.c check_brackets.c
HEADERS = check_brackets.h

TEST_RUNNER = tests
TEST_SOURCES = tests.c check_brackets.c

.PHONY: all clean test

all: $(TARGET)

$(TARGET): $(SOURCES) $(HEADERS)
	$(CC) $(CFLAGS) -o $(TARGET) $(SOURCES)

test: $(TEST_RUNNER)
	@echo "--- Running Bracket Tests ---"
	./$(TEST_RUNNER)
	@echo "-------------------------------"

$(TEST_RUNNER): $(TEST_SOURCES) $(HEADERS)
	$(CC) $(CFLAGS) -o $(TEST_RUNNER) $(TEST_SOURCES)

clean:
	rm -f $(TARGET) $(TEST_RUNNER)