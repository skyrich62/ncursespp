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

#include "screen.h"

ScreenUI::ScreenUI() :
    init(),
    ScreenLength(LINES - 6),
    w_loc{1, 80, ScreenLength + 3, 0},
    w_level{ScreenLength, 64, 3, 0},
    w_menu{ScreenLength, 64, 3, 0},
    w_data{2, 80, ScreenLength + 4, 0}
{
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
        
    const auto ScreenLength = LINES - 6;


    for (auto i = 0u; auto &win: w_showLine) {
        win = std::make_unique<Window>(1, 64, ++i + 2, 0);
        win->allow_scroll(false).wclear();
    }

    w_msg1.allow_scroll(false).wclear();
    w_msg2.allow_scroll(false).wclear();
    w_msg3.allow_scroll(false).wclear();
    w_more.allow_scroll(false).wclear();
    w_loc.allow_scroll(false).wclear();
    w_level.allow_scroll(false).wclear();
    w_menu.allow_scroll(false).wclear();
    w_data.allow_scroll(false).wclear();
    w_time.allow_scroll(false).wclear();
    w_phase.allow_scroll(false).wclear();
    w_flag.allow_scroll(false).wclear();
    w_com.allow_scroll(false).wclear();

    init.touch();
}
