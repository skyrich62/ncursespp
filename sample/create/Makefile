CXX = /usr/local/gcc-9.2.0/bin/g++ 
CXXFLAGS = -std=c++2a -I ../../include -g
LXXFLAGS = -lncurses -L ../../lib -lwcurses  -g
LXX = $(CXX)

all: test1

clean:
	rm -f *.o test1

test1: test1.o
	$(LXX) test1.o $(LXXFLAGS) -o test1

