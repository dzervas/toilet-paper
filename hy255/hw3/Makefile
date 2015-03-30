CFLAGS = -ansi -pedantic -Wall
CC = cc

all: list hash

list:
	@echo homework build options:
	@echo "CFLAGS   = $(CFLAGS)"
	@echo "CC       = $(CC)"
	@echo CC $(CFLAGS) -o list
	@$(CC) $(CFLAGS) -o list symtablelist.c testsymtab.c

hash:
	@echo homework build options:
	@echo "CFLAGS   = $(CFLAGS)"
	@echo "CC       = $(CC)"
	@echo CC $(CFLAGS) -o hash
	@$(CC) $(CFLAGS) -o hash symtablehash.c testsymtab.c

clean:
	rm -f hash list
