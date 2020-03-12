# ncursespp

A modern C++ wrapper for ncurses windows with std::ostream and std::istream functionality.

# Sample
    #include "wstream.h"
    
    int main()
    {
        // Initializer will setup the terminal for windows on construction and return the terminal
        // to normal mode on destruction.
        ncursespp::initializer init;
        
        // Disable echo, set cbreak mode, clear the terminal, and allow color.
        init.echo(false).cbreak(true).clear().start_color()
            .init_pair(1, COLOR_BLACK, COLOR_YELLOW);
        
        // Create an iostream-enabled window, occupying the full terminal
        ncursespp::windowstream win{0, 0, 0, 0};
        
        // Output "Hello world!" on the window, and draw it.
        // "Hello" will be output in the default color, (usually white on black),
        // " World!" will be output in color1, (black on yellow in this case.)
        win << "Hello" << ncursespp::color(1) << " world!" << ncursespp::wrefresh();
        
        char dummy;
        win.wgetch(dummy);    // Wait for a keypress
        
        return 0
    }
