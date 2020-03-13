CXXFLAGS = -std=c++2a -g
CXX = /usr/local/gcc-9.2.0/bin/g++
LXX = $(CXX)
LXXFLAGS = -g -lncurses

all: main

clean:
	rm -rf *.o main libwcurses.a

OBJS = \
    wstream.o \
    window.o

libwcurses.a: $(OBJS)
	ar -cr libwcurses.a $(OBJS) 

main.o : main.cc window.h screen.h wstream.h
	$(CXX) main.cc $(CXXFLAGS) -c

window.o: window.cc window.h
	$(CXX) window.cc $(CXXFLAGS) -c

screen.o: screen.cc screen.h defs.h
	$(CXX) screen.cc $(CXXFLAGS) -c

wstream.o: wstream.h window.h wstream.cc
	$(CXX) wstream.cc $(CXXFLAGS) -c

main: libwcurses.a main.o screen.o
	$(LXX)  $(OBJS) main.o screen.o $(LXXFLAGS) -L . -lwcurses -o main
