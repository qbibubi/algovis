#pragma once
#include "../core/registry.h"
#include "ncurses_window.h"

#include <cstddef>

/**
 * @brief Algorithm selection menu displayed before running a sorting algorithm.
 * @class AlgorithmMenu
 *
 * Displays a centered window with a list of available sorting algorithms.
 * Supports keyboard navigation (W/S/J/K/Enter) and runs until an algorithm is selected.
 */
class AlgorithmMenu {
  public:
    AlgorithmMenu();

    AlgorithmMenu(AlgorithmMenu const&) = delete;
    AlgorithmMenu& operator=(AlgorithmMenu const&) = delete;

    /**
     * @brief Render the menu window.
     */
    void Draw();

    /**
     * @brief Handle keyboard input for menu navigation.
     */
    void Input();

    /**
     * @return true if the menu is still active (waiting for selection).
     */
    [[nodiscard]] bool GetIsRunning() const { return IsRunning; }

    /**
     * @return Index of the currently selected algorithm.
     */
    [[nodiscard]] std::size_t GetSelectedIndex() const { return SelectedIndex; }

  private:
    NcursesWindow View;
    bool IsRunning = false;
    int Width = 0;
    int Height = 0;
    std::size_t SelectedIndex = 0;

    static constexpr std::string_view Title = "Select an algorithm";
};
