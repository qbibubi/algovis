#include "../../include/ui/menu.h"

#include <ranges>
#include <algorithm>

menu_t::menu_t() {
    auto const menu_padding_x = 6;
    auto const menu_padding_y = 2;

    auto it = std::ranges::max_element(algorithms, {}, &std::string_view::size); 
    auto const max_string_length = (it != algorithms.end()) ? it->size() : 0;

    width = std::max<int>(max_string_length + menu_padding_x, title.size() + menu_padding_x);
    height = algorithms.size() + menu_padding_y;

    auto const center_x = (COLS - width) / 2;
    auto const center_y = (LINES - height) / 2;

    view = newwin(height, width, center_y, center_x);
    if (!view) return;
    
    keypad(view, true);
}

menu_t::~menu_t() {
    if(view) { 
        delwin(view);
    }
}

void menu_t::draw() {
    box(view, 0, 0);
    
    mvwprintw(view, 0, (width - title.size()) / 2, "%.*s", static_cast<int>(title.size()), title.data());
    
    for (size_t i = 0; i < algorithms.size(); ++i) {
        if (i == selected_index) wattron(view, A_REVERSE);
    
        mvwprintw(
            view, 
            i + 1, 2, 
            "%-*.*s", 
            width - 4, 
            static_cast<int>(algorithms[i].size()), algorithms[i].data()
        );

        if (i == selected_index) wattroff(view, A_REVERSE);
    }

    wrefresh(view);
}

void menu_t::input() {
    auto const key = static_cast<keys>(wgetch(view));

    switch (key) {
        case keys::enter:
            running = false;
            break;
        case keys::w:
        case keys::k:
            selected_index--;
            if (selected_index< 0) selected_index= algorithms.size() - 1;
            break;
        case keys::s:
        case keys::j:
            selected_index++;
            if (selected_index >= static_cast<int>(algorithms.size())) selected_index = 0;
            break;
        case keys::a: break;
        case keys::d: break;
    }
}

bool menu_t::get_running() const {
    return running;
}
        
int menu_t::get_selected_index() const {
    return selected_index;
}
