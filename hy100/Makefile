.SUFFIXES: .c

FILES = $(patsubst %.c, %, $(wildcard *.c))
CFLAGS = -ansi -pedantic -Werror -O2
CPPFLAGS = -D_BSD_SOURCE -D_POSIX_C_SOURCE=200809L
CC = cc

all: $(FILES)

.c:
	@echo homework build options:
	@echo "CFLAGS   = $(CFLAGS)"
	@echo "LDFLAGS  = $(LDFLAGS)"
	@echo "CC       = $(CC)"
	@echo CC $(CFLAGS) -o $(@)
	@$(CC) $(CFLAGS) -o $@ $< $(LDFLAGS)

clean:
	rm -f $(FILES)

.PHONY: all clean
