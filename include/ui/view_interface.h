#pragma once
#include <ncurses.h>

class view_interface_t {
public:
    virtual ~view_interface_t() = default;
    virtual void draw() = 0;
    virtual void input() = 0;

    bool get_running() const { return running; }

protected:
    WINDOW* view = nullptr;
    bool running = false;
    int width = 0;
    int height = 0;
};

