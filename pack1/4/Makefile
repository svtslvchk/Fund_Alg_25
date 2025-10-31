CC = gcc
CFLAGS = -Wall -Werror -Wextra -pedantic -fsanitize=address -std=c11 -g

TARGET = lab4
SOURCES = main.c operations.c
HEADERS = operations.h

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(SOURCES) $(HEADERS)
	$(CC) $(CFLAGS) -o $(TARGET) $(SOURCES) -lm

clean:
	rm -f $(TARGET) *.o
