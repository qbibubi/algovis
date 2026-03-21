#pragma once
#include <ncurses.h>
#include <string_view>

class visualizer_t {
public:
    explicit visualizer_t(std::string_view algo_name);
    ~visualizer_t();

    void draw();
    void input();
    bool get_running() const;

private:
    WINDOW* view = nullptr;
    std::string_view algorithm;
    int width = 0, height = 0;
    bool running = false;
};

