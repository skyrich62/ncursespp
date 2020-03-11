#include <curses.h>

namespace ncursespp {

class initializer
{
public:
    initializer();
    ~initializer();

    initializer(const initializer&) = delete;
    initializer(initializer&&) = delete;

    initializer& operator=(const initializer&) = delete;
    initializer& operator=(initializer&&) = delete;

    initializer& cbreak(bool);
    initializer& echo(bool);
    initializer& keypad(bool);
    initializer& raw(bool);
    initializer& nl(bool);
    initializer& intrflush(bool);
    initializer& start_color();
    initializer& init_pair(short pair, short f, short b);
    initializer& cursor(int);
    initializer& clear();
    initializer& touch()               { ::touchwin(stdscr); return *this;}
    initializer& refresh()             { ::wrefresh(stdscr); return *this;}
    initializer& color(int c, int r, int g, int b);
};

class suspender
{
public:
    suspender()                   { def_prog_mode(); endwin(); }
   ~suspender()                   { reset_prog_mode(); refresh(); }
};

} // namespace ncursespp
