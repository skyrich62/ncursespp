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

#include "ncursespp/wstream.h"

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
    auto win = dynamic_cast<ncursespp::windowstream*>(&os);
    if (win) win->get_window().attr(attrs.attrs_);
    return os;
}

std::ostream&
operator<<(std::ostream &os, const ncursespp::_Attr &attr)
{
    os.flush();
    auto win = dynamic_cast<ncursespp::windowstream*>(&os);
    if (win) win->get_window().attr(attr.attr_, attr.onoff_);
    return os;
}

std::ostream&
operator<<(std::ostream &os, const ncursespp::_Pos &pos)
{
    os.flush();
    auto win = dynamic_cast<ncursespp::windowstream*>(&os);
    if (win) win->get_window().move(pos.row_, pos.col_);
    return os;
}

std::ostream&
operator<<(std::ostream &os, const ncursespp::_Color_set &colors)
{
    os.flush();
    auto win = dynamic_cast<ncursespp::windowstream*>(&os);
    if (win) win->get_window().color(colors.color_pair_);
    return os;
}

std::ostream&
operator<<(std::ostream &os, const ncursespp::_Refresh&)
{
    os.flush();
    auto win = dynamic_cast<ncursespp::windowstream*>(&os);
    if (win) win->get_window().wrefresh();
    return os;
}
