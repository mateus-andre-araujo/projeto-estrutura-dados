CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -Iinclude
TARGET = sistema_biblioteca
SRCS = src/main.c src/bst.c src/estrutura.c
OBJS = $(SRCS:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET) $(TARGET).exe

.PHONY: all clean
