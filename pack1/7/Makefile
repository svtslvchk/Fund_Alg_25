CC = gcc
CFLAGS = -Wall -Werror -Wextra -Wpedantic -fsanitize=address -std=c11 -g
TARGET = app
SOURCES = main.c operations.c
HEADERS = operations.h

TEST_RUNNER = run_tests
TEST_SOURCES = tests.c operations.c

.PHONY: all clean internal_tests test test_errors test_functionality

all: $(TARGET)

$(TARGET): $(SOURCES) $(HEADERS)
	$(CC) $(CFLAGS) -o $(TARGET) $(SOURCES)

internal_tests: $(TEST_RUNNER)
	@echo "--- Running Internal (C tests.c) ---"
	./$(TEST_RUNNER)
	@echo "------------------------------------"

$(TEST_RUNNER): $(TEST_SOURCES) $(HEADERS)
	$(CC) $(CFLAGS) -o $(TEST_RUNNER) $(TEST_SOURCES)

clean:
	rm -f $(TARGET) $(TEST_RUNNER) input.txt output.txt expected.txt tmp_*.txt

test: all
	@echo "--- Running External Tests ---"
	@printf "1010 77 1A F\nhello 123 Z9\n0005\n" > input.txt
	@$(MAKE) test_errors
	@$(MAKE) test_functionality
	@$(MAKE) clean
	@echo "--- External Tests Finished ---"

test_errors:
	@echo "\n--> Testing Error Handling..."
	-@./$(TARGET) >/dev/null 2>&1; if [ $$? -eq 1 ]; then echo "[PASS] No arguments"; else echo "[FAIL] No arguments"; fi
	-@./$(TARGET) non_existent_input.txt out.txt >/dev/null 2>&1; if [ $$? -eq 3 ]; then echo "[PASS] Input file not found"; else echo "[FAIL] Input file not found"; fi
	-@./$(TARGET) input.txt /root/out.txt >/dev/null 2>&1; if [ $$? -eq 3 ]; then echo "[PASS] Cannot open output file (permission)"; else echo "[FAIL] Cannot open output file (permission)"; fi

test_functionality:
	@echo "\n--> Testing Functionality..."
	-@./$(TARGET) input.txt output.txt
	@printf "1010 2 10\n77 8 63\n1A 11 21\nF 16 15\nhello 25 6873049\n123 4 27\nZ9 36 1269\n5 6 5\n" > expected.txt
	@diff -w output.txt expected.txt >/dev/null 2>&1 && echo "[PASS] functionality" || (echo "[FAIL] functionality"; echo "---- ACTUAL ----"; cat output.txt; echo "---- EXPECTED ----"; cat expected.txt)
