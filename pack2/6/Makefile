CC = gcc
CFLAGS = -Wall -Wextra -Werror -Wpedantic -std=c11 -fsanitize=address -g

TARGET = lab6
TEST_TARGET = test_lab6

SOURCES = main.c operations.c
TEST_SOURCES = tests.c operations.c
HEADERS = operations.h

.PHONY: all clean test run

all: $(TARGET)

$(TARGET): $(SOURCES) $(HEADERS)
	$(CC) $(CFLAGS) -o $(TARGET) $(SOURCES) -lm

$(TEST_TARGET): $(TEST_SOURCES) $(HEADERS)
	$(CC) $(CFLAGS) -o $(TEST_TARGET) $(TEST_SOURCES) -lm

test: $(TEST_TARGET)
	./$(TEST_TARGET)

run: $(TARGET)
	./$(TARGET) students.csv trace.txt

clean:
	rm -f $(TARGET) $(TEST_TARGET) *.o core trace.txt test_trace.txt

