#include <curses.h>
#include <string>
#include <functional>

#undef getch

namespace ncursespp {

struct _Attr { int attr_; bool onoff_; };

struct _Pos { int row_; int col_; };

struct _Color_set { short color_pair_; };

inline _Attr attr(int attr, bool onoff)    { return {attr, onoff}; }
inline _Pos  move(int row, int col)        { return {row, col}; }
inline _Color_set color(short color_pair)  { return {color_pair}; }

class window
{
public:
    window(int rows, int cols, int row, int col);
    friend window& operator<< (window &win, const char *str);
    friend window& operator<< (window &win, const std::string& str);

    friend window& operator>> (window &win, std::string& str);
    
    window& move(int row, int col);
    window& attr(int attr, bool onoff);
    window& clear();
    window& refresh();
    window& getch(char &b);
    window& color(short color_pair);

private:
    WINDOW *win_;
};

window& operator<< (window &win, long long int i);
window& operator<< (window &win, double d);
window& operator<< (window &win, const _Attr& attr);
window& operator<< (window &win, const _Pos& pos);
window& operator<< (window &win, const _Color_set& color_set);

window& operator>> (window &win, char &c);
window& operator>> (window &win, long long int &i);
window& operator>> (window &win, double &d);

} // namespace ncursespp
