#include "../include/ui/menu.h"
#include "../include/ui/window.h"
#include "../include/ui/visualizer.h"

int main() {
    window_t window;

    while (true) {
        std::size_t selected_index = 0;

        {
            menu_t menu;
            while (menu.get_running()) {
                menu.draw();
                menu.input();
            }

            selected_index = menu.get_selected_index();
        }

        clear();
        refresh();

        {
            visualizer_t visualizer(algorithms[selected_index]);
            while (visualizer.get_running()) {
                visualizer.draw();
                visualizer.input();
            }
        }

        clear();
        refresh();
    }

    return 0;
}
