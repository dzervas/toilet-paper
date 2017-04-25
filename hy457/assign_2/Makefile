CC = gcc
DBUG = -g
CCFLAGS = -Wall
TA_CCFLAGS = -fPIC -shared -ldl -lssl -lcrypto
#TB_CCFLAGS = -fPIC -shared -ldl

TARGETS = Task_A main Task_B

all: $(TARGETS)

main: main.c
	$(CC) $(CCFLAGS) $(DBUG) -o $@ $<

Task_A: Task_A.c
	$(CC) $(CCFLAGS) $(TA_CCFLAGS) $(DBUG) -o $@.so $<

Task_B: Task_B.c
	$(CC) $(CCFLAGS) $(DBUG) -o $@ $<

clean:
	rm -f $(TARGETS) *.so
