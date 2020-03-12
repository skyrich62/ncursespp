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

    window& get_window()                    { return buf_.get_window(); }

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
