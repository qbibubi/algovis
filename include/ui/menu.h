#pragma once
#include "view_interface.h"
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

class menu_t : public view_interface_t {
public:
    menu_t();
    ~menu_t() override;

    void draw() override;
    void input() override;

    int get_selected_index() const;

private:
    std::string_view title = "Select an algorithm";
    std::size_t selected_index = 0;
};

