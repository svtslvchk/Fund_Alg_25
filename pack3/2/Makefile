CC = gcc
CFLAGS = -Wall -Werror -Wextra -Wpedantic -fsanitize=address -std=c11 -g
TARGET = lab2
SOURCES = main.c vector.c
HEADERS = vector.h

TEST_INT = test_int
TEST_STR = test_str

.PHONY: all clean test

all: $(TARGET)

$(TARGET): $(SOURCES) $(HEADERS)
	$(CC) $(CFLAGS) -o $(TARGET) $(SOURCES)

test: $(TEST_INT) $(TEST_STR)
	@echo "=== Running Integer Tests ==="
	./$(TEST_INT)
	@echo "=== Running String Tests ==="
	./$(TEST_STR)

$(TEST_INT): test_int.c vector.c $(HEADERS)
	$(CC) $(CFLAGS) -o $(TEST_INT) test_int.c vector.c

$(TEST_STR): test_str.c vector.c $(HEADERS)
	$(CC) $(CFLAGS) -o $(TEST_STR) test_str.c vector.c

clean:
	rm -f $(TARGET) $(TEST_INT) $(TEST_STR)