CXX ?= g++
CXXFLAGS = -std=c++2a -I ../../include
LXXFLAGS = -L ../../lib -lwcurses -lncurses
LXX = $(CXX)

all: hello

clean:
	rm -f *.o hello

hello: hello.o
	$(LXX) hello.o $(LXXFLAGS) -o hello

