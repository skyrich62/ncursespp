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

#include <iomanip>
#include <vector>

#include "screen.h"

namespace ncp = ncursespp;


int main()
{
    ScreenUI scr;
    char dummy;

    scr.msg1() << "Message 1" << ncp::refresh();
    scr.msg2() << "Message 2" << ncp::refresh();
    scr.msg3() << "Message 3" << ncp::refresh();
    scr.more() << "*** MORE ***" << ncp::refresh();


    scr.data() << "Data" << ncp::refresh();
    scr.time() << "Time" << ncp::refresh();
    scr.flag() << "Flags" << ncp::refresh();
    scr.phase() << "Phase" << ncp::refresh();
    scr.com() << "Com" << ncp::refresh();

    scr.msg1().wgetch(dummy);
    scr.more().wclear().wrefresh();
    for (auto i = 0u; i < scr.level().lines(); ++i) {
        if (i < 26) {
            scr.level() << ncp::color(i);
        } else if (i == 30) {
            scr.level() << ncp::attr(COLOR_PAIR(9) | A_BOLD);
        }
        scr.level() << "Level, line: " << std::setw(10) << std::left << i 
                    << "\n" << ncp::attr(A_NORMAL);
    }
    scr.level().wgetch(dummy);

    scr.menu() << "1. menu\n"
               << ncp::color(2) << "2. menu\n"
               << ncp::color(3) << "3. menu" << ncp::refresh();

    scr.menu().wgetch(dummy);
    scr.menu().wclear();
    scr.level().wrefresh().touch();
    scr.menu().wgetch(dummy);

    auto i = 0u;
    for (auto& win : scr.showLine()) {
        (*win) << "Show line #" << ++i << ncp::refresh();
    }
    scr.showLine()[0]->wgetch(dummy);

    return 0;
}

