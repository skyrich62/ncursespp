/**
The MIT License (MIT)

@file window.h Interface for windows and terminal initialization.

@copyright
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

namespace CompuBrite::ncursespp {

/// RAII initialier for the windowing ncurses system.
class initializer
{
public:
    /// Initialize the ncurses system.
    initializer();

    /// Deinitializer the ncurses system and restore the terminal.
    ~initializer();

    initializer(const initializer&) = delete;
    initializer(initializer&&) = delete;

    initializer& operator=(const initializer&) = delete;
    initializer& operator=(initializer&&) = delete;

    /// Turn on or off cbreak mode.
    initializer& cbreak(bool);

    /// Turn on or off keyboard echo mode.
    initializer& echo(bool);

    /// Turn on or off keypad mode.
    initializer& keypad(bool);

    /// Turn on or off raw input mode.
    initializer& raw(bool);

    /// Turn on or off nl mode.
    initializer& nl(bool);

    /// Turn on or off intrflush mode.
    initializer& intrflush(bool);

    /// Allow color mode.
    initializer& start_color();

    /// Initialize color pairs.
    initializer& init_pair(short pair, short f, short b);

    /// Show/hide the cursor.
    initializer& cursor(int);

    /// Clear the terminal screen.
    initializer& clear();

    /// Cause the terminal screen to be redrawn.
    initializer& touch()               { ::touchwin(stdscr); return *this;}

    /// Refresh the terminal screen.
    initializer& refresh()             { ::wrefresh(stdscr); return *this;}

    /// Initialize a color via RGB values.
    initializer& color(int c, int r, int g, int b);
};

/// Used to suspend the terminal usage via RAII.
class suspender
{
public:
    /// Suspend terminal/ncurses modes temporarily.
    suspender()                   { def_prog_mode(); endwin(); }

    /// Resume terminal/curses modes.
    ~suspender()                   { reset_prog_mode(); refresh(); }
};

/// Window coordinates.  These are the coordinates on the terminal which
/// a window will occupy.
struct WindowCoords
{
    int line;
    int col;
};

/// Window size in lines and columns.
struct WindowSize
{
    int lines;
    int cols;
};

/// User interface for dealing with the window itself.
class window
{
public:
    /// Create a window without size or coordinates.
    /// This creates a window object, but no actual window on the screen.
    window() : win_(nullptr), lines_(0), cols_(0), top_(0), left_(0) { }

    /// Create a window of the given size and at the given location.
    /// @overload
    window(int lines, int cols, int top, int left);

    /// Create a window of the given size and coordinates.
    /// @overload
    window(const WindowSize &size, const WindowCoords& coords) :
        window(size.lines, size.cols, coords.line, coords.col)
    { }

    /// Destroy the window.
    ~window();

    /// Create a window.  Useful if the default ctor was previously used
    /// If this window has already been created either via the other ctors,
    /// or a previous call to create, this is a no-op.
    window& create(int lines, int cols, int top, int left);

    /// Create a window using WindowSize and WindowCoords.
    /// @overload
    window& create(const WindowSize &size, const WindowCoords &coords);

    /// Move the window cursor to the given coordinates.
    window& move(int row, int col);

    /// turn on or off some attributes
    window& attr(int a, bool onoff);

    /// turn on some attributes and turn off all others.
    window& attr(int a);

    /// Get a character from the keyboard.
    /// @param b The character will be stored here.
    window& wgetch(char &b);

    /// Get a character and throw it away, (useful for "--- more ---"
    /// prompts.
    window& wgetch()                      { char dummy; return wgetch(dummy); }

    /// Set the foreground and background color for further text to the given
    /// color_pair.
    window& color(short color_pair);

    /// Allow or disallow scrolling in the window.
    window& allow_scroll(bool ok);

    /// Get the location of the cursor in the window.
    window& get_loc(int &y, int &x);

    /// Turn keypad mode on or off for this window.
    window& keypad(bool onoff);

    /// Touch this window, (causes a complete redraw on next refresh.)
    window& touch()                         { ::touchwin(win_); return *this; }

    /// Clear the contents of this window.
    window& wclear();

    /// Refresh this window.
    window& wrefresh();

    /// Set a border around this window using the given characters.
    window& set_border(char left, char right, char top, char bottom,
                       char topLeft, char topRight,
                       char bottomLeft, char bottomRight)
    {
        wborder(win_, left, right, top, bottom, topLeft, topRight,
                bottomLeft, bottomRight);
        return *this;
    }

    /// Return the number of lines in this window.
    auto lines() const noexcept             { return lines_; }

    /// Return the number of columns in this window.
    auto cols() const noexcept              { return cols_; }

    /// Return the top line of this window relative to its parent.
    auto top() const noexcept               { return top_; }

    /// Return the left column of this window relative to its parent.
    auto left() const noexcept              { return left_; }

    /// Return the window coordinates.
    WindowCoords coords() const noexcept    { return { top_, left_}; }

    /// Return the window size.
    WindowSize size() const noexcept        { return { lines_, cols_}; }

    /// Return the underlying window handle.
    WINDOW* handle()                        { return win_; }

private:
    WINDOW *win_;
    int     lines_;
    int     cols_;
    int     top_;
    int     left_;
};

} // namespace CompuBrite::ncursespp
