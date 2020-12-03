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

// A "Hello World" program for ncursespp::window

#include "ncursespp/wstream.h"

namespace ncpp = CompuBrite::ncursespp;

int main()
{
    // Initializer will setup the terminal for windows on construction and return the terminal
    // to normal mode on destruction.
    ncpp::initializer init;

    // Disable echo, set cbreak mode, clear the terminal, and allow color.
    init.echo(false).cbreak(true).clear().start_color()
        .init_pair(1, COLOR_BLACK, COLOR_YELLOW);

    // Create an iostream-enabled window, occupying the full terminal
    ncpp::windowstream win{0, 0, 0, 0};

    // Output "Hello world!" on the window, and draw it.
    // "Hello" will be output in the default color, (usually white on black),
    // " World!" will be output in color1, (black on yellow in this case.)
    win << "Hello" << ncpp::color(1) << " world!" << ncpp::refresh();

    win.wgetch();    // Wait for a keypress

    return 0;
}
