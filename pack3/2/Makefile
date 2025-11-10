CC = gcc
CFLAGS = -Wall -Werror -Wextra -Wpedantic -std=c11 -g -lm
HEADERS = vector.h

MAIN_INT = lab2
TEST_INT = test_int
TEST_STR = test_str

.PHONY: all clean test test_int test_str demo valgrind help

all: $(MAIN_INT)

$(MAIN_INT): main.c vector.c $(HEADERS)
	$(CC) $(CFLAGS) -o $(MAIN_INT) main.c vector.c

test: $(TEST_INT) $(TEST_STR)
	@echo "=== Running Integer Tests ==="
	./$(TEST_INT)
	@echo "=== Running String Tests ==="
	./$(TEST_STR)

test_int: $(TEST_INT)
	./$(TEST_INT)

test_str: $(TEST_STR)
	./$(TEST_STR)

$(TEST_INT): test_int.c vector.c $(HEADERS)
	$(CC) $(CFLAGS) -o $(TEST_INT) test_int.c vector.c

$(TEST_STR): test_str.c vector.c $(HEADERS)
	$(CC) $(CFLAGS) -o $(TEST_STR) test_str.c vector.c

demo: $(MAIN_INT)
	./$(MAIN_INT)

valgrind: $(MAIN_INT) $(TEST_INT) $(TEST_STR)
	@echo "=== Demo with Valgrind ==="
	valgrind --leak-check=full --track-origins=yes ./$(MAIN_INT)
	@echo "=== Integer Tests with Valgrind ==="
	valgrind --leak-check=full --track-origins=yes ./$(TEST_INT)
	@echo "=== String Tests with Valgrind ==="
	valgrind --leak-check=full --track-origins=yes ./$(TEST_STR)

clean:
	rm -f $(MAIN_INT) $(TEST_INT) $(TEST_STR)

