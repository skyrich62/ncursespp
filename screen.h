#include "initializer.h"
#include "wstream.h"
#include "defs.h"

#include <memory>

class ScreenUI
{
public:

    using Window = ncursespp::windowstream;
    using WinPtr = std::unique_ptr<Window>;

    enum Colors : char {WHITE, BROWN, YELLOW, GREY, GREEN, BLUE, RED};

    ScreenUI();
   ~ScreenUI() = default;

    Window& msg1()                          { return *w_msg1; }
    Window& msg2()                          { return *w_msg2; }
    Window& msg3()                          { return *w_msg3; }
    Window& more()                          { return *w_more; }
    Window& loc()                           { return *w_loc; }
    Window& level()                         { return *w_level; }
    auto&   showLine()                      { return w_showLine; }
    Window& menu()                          { return *w_menu; }
    Window& data()                          { return *w_data; }
    Window& time()                          { return *w_time; }
    Window& phase()                         { return *w_phase; }
    Window& flag()                          { return *w_flag; }
    Window& com()                           { return *w_com; }
    auto& terminal()                        { return init; }
private:
    ncursespp::initializer init;
    WinPtr w_msg1;
    WinPtr w_msg2;
    WinPtr w_msg3;
    WinPtr w_more;
    WinPtr w_loc;
    WinPtr w_level;
    std::array<WinPtr, maxItems> w_showLine;
    WinPtr w_menu;
    WinPtr w_data;
    WinPtr w_time;
    WinPtr w_phase;
    WinPtr w_flag;
    WinPtr w_com;
};
