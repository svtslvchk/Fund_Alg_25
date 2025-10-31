CC = gcc
CFLAGS = -Wall -Wextra -Werror -Wpedantic -std=c11 -fsanitize=address -g

TARGET = lab5

SOURCES = main.c operations.c
HEADERS = operations.h

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(SOURCES) $(HEADERS)
	$(CC) $(CFLAGS) -o $(TARGET) $(SOURCES) -lm

clean:
	rm -f $(TARGET) *.o core
