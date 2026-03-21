#include "../../include/ui/window.h"

#include <cstdlib>

window_t::window_t() {
    window = initscr();
    if (!window) {
        exit(1);
    }

    if (start_color() == ERR || !has_colors()) {
        endwin();
        exit(1);
    }
    
    clear();
    noecho();
    cbreak();
    curs_set(0);

    running = true;
}

window_t::~window_t() {
    endwin();
}

bool window_t::get_running() const {
    return running;
}
