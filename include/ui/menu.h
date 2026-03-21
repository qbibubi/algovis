#pragma once
#include <ncurses.h>
#include <array>
#include <string_view>

enum class keys : int {
    enter = 10,

    w = 119,
    a = 97,
    s = 115,
    d = 100,

    j = 106,
    k = 107
};

auto constexpr algorithms = std::to_array<std::string_view>({
    "Bubble sort",
    "Insertion sort",
    "Selection sort",
    "Quick sort",
    "Heap sort"
});

class menu_t {
public:
    menu_t();
    ~menu_t();

public:
    void draw();
    void input();

    bool get_running() const;            
    int get_selected_index() const;

private:
    std::string_view title = "Select an algorithm";
    WINDOW* view = nullptr;
    int width = 0, height = 0;
    int selected_index = 0;
    bool running = true;
};

