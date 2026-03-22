#include "../include/ui/window.h"

#include <cstdlib>

ApplicationWindow::ApplicationWindow() {
    Window = initscr();
    if (!Window)
        exit(1);

    if (start_color() == ERR || !has_colors()) {
        endwin();
        exit(1);
    }

    clear();
    noecho();
    cbreak();
    curs_set(0);

    IsRunning = true;
}

ApplicationWindow::~ApplicationWindow() {
    endwin();
}
