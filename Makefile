CC = gcc
CFLAGS = -g -std=c11

TARGET = MINISHELL

all: $(TARGET)

$(TARGET): *.c
	$(CC) $(CFLAGS) $^ -o $@

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)

.PHONY: all run clean
