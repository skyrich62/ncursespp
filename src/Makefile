CXXFLAGS = -std=c++2a -g
CXX = /usr/local/gcc-9.2.0/bin/g++ -I ../include
LXX = $(CXX)
LXXFLAGS = -g -lncurses

all: libwcurses.a

clean:
	rm -rf *.o libwcurses.a

OBJS = \
    wstream.o \
    window.o

libwcurses.a: $(OBJS)
	ar -cr libwcurses.a $(OBJS) 
	cp libwcurses.a ../lib
