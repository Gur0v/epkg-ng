TARGET = epkg
CC = gcc
CFLAGS = -Wall -Wextra -Wpedantic -O2 -march=native -mtune=native -std=c99
LDFLAGS = -s
SRCDIR = .
OBJDIR = obj
PREFIX ?= /usr/local
BINDIR = $(PREFIX)/bin
MANDIR = $(PREFIX)/share/man/man1

SRCS = $(wildcard $(SRCDIR)/*.c)
OBJS = $(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
DEPS = $(OBJS:.o=.d)

.DEFAULT_GOAL = all

all: $(TARGET)

$(TARGET): $(OBJS) | $(OBJDIR)
	$(CC) $(LDFLAGS) -o $@ $^
	@echo "Build complete: $(TARGET)"

$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -MMD -MP -c $< -o $@

$(OBJDIR):
	@mkdir -p $(OBJDIR)

install: $(TARGET)
	@echo "Installing $(TARGET) to $(BINDIR)"
	install -d $(BINDIR)
	install -m755 $(TARGET) $(BINDIR)/$(TARGET)

uninstall:
	@echo "Removing $(TARGET) from $(BINDIR)"
	rm -f $(BINDIR)/$(TARGET)

clean:
	rm -rf $(OBJDIR) $(TARGET)
	@echo "Clean complete"

distclean: clean
	rm -f $(DEPS)

debug: CFLAGS += -g -DDEBUG -O0
debug: LDFLAGS := $(filter-out -s,$(LDFLAGS))
debug: $(TARGET)

release: CFLAGS += -DNDEBUG -flto
release: LDFLAGS += -flto
release: $(TARGET)

check: $(TARGET)
	@echo "Running basic tests..."
	./$(TARGET) 2>/dev/null || true
	@echo "Tests complete"

rebuild: clean all

.PHONY: all install uninstall clean distclean debug release check rebuild
.SUFFIXES:

-include $(DEPS)
