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

} // namespace ncursespp


// This program demonstrates creating the actual ncurses window *after*
// constructing an ncursespp::window object.

#include "ncursespp/wstream.h"

namespace ncp = ncursespp;

int main()
{
    ncp::initializer init;
    init.echo(false).cbreak(true).clear().start_color().
         init_pair(1, COLOR_BLACK, COLOR_YELLOW);

    ncp::windowstream win;
    win.create(0, 0, 0, 0);

    win << ncp::color(1) << "Hello world!\n" << ncp::refresh();
    for (auto i = 0u; i< 10; ++i) {
        win << "Line #" << i+1 << '\n';
    }
    win << ncp::refresh();
    char dummy;
    win.wgetch(dummy);
    return 0;
}
   
