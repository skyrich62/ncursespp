CXX = /usr/local/gcc-9.2.0/bin/g++ 
CXXFLAGS = -std=c++2a -I ../../include -g
LXXFLAGS = -lncurses -L ../../lib -lwcurses  -g
LXX = $(CXX)

all: rogue

clean:
	rm -f *.o rogue

OBJS = rogue.o screen.o

rogue: $(OBJS)
	$(LXX) $(OBJS) $(LXXFLAGS) -o rogue
