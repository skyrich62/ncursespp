#include <curses.h>
#include <string>
//#include <functional>
#include <sstream>
#include <iostream>

#undef getch

namespace ncursespp {

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
    window& getch(char &b);
    window& color(short color_pair);
    window& allow_scroll(bool ok);
    window& get_loc(int &y, int &x);
    window& keypad(bool onoff);
    window& touch()                         { ::touchwin(win_); return *this; }

    window& clear();
    window& refresh();
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
    auto handle()                           { return win_; }

private:
    WINDOW *win_;
    int     lines_;
    int     cols_;
    int     top_;
    int     left_;
};

} // namespace ncursespp
