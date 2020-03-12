CXXFLAGS = -std=c++2a -g
CXX = /usr/local/gcc-9.2.0/bin/g++
LXX = $(CXX)
LXXFLAGS = -g -lncurses

all: main

clean:
	rm -rf *.o main

OBJS = \
    main.o \
    screen.o \
    initializer.o \
    wstream.o \
    window.o

main.o : main.cc window.h screen.h initializer.h wstream.h
	$(CXX) main.cc $(CXXFLAGS) -c

initializer.o : initializer.cc initializer.h
	$(CXX) initializer.cc $(CXXFLAGS) -c

window.o: window.cc window.h
	$(CXX) window.cc $(CXXFLAGS) -c

screen.o: screen.cc screen.h defs.h
	$(CXX) screen.cc $(CXXFLAGS) -c

wstream.o: wstream.h window.h wstream.cc
	$(CXX) wstream.cc $(CXXFLAGS) -c

main: $(OBJS)
	$(LXX)  $(OBJS) $(LXXFLAGS) -o main
