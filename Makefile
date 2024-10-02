TARGET = epkg

CC = gcc

CFLAGS = -Wall -Wextra -O2

SRCS = epkg.c

OBJS = $(SRCS:.c=.o)

PREFIX = /usr/local/bin

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

install: $(TARGET)
	install -Dm755 $(TARGET) $(PREFIX)/$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)

uninstall:
	rm -f $(PREFIX)/$(TARGET)

rebuild: clean all

.PHONY: all clean rebuild install uninstall
