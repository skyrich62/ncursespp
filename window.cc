#include <sstream>

#include "window.h"

namespace ncursespp {

window::window(int lines, int cols, int top, int left)
{
    win_ = ::newwin(lines, cols, top, left);
    lines_ = lines ? lines : LINES;
    cols_  = cols ? cols : COLS;
    top_ = top;
    left_ = left;
}

window::~window()
{
    delwin(win_);
}

window& window::move(int row, int col)
{
    ::wmove(win_, row, col);
    return *this;
}

window& window::attr(int a, bool onoff)
{
    onoff ? ::wattron(win_, a) : ::wattroff(win_, a);
    return *this;
}

window& window::attr(int a)
{
    wattrset(win_, a);
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

window& window::allow_scroll(bool ok)
{
    ::scrollok(win_, ok ? 1 : 0);
    return *this;
}

window& window::keypad(bool onoff)
{
    ::keypad(win_, onoff ? 1 : 0);
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

window& window::get_loc(int &y, int &x)
{
    getyx(win_, y, x);
    return *this;
}

// Output
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

// Manipulators
window&
operator<<(window &win, const _Attr_Set &attrs)
{
     win.attr(attrs.attrs_);
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
operator<<(window &win, const _Refresh&)
{
    win.refresh();
    return win;
}

// Input
window&
operator>>(window &win, std::string &str)
{
    char buffer[1024];
    ::wgetnstr(win.win_, buffer, sizeof(buffer));
    str = buffer;
    return win;
}

} // namespace ncursespp
