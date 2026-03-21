#pragma once
#include "view_interface.h"
#include <string_view>

class visualizer_t : public view_interface_t {
public:
    explicit visualizer_t(std::string_view algo_name);
    ~visualizer_t() override;

    void draw() override;
    void input() override;

private:
    std::string_view algorithm;
};

