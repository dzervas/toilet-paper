.SUFFIXES: .c

FILES = $(patsubst %.c, %, $(wildcard *.c))
CFLAGS = -ansi -pedantic -Werror -O2
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
