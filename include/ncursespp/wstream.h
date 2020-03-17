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

#include <streambuf>
#include <istream>
#include <ostream>
#include "window.h"

namespace ncursespp {

class windowbuf : public std::basic_streambuf<char>
{
public:
    using inherited = std::basic_streambuf<char>;
    using char_type = char;
    using buf_type = std::basic_streambuf<char_type>;
    using int_type = typename buf_type::int_type;
    using traits_type = typename inherited::traits_type;

protected:
    static const int char_size = sizeof(char_type);
    static const int SIZE = 128;
    char_type obuf[SIZE];
    char_type ibuf[SIZE];

    window win_;

private:
    void init()
    {
        buf_type::setp(obuf, obuf + (SIZE -1));
        buf_type::setg(ibuf, ibuf, ibuf);
    }


public:
    windowbuf() : inherited()
    {
        init();
    }

    windowbuf(const WindowSize& size, const WindowCoords& coords) : 
        inherited(), win_(size, coords) 
    {
        init();
    }

    windowbuf(int lines, int cols, int top, int left) : 
        inherited(), win_(lines, cols, top, left) 
    {
        init();
    }

    windowbuf(window&& win) : inherited(), win_(std::move(win))
    {
        init();
    }

    auto create(const WindowSize &size, const WindowCoords &coords)
    {
        win_.create(size, coords);
        return win_.handle();
    }

    auto create(int lines, int cols, int top, int left)
    {
        return create({lines, cols}, {top, left});
    }
    
    void set_window(window &&win)           { win_ = std::move(win); }
    window& get_window()                    { return win_; }

protected:
    int output_buffer();
    virtual int_type overflow(int_type c) override;
    virtual int sync() override;
    virtual int underflow() override;

};

class windowstream : public std::basic_iostream<char>
{
public:
    using inherited = std::basic_iostream<char>;
    using type_type = char;
    using stream_type = inherited;
    using buf_type = windowbuf;

protected:
    buf_type buf_;

public:
    windowstream() :
        stream_type(&buf_),
        buf_()
    {
    }

    windowstream(const WindowSize &size, const WindowCoords &coords) :
        stream_type(&buf_),
        buf_(size, coords)
    {
    }

    windowstream(int lines, int cols, int top, int left) :
        stream_type(&buf_),
        buf_(lines, cols, top, left)
    {
    }

    windowstream(window&& win) : 
        stream_type(&buf_),
        buf_(std::move(win))
    {
    }

    bool create(const WindowSize &size, const WindowCoords &coords)
    {
        return buf_.create(size, coords);
    }

    bool create(int lines, int cols, int top, int left)
    {
        return buf_.create(lines, cols, top, left);
    }

    auto &get_window()                      { return buf_.get_window(); }
    auto &wgetch(char c)                    { return get_window().wgetch(c); }
    auto &attr(int a)                       { return get_window().attr(a); }
    auto &color(short c)                    { return get_window().color(c); }
    auto &allow_scroll(bool ok)             { return get_window().allow_scroll(ok); }
    auto &get_loc(int &y, int &x)           { return get_window().get_loc(y, x); }
    auto &wclear()                          { return get_window().wclear(); }
    auto &touch()                           { return get_window().touch(); }
    auto &keypad(bool onoff)                { return get_window().keypad(onoff); }
    auto &wrefresh()                        { return get_window().wrefresh(); }
    auto lines()                            { return get_window().lines(); }
    auto cols()                             { return get_window().cols(); }
    auto top()                              { return get_window().top(); }
    auto left()                             { return get_window().left(); }
};

// Manipulators
struct _Attr                                { int attr_; bool onoff_; };
struct _Attr_Set                            { int attrs_; };
struct _Pos                                 { int row_; int col_; };
struct _Color_set                           { short color_pair_; };
struct _Refresh                             { };
 
/// Turn on or off some attributes or colors
inline _Attr attr(int attr, bool onoff)     { return {attr, onoff}; }

/// Set the active attributes, turning off all others.
inline _Attr_Set attr(int attr)             { return {attr}; }

/// Move the cursor.
inline _Pos  move(int row, int col)         { return {row, col}; }

/// Set the active foreground and background colors
inline _Color_set color(short color_pair)   { return {color_pair}; }

/// Refresh the window.
inline _Refresh refresh()                   { return {}; }

} // ncursespp

std::ostream& operator<< (std::ostream &win, const ncursespp::_Attr& attr);
std::ostream& operator<< (std::ostream &win, const ncursespp::_Attr_Set& attrs);
std::ostream& operator<< (std::ostream &win, const ncursespp::_Pos& pos);
std::ostream& operator<< (std::ostream &win, const ncursespp::_Color_set& color_set);
std::ostream& operator<< (std::ostream &win, const ncursespp::_Refresh&);
