CC = gcc
CFLAGS = -Wall -Wextra -I./include

SRC_DIR = src
SRCS = $(SRC_DIR)/main.c \
       $(SRC_DIR)/scan_input.c \
       $(SRC_DIR)/commands.c \
       $(SRC_DIR)/signals.c \
       $(SRC_DIR)/exception_handling.c

TARGET = minishell

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) $(SRCS) -o $(TARGET)

clean:
	rm -f $(TARGET)

run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run
