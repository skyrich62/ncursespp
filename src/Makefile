CXX ?= g++
CXXFLAGS = -std=c++2a -g -I ../include
LXX = $(CXX)
LXXFLAGS = -g -lncurses
AR ?= ar
LIBDIR ?= ../lib
LIB ?= $(LIBDIR)/libwcurses.a

all: $(LIB)

clean:
	rm -rf *.o libwcurses.a $(LIB)

OBJS = \
    wstream.o \
    window.o

$(LIB): $(OBJS)
	@if [ -e "$(LIBDIR)" ] && [ ! -d "$(LIBDIR)" ]; then rm -f "$(LIBDIR)"; fi
	@mkdir -p "$(LIBDIR)"
	$(AR) -cr $@ $(OBJS)
