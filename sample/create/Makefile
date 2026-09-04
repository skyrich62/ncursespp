CXX ?= g++
CXXFLAGS = -std=c++2a -I ../../include -g
LXXFLAGS = -L ../../lib -lwcurses -lncurses -g
LXX = $(CXX)

all: test1

clean:
	rm -f *.o test1

test1: test1.o
	$(LXX) test1.o $(LXXFLAGS) -o test1

