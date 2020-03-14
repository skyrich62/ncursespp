CXX = /usr/local/gcc-9.2.0/bin/g++ 
CXXFLAGS = -std=c++2a -I ../../include
LXXFLAGS = -lncurses -L ../../lib -lwcurses 
LXX = $(CXX)

all: rogue

clean:
	rm -f *.o rogue

OBJS = rogue.o screen.o

rogue: $(OBJS)
	$(LXX) $(OBJS) $(LXXFLAGS) -o rogue
