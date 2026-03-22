#include "../include/core/registry.h"
#include "../include/ui/menu.h"
#include "../include/ui/visualizer.h"
#include "../include/ui/window.h"

/**
 * @brief Main application entry point.
 * @details Runs a loop: show algorithm selection menu, then run the selected
 *          algorithm with visualization, until the user exits.
 */
int main() {
    ApplicationWindow application;

    while (application.GetIsRunning()) {
        std::size_t selectedIndex = 0;
        {
            AlgorithmMenu menu;
            while (menu.GetIsRunning()) {
                menu.Draw();
                menu.Input();
            }
            selectedIndex = menu.GetSelectedIndex();
        }

        clear();
        refresh();

        {
            auto const& entry = AlgorithmRegistry[selectedIndex];

            SortingVisualizer visualizer{entry.Name};
            visualizer.GenerateData();

            entry.Execute(visualizer, visualizer.GetData());

            while (visualizer.GetIsRunning()) {
                visualizer.Input();
                visualizer.Draw();
            }
        }

        clear();
        refresh();
    }

    return 0;
}
