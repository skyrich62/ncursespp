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

#include <curses.h>
#include <string>
#include <sstream>
#include <iostream>

#undef getch

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

struct WindowCoords
{
    int line;
    int col;
};

struct WindowSize
{
    int lines;
    int cols;
};

class window
{
public:
    window(int lines, int cols, int top, int left);
    window(const WindowSize &size, const WindowCoords& coords) :
        window(size.lines, size.cols, coords.line, coords.col)
    { }
   ~window();

    window& move(int row, int col);
    // turn on or off some attributes
    window& attr(int a, bool onoff);

    // turn on some attributes and turn off all others.
    window& attr(int a);
    window& wgetch(char &b);
    window& color(short color_pair);
    window& allow_scroll(bool ok);
    window& get_loc(int &y, int &x);
    window& keypad(bool onoff);
    window& touch()                         { ::touchwin(win_); return *this; }

    window& wclear();
    window& wrefresh();
    window& set_border(char left, char right, char top, char bottom,
                       char topLeft, char topRight,
                       char bottomLeft, char bottomRight)
    {
        wborder(win_, left, right, top, bottom, topLeft, topRight,
                bottomLeft, bottomRight);
        return *this;
    }

    auto lines() const noexcept             { return lines_; }
    auto cols() const noexcept              { return cols_; }
    auto top() const noexcept               { return top_; }
    auto left() const noexcept              { return left_; }

    WindowCoords coords() const noexcept    { return { top_, left_}; }
    WindowSize size() const noexcept        { return { lines_, cols_}; }
    WINDOW* handle()                        { return win_; }

private:
    WINDOW *win_;
    int     lines_;
    int     cols_;
    int     top_;
    int     left_;
};

} // namespace ncursespp
