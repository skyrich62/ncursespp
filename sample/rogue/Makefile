CXX ?= g++
CXXFLAGS = -std=c++2a -I ../../include -g
LXXFLAGS = -L ../../lib -lwcurses -lncurses -g
LXX = $(CXX)

all: rogue

clean:
	rm -f *.o rogue

OBJS = rogue.o screen.o

rogue: $(OBJS)
	$(LXX) $(OBJS) $(LXXFLAGS) -o rogue
