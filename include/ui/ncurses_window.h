#pragma once
#include <ncurses.h>
#include <utility>

/**
 * @brief RAII wrapper for ncurses WINDOW handles.
 * @class NcursesWindow
 *
 * Manages the lifetime of a ncurses WINDOW pointer, ensuring proper cleanup
 * via delwin() on destruction. Supports move semantics but not copy.
 */
class NcursesWindow {
  public:
    NcursesWindow() = default;

    /**
     * @param windowPtr Raw ncurses window pointer to manage.
     */
    explicit NcursesWindow(WINDOW* windowPtr) : WindowPtr(windowPtr) {}

    ~NcursesWindow() {
        if (WindowPtr)
            delwin(WindowPtr);
    }

    NcursesWindow(NcursesWindow const&) = delete;
    NcursesWindow& operator=(NcursesWindow const&) = delete;

    NcursesWindow(NcursesWindow&& other) noexcept : WindowPtr(std::exchange(other.WindowPtr, nullptr)) {}

    NcursesWindow& operator=(NcursesWindow&& other) noexcept {
        if (this != &other) {
            if (WindowPtr) {
                delwin(WindowPtr);
            }

            WindowPtr = std::exchange(other.WindowPtr, nullptr);
        }

        return *this;
    }

    /**
     * @return Raw ncurses window pointer.
     */
    [[nodiscard]] WINDOW* Get() const { return WindowPtr; }

    /**
     * @return true if the window pointer is not null.
     */
    explicit operator bool() const { return WindowPtr != nullptr; }

  private:
    WINDOW* WindowPtr = nullptr;
};
