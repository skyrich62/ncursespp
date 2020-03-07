#include "initializer.h"
#include "window.h"

int main()
{
    ncursespp::initializer init;
    init.cbreak(true).nl(false).echo(false).start_color();
    init.init_pair(1, COLOR_RED, COLOR_BLACK)
        .init_pair(2, COLOR_BLUE, COLOR_WHITE);
    ncursespp::window win(0, 0, 0, 0);
    win.clear();
    win << ncursespp::color(1) 
        << "Hello world!";
    char dummy;
    win >> dummy;

    win << ncursespp::move(2, 15) << "goodbye " 
        << ncursespp::color(2)
        << ncursespp::attr(A_BOLD | A_STANDOUT, true)
        << "cruel" 
        << ncursespp::attr(A_BOLD | A_STANDOUT, false)
        << ncursespp::color(0)
        << ncursespp::attr(A_DIM, true)
        << " world\n";

    win << "This should be on the next line";
    win << "\nType a string: ";
    init.echo(true);
    std::string s;
    win >> s;
    win << "You typed: " << s << ", and now a number: ";

    long long int x;
    win >> x;
    win << "You entered: " << x;
    win >> dummy;

    return 0;
}

