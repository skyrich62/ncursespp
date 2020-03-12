#include "wstream.h"

namespace ncursespp {

int
windowbuf::output_buffer()
{
    int num = buf_type::pptr() - buf_type::pbase();
    if (num > 0) {
        auto result = waddnstr(win_.handle(), obuf, num * char_size);
        if (result == ERR) {
            return traits_type::eof();
        }
        buf_type::pbump(-num);
    }
    return num;
}

windowbuf::int_type
windowbuf::overflow(int_type c)
{
    if (c != traits_type::eof()) {
        *buf_type::pptr() = c;
        buf_type::pbump(1);
    }
    if (output_buffer() == traits_type::eof()) {
        return traits_type::eof();
    }
    return traits_type::not_eof(c);
}

int
windowbuf::sync()
{
    if (output_buffer() == traits_type::eof()) {
        return -1;
    }
    return 0;
}

int
windowbuf::underflow()
{
    if (buf_type::gptr() < buf_type::egptr()) {
        return *buf_type::gptr();
    }

    win_.wgetch(*ibuf);
    buf_type::setg(ibuf, ibuf, ibuf + 1);
    return *buf_type::gptr();
}

} // namespace ncursespp

// Manipulators
std::ostream&
operator<<(std::ostream &os, const ncursespp::_Attr_Set &attrs)
{
    os.flush();
    auto &win = dynamic_cast<ncursespp::windowstream&>(os);
    win.get_window().attr(attrs.attrs_);
    return os;
}

std::ostream&
operator<<(std::ostream &os, const ncursespp::_Attr &attr)
{
    os.flush();
    auto &win = dynamic_cast<ncursespp::windowstream&>(os);
    win.get_window().attr(attr.attr_, attr.onoff_);
    return os;
}

std::ostream&
operator<<(std::ostream &os, const ncursespp::_Pos &pos)
{
    os.flush();
    auto &win = dynamic_cast<ncursespp::windowstream&>(os);
    win.get_window().move(pos.row_, pos.col_);
    return os;
}

std::ostream&
operator<<(std::ostream &os, const ncursespp::_Color_set &colors)
{
    os.flush();
    auto &win = dynamic_cast<ncursespp::windowstream&>(os);
    win.get_window().color(colors.color_pair_);
    return os;
}

std::ostream&
operator<<(std::ostream &os, const ncursespp::_Refresh&)
{
    os.flush();
    auto &win = dynamic_cast<ncursespp::windowstream&>(os);
    win.get_window().wrefresh();
    return os;
}

