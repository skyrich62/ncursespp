#include "screen.h"
#include <iomanip>

namespace ncp = ncursespp;

int main()
{

    ncp::initializer init;
    init.echo(false).cbreak(true).clear().start_color()
        .init_pair(1, COLOR_BLACK, COLOR_BLUE)
        .init_pair(2, COLOR_BLACK, COLOR_GREEN)
        .init_pair(3, COLOR_BLACK, COLOR_RED)
        .init_pair(4, COLOR_BLACK, COLOR_WHITE)
        .init_pair(5, COLOR_BLACK, COLOR_YELLOW)
        .init_pair(6, COLOR_BLUE, COLOR_BLACK)
        .init_pair(7, COLOR_BLUE, COLOR_WHITE)
        .init_pair(8, COLOR_CYAN, COLOR_BLACK)
        .init_pair(9, COLOR_GREEN, COLOR_BLACK)
        .init_pair(10, COLOR_GREEN, COLOR_BLUE)
        .init_pair(11, COLOR_GREEN, COLOR_RED)
        .init_pair(12, COLOR_GREEN, COLOR_YELLOW)
        .init_pair(13, COLOR_MAGENTA, COLOR_BLACK)
        .init_pair(14, COLOR_MAGENTA, COLOR_WHITE)
        .init_pair(15, COLOR_RED, COLOR_BLACK)
        .init_pair(16, COLOR_RED, COLOR_WHITE)
        .init_pair(17, COLOR_WHITE, COLOR_BLACK)
        .init_pair(18, COLOR_WHITE, COLOR_BLUE)
        .init_pair(19, COLOR_WHITE, COLOR_RED)
        .init_pair(20, COLOR_WHITE, COLOR_YELLOW)
        .init_pair(21, COLOR_YELLOW, COLOR_BLACK)
        .init_pair(22, COLOR_YELLOW, COLOR_BLUE)
        .init_pair(23, COLOR_YELLOW, COLOR_RED)
        .init_pair(24, COLOR_YELLOW, COLOR_WHITE)
        .init_pair(25, COLOR_YELLOW, COLOR_GREEN);

    ncp::windowstream win(0, 0, 0, 0);

    for (auto i = 0u; i < 10; ++i) {
        win << ncp::color(i) << "This is a test, line # " << i+1 << std::endl;
    }

    win << refresh();
    win.flush();

    char c;
    win.get_window().getch(c);
    
/*
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
        if (i < 26) {
            scr.level() << ncp::color(i);
        } else if (i == 30) {
            scr.level() << ncp::attr(COLOR_PAIR(9) | A_BOLD);
        }
        scr.level() << std::setw(20) << "Level, line " << std::hex << i 
                    << "\n" << ncp::attr(A_NORMAL);
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
*/

    return 0;
}

