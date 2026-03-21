#include "../../include/ui/visualizer.h"

visualizer_t::visualizer_t(std::string_view algo_name) : algorithm(algo_name) {
    width = COLS - 4;
    height = LINES - 2;

    int center_x = (COLS- width) / 2;
    int center_y = (LINES- height) / 2;

    view = newwin(height, width, center_y, center_x);
    if (!view) {
        return;
    }

    keypad(view, TRUE);

    running = true;
}

visualizer_t::~visualizer_t() {
    if (view) {
        delwin(view);
    }
}

void visualizer_t::draw() {
    box(view, 0, 0);

    mvwprintw(view, 0, 2, "[ %.*s Visualizer ]", 
              static_cast<int>(algorithm.size()), algorithm.data());

    mvwprintw(view, height / 2, (width - 35) / 2, 
              "Visualizer is running! Press 'q' to quit.");

    wrefresh(view);
}

void visualizer_t::input() {
    auto const key = wgetch(view);

    if (key == 'q' || key == 'Q') {
        running = false;
    }
}

bool visualizer_t::get_running() const {
    return running;
}

