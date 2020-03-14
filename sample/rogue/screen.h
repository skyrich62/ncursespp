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
#include "defs.h"

#include <memory>

class ScreenUI
{
public:
    using Window = ncursespp::windowstream;
    using WinPtr = std::unique_ptr<Window>;

    ScreenUI();
   ~ScreenUI() = default;

    auto& msg1()                            { return w_msg1; }
    auto& msg2()                            { return w_msg2; }
    auto& msg3()                            { return w_msg3; }
    auto& more()                            { return w_more; }
    auto& loc()                             { return w_loc; }
    auto& level()                           { return w_level; }
    auto& showLine()                        { return w_showLine; }
    auto& menu()                            { return w_menu; }
    auto& data()                            { return w_data; }
    auto& time()                            { return w_time; }
    auto& phase()                           { return w_phase; }
    auto& flag()                            { return w_flag; }
    auto& com()                             { return w_com; }
    auto& terminal()                        { return init; }

private:
    ncursespp::initializer init;
    const int ScreenLength;
    Window w_msg1{1, 80, 0, 0};
    Window w_msg2{1, 80, 1, 0};
    Window w_msg3{1, 80, 2, 0};
    Window w_more{1, 15, 3, 65};
    Window w_loc;
    Window w_level;
    std::array<WinPtr, maxItems> w_showLine;
    Window w_menu;
    Window w_data;
    Window w_time{2, 15, 4, 65};
    Window w_phase{2, 15, 6, 65};
    Window w_flag{4, 15, 9, 65};
    Window w_com{8, 15, 14, 65};
};
