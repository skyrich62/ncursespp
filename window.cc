/**
The MIT License (MIT)

Copyright (c) 2020 Rich Newman

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

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
