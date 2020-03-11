#include "screen.h"

namespace ncp = ncursespp;

int main()
{
    ScreenUI scr;
    scr.msg1() << "Message 1" << ncp::refresh();
    scr.msg2() << "Message 2" << ncp::refresh();
    scr.msg3() << "Message 3" << ncp::refresh();
    scr.more() << "*** MORE ***" << ncp::refresh();
    scr.data() << "Data" << ncp::refresh();
    scr.time() << "Time" << ncp::refresh();
    scr.flag() << "Flags" << ncp::refresh();
    scr.phase() << "Phase" << ncp::refresh();
    scr.com() << "Com" << ncp::refresh();

    char dummy;
    for (auto i = 0u; i < scr.level().lines(); ++i) {
        if (i < 25) {
            scr.level() << ncp::color(i+1);
        }
        scr.level() << "Level, line " << i << "\n" << ncp::color(0);
    }
    scr.level().refresh();
    scr.level().getch(dummy);

    scr.menu() << "1. menu\n"
               << ncp::color(2) << "2. menu\n"
               << ncp::color(3) << "3. menu" << ncp::refresh();

    scr.menu().getch(dummy);
    scr.menu().clear();
    scr.level().refresh().touch();
    scr.menu().getch(dummy);

    auto i = 0u;
    for (auto& win : scr.showLine()) {
        win->clear().touch().refresh();
        *win << "Show line #" << ++i << "\n";
        win->refresh();
    }
    scr.showLine()[0]->getch(dummy);

    return 0;
}

