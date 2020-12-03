# ncursespp

A modern C++ wrapper for ncurses windows with std::ostream and std::istream functionality.

# Sample

    #include "wstream.h"

    namespace ncp = CompuBrite::ncursespp;

    int main()
    {
        // Initializer will setup the terminal for windows on construction and return the terminal
        // to normal mode on destruction.
        ncp::initializer init;

        // Disable echo, set cbreak mode, clear the terminal, and allow color.
        init.echo(false).cbreak(true).clear().start_color()
            .init_pair(1, COLOR_BLACK, COLOR_YELLOW);

        // Create an iostream-enabled window, occupying the full terminal
        ncp::windowstream win{0, 0, 0, 0};

        // Output "Hello world!" on the window, and draw it.
        // "Hello" will be output in the default color, (usually white on black),
        // " World!" will be output in color1, (black on yellow in this case.)
        win << "Hello" << ncp::color(1) << " world!" << ncp::refresh();

        win.wgetch();    // Wait for a keypress

        return 0;
    }

# Still a work in progress

This is still a work in progress, but I'm far enough along for now.

I started this with the idea of reviving the game "omega", which hasn't been
touched in quite some time, was written in K&R C and is quite buggy.  I'm
thinking of a new re-write from scratch in C++.  Doing this ncurses library
was a good starting point.

http://www.alcyone.com/max/projects/omega/
