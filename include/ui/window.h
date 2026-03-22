#pragma once
#include <ncurses.h>

/**
 * @brief Manages the ncurses library lifecycle for the entire application.
 * @class ApplicationWindow
 *
 * Handles initialization of ncurses on construction and cleanup on destruction.
 * Provides a simple running state for the main application loop.
 */
class ApplicationWindow {
  public:
    ApplicationWindow();
    ~ApplicationWindow();

    ApplicationWindow(ApplicationWindow const&) = delete;
    ApplicationWindow& operator=(ApplicationWindow const&) = delete;

    /**
     * @return true if the application should continue running.
     */
    [[nodiscard]] bool GetIsRunning() const { return IsRunning; }

  private:
    WINDOW* Window = nullptr;
    bool IsRunning = false;
};
