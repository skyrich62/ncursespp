#include "initializer.h"

namespace ncursespp {

initializer::initializer()
{
    ::initscr();
}

initializer::~initializer()
{
    ::endwin();
}

initializer&
initializer::cbreak(bool yn)
{
    yn ? ::cbreak() : ::nocbreak();
    return *this;
}

initializer&
initializer::echo(bool yn)
{
    yn ? ::echo() : ::noecho();
    return *this;
}

initializer&
initializer::keypad(bool yn)
{
    ::keypad(::stdscr, yn);
    return *this;
}

initializer&
initializer::raw(bool yn)
{
    yn ? ::raw() : ::noraw();
    return *this;
}

initializer&
initializer::nl(bool yn)
{
    yn ? ::nl() : ::nonl();
    return *this;
}

initializer&
initializer::start_color()
{
    ::start_color();
    return *this;
}

initializer&
initializer::init_pair(short pair, short fg, short bg)
{
    ::init_pair(pair, fg, bg);
    return *this;
}

initializer&
initializer::cursor(int visibility)
{
    ::curs_set(visibility);
    return *this;
}

initializer&
initializer::clear()
{
    ::wclear(stdscr);
    return *this;
}

initializer&
initializer::color(int c, int r, int g, int b)
{
    ::init_color(c, r, g, b);
    return *this;
}
} // namespace ncursespp
