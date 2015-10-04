.SUFFIXES: .java .class

CLASSES = $(patsubst %.java, %, $(wildcard *.java))
JC = javac
JFLAGS = 

.java:
	@echo "Building file..."
	$(JC) $(JFLAGS) $<

all: $(CLASSES)

clean:
	rm -rf *.class Encrypted*

fresh: clean all
