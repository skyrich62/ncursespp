CXX = /usr/local/gcc-9.2.0/bin/g++ 
CXXFLAGS = -std=c++2a -I ../../include
LXXFLAGS = -lncurses -L ../../lib -lwcurses 
LXX = $(CXX)

all: hello

clean:
	rm -f *.o hello

hello: hello.o
	$(LXX) hello.o $(LXXFLAGS) -o hello

