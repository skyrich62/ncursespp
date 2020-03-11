#include <curses.h>
#include <string>
#include <functional>
#include <sstream>

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

    // Output
    friend window& operator<< (window &win, const char *str);
    friend window& operator<< (window &win, const std::string& str);

    // Input
    friend window& operator>> (window &win, std::string& str);

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

private:
    WINDOW *win_;
    int     lines_;
    int     cols_;
    int     top_;
    int     left_;
};

// Manipulators
struct _Attr                                { int attr_; bool onoff_; };
struct _Attr_Set                            { int attrs_; };
struct _Pos                                 { int row_; int col_; };
struct _Color_set                           { short color_pair_; };
struct _Refresh                             { };
 
inline _Attr attr(int attr, bool onoff)     { return {attr, onoff}; }
inline _Attr_Set attr(int attr)             { return {attr}; }
inline _Pos  move(int row, int col)         { return {row, col}; }
inline _Color_set color(short color_pair)   { return {color_pair}; }
inline _Refresh refresh()                   { return {}; }

window& operator<< (window &win, const _Attr& attr);
window& operator<< (window &win, const _Attr_Set& attrs);
window& operator<< (window &win, const _Pos& pos);
window& operator<< (window &win, const _Color_set& color_set);
window& operator<< (window &win, const _Refresh&);

// Output
template <typename T>
window& operator<< (window &win, T t)
{
    std::ostringstream os;
    os << t;
    return win << os.str();
}

// Input

inline window& operator>> (window &win, char &c)
{
    win.getch(c);
    return win;
}

template <typename T>
window& operator>> (window &win, T &i)
{
    std::string s;
    win >> s;
    std::istringstream is(s);
    is >> i;
    return win;
}

} // namespace ncursespp
