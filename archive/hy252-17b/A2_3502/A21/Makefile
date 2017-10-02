.SUFFIXES: .java .class

CLASSES = $(patsubst %.java, %, $(wildcard *.java))
JC = javac
JFLAGS = -cp .

.java:
	@echo "Building file..."
	$(JC) $(JFLAGS) $<

all: $(CLASSES)

clean:
	rm -rf *.class

fresh: clean all

test: all
	java $(JFLAGS) $(CLASSES)
