#include "../include/ui/menu.h"
#include "../include/ui/window.h"
#include "../include/ui/visualizer.h"

#include <concepts>

template<typename T>
concept ui_view = requires(T& view) {
    { view.get_running() } -> std::convertible_to<bool>;
    view.draw();
    view.input();
};

template<ui_view T>
void run_view(T& view) {
    while (view.get_running()) {
        view.draw();
        view.input();
    }
}

int main() {
    window_t window;

    while (true) {
        auto selected_index = -1;

        {
            menu_t menu;
            run_view(menu);

            selected_index = menu.get_selected_index();
        }

        clear();
        refresh();

        {
            visualizer_t visualizer(algorithms[selected_index]);
            run_view(visualizer);
        }

        clear();
        refresh();
    }

    return 0;
}
