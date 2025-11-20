CC = gcc
CFLAGS = -Wall -Werror -Wextra -Wpedantic -std=c11 -g
TARGET = test_complete
SOURCES = test.c liver.c linked_list.c
HEADERS = liver.h linked_list.h

.PHONY: all clean test

all: $(TARGET)

$(TARGET): $(SOURCES) $(HEADERS)
	$(CC) $(CFLAGS) -o $(TARGET) $(SOURCES)

test: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)