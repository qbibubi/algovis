#include "../include/ui/menu.hpp"

int main() {
    window_t window;

    while (true) {
        auto selected_index = -1;

        {
            menu_t menu;
            while (menu.running()) {
                menu.draw();
                menu.input();
            }

            selected_index = menu.get_selected_index();
        }

        clear();
        refresh();

        {
            sorting_t visualizer(algorithms[selected_index]);
            while (visualizer.running()) {
                visualizer.draw();
                visualizer.input();
            }
        }

        clear();
        refresh();
    }

    return 0;
}
