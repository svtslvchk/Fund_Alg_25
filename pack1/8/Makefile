CC = gcc
CFLAGS = -Wall -Werror -Wextra -Wpedantic -fsanitize=address -std=c11 -g
TARGET = app
SOURCES = main.c operations.c validation.c
HEADERS = operations.h

TEST_RUNNER = tests
TEST_SOURCES = tests.c operations.c validation.c

.PHONY: all clean test

all: $(TARGET)

$(TARGET): $(SOURCES) $(HEADERS)
	$(CC) $(CFLAGS) -o $(TARGET) $(SOURCES)

test: $(TEST_RUNNER)
	@echo "--- Running Internal Tests ---"
	./$(TEST_RUNNER)
	@echo "-------------------------------"

$(TEST_RUNNER): $(TEST_SOURCES) $(HEADERS)
	$(CC) $(CFLAGS) -o $(TEST_RUNNER) $(TEST_SOURCES)

clean:
	rm -f $(TARGET) $(TEST_RUNNER) input.txt output.txt expected.txt tmp_*.txt
