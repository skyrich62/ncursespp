#include "screen.h"

ScreenUI::ScreenUI()
{
    init.echo(false).cbreak(true).clear().start_color()
        .color(WHITE, 800, 800, 800)
        .color(BROWN, 644, 164, 164)
        .color(YELLOW, 800, 800, 0)
        .color(GREY, 200, 200, 200)
        .color(GREEN, 0, 1000, 0)
        .color(BLUE, 0, 0, 1000)
        .color(RED, 1000, 0, 0)
        .init_pair(1, COLOR_BLACK, COLOR_BLACK)
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
        .init_pair(24, COLOR_YELLOW, COLOR_YELLOW);
        


    const auto ScreenLength = LINES - 6;

    w_msg1 = std::make_unique<Window>(1, 80, 0, 0);
    w_msg2 = std::make_unique<Window>(1, 80, 1, 0);
    w_msg3 = std::make_unique<Window>(1, 80, 2, 0);
    w_more = std::make_unique<Window>(1, 15, 3, 65);
    w_loc  = std::make_unique<Window>(1, 80, ScreenLength + 3, 0);
    w_level= std::make_unique<Window>(ScreenLength, 64, 3, 0);
    for (auto i = 0u; i < maxItems; ++i) {
        w_showLine[i] = std::make_unique<Window>(1, 64, i+3, 0);
        w_showLine[i]->allow_scroll(false).clear();
    }
    w_menu = std::make_unique<Window>(ScreenLength, 64, 3, 0);
    w_data = std::make_unique<Window>(2, 80, ScreenLength + 4, 0);
    w_time = std::make_unique<Window>(2, 15, 4, 65);
    w_phase = std::make_unique<Window>(2, 15, 6, 65);
    w_flag = std::make_unique<Window>(4, 15, 9, 65);
    w_com = std::make_unique<Window>(8, 15, 14, 65);


    w_msg1->allow_scroll(false);
    w_msg2->allow_scroll(false);
    w_msg3->allow_scroll(false);
    w_more->allow_scroll(false);
    w_loc->allow_scroll(false);
    w_level->allow_scroll(false);
    w_menu->allow_scroll(false);
    w_data->allow_scroll(false);
    w_time->allow_scroll(false);
    w_phase->allow_scroll(false);
    w_flag->allow_scroll(false);
    w_com->allow_scroll(false);

    init.touch();
}

