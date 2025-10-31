CC = gcc
CFLAGS = -Wall -Werror -Wextra -pedantic -fsanitize=address -std=c11 -g
TARGET = lab6
SOURCES = main.c operations.c
HEADERS = operations.h

TEST_RUNNER = run_tests
TEST_SOURCES = tests.c operations.c

.PHONY: all clean internal_tests

all: $(TARGET)

$(TARGET): $(SOURCES) $(HEADERS)
	$(CC) $(CFLAGS) -o $(TARGET) $(SOURCES) -lm

internal_tests: $(TEST_RUNNER)
	@echo "--- Running Internal Tests ---"
	./$(TEST_RUNNER)
	@echo "------------------------------------"

$(TEST_RUNNER): $(TEST_SOURCES) $(HEADERS)
	$(CC) $(CFLAGS) -o $(TEST_RUNNER) $(TEST_SOURCES) -lm

clean:
	rm -f $(TARGET) $(TEST_RUNNER) *.o
