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

