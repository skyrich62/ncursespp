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

window& window::wclear()
{
    ::wclear(win_);
    return *this;
}

window& window::wrefresh()
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

window& window::wgetch(char &c)
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

} // namespace ncursespp
