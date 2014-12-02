.SUFFIXES: .c

FILES = $(patsubst %.cpp, %, $(wildcard *.cpp))
CXXFLAGS = -g -Wall -O2
CXX = g++

all: $(FILES)

.cpp:
	@echo homework build options:
	@echo "CXXFLAGS   = $(CXXFLAGS)"
	@echo "LDFLAGS  = $(LDFLAGS)"
	@echo "CXX       = $(CXX)"
	@echo CXX $(CXXFLAGS) -o $(@)
	@$(CXX) $(CXXFLAGS) -o $@ $< $(LDFLAGS)

clean:
	rm -rf $(FILES) *.dSYM

error:
	@echo "Please specify name of project to build (source file without .cpp extension)"

.PHONY: all clean error
