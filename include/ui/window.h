#pragma once
#include <ncurses.h>

class window_t  {
public:
    window_t(); 
    ~window_t();

public:
    bool get_running() const;

private:
    WINDOW* window = nullptr;
    bool running = false;
};

