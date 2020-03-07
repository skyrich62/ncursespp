#include <sstream>

#include "window.h"

namespace ncursespp {

window::window(int rows, int cols, int row, int col)
{
    win_ = ::newwin(rows, cols, row, col);
}

window& window::move(int row, int col)
{
    ::wmove(win_, row, col);
    return *this;
}

window& window::attr(int attr, bool onoff)
{
    onoff ? ::wattron(win_, attr) : ::wattroff(win_, attr);
    return *this;
}

window& window::clear()
{
    ::wclear(win_);
    return *this;
}

window& window::refresh()
{
    ::wrefresh(win_);
    return *this;
}

window& window::getch(char &c)
{
    c = ::wgetch(win_);
    return *this;
}

window& window::color(short color_pair)
{
    ::wcolor_set(win_, color_pair, nullptr);
    return *this;
}

window&
operator<<(window &win, long long int i)
{
    std::ostringstream os;
    os << i;
    return win << os.str();
}

window&
operator<<(window &win, double d)
{
    std::ostringstream os;
    os << d;
    return win << os.str();
}

window&
operator<<(window &win, const char *str)
{
    ::waddstr(win.win_, str);
    return win;
}

window&
operator<<(window &win, const std::string &str)
{
    ::waddstr(win.win_, str.c_str());
    return win;
}

window&
operator<<(window &win, const _Attr &attr)
{
     win.attr(attr.attr_, attr.onoff_);
     return win;
}

window&
operator<<(window &win, const _Pos &pos)
{
    win.move(pos.row_, pos.col_);
    return win;
}

window&
operator<<(window &win, const _Color_set &colors)
{
    win.color(colors.color_pair_);
    return win;
}

window&
operator>>(window &win, char &c)
{
    win.getch(c);
    return win;
}

window&
operator>>(window &win, std::string &str)
{
    char buffer[1024];
    ::wgetnstr(win.win_, buffer, sizeof(buffer));
    str = buffer;
    return win;
}

window&
operator>>(window &win, long long int &i)
{
    std::string s;
    win >> s;
    std::istringstream is(s);
    is >> i;
    return win;
}

window&
operator>>(window &win, double &d)
{
    std::string s;
    win >> s;
    std::istringstream is(s);
    is >> d;
    return win;
}


} // namespace ncursespp
