CXXFLAGS = -std=c++17 -g
CXX = /usr/local/gcc-9.2.0/bin/g++
LXX = $(CXX)
LXXFLAGS = -g -lncurses

all: main

clean:
	rm -rf *.o main

OBJS = \
    main.o \
    initializer.o \
    window.o

initializer.o : initializer.cc initializer.h
	$(CXX) initializer.cc $(CXXFLAGS) -c

window.o: window.cc window.h
	$(CXX) window.cc $(CXXFLAGS) -c

main: $(OBJS)
	$(LXX)  $(OBJS) $(LXXFLAGS) -o main
