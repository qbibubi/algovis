#pragma once
#include <utility>
#include <vector>
#include <algorithm>
#include <cstdint>

namespace bubble {
inline void sort(std::vector<uint32_t>& v) {
    auto const size = v.size();

    for (auto i = 0; i < size; ++i) {
        for (auto j = 0; j < size - 1; ++j) {
            if (v[j] > v[j + 1]) {
                std::swap(v[j], v[j + 1]);
            }
        }
    }
}

inline void sort_extended(std::vector<uint32_t>& v) {
    auto const size = v.size();

    for (auto i = 0; i < size; ++i) {
        for (auto j = 0; j < size - i - 1; ++j) {
            if (v[j] > v[j + 1]) {
                std::swap(v[j], v[j + 1]);
            }
        }
    }
}

inline void sort_extended_flag(std::vector<uint32_t> & v) {
    auto size = v.size();

    bool swapped;

    for (auto i = 0; i < size - 1; ++i) {
        swapped = false;

        for (auto j = 0; j < size - i - 1; ++j) {
            if (v[j] > v[j + 1]) {
                std::swap(v[j], v[j + 1]);
                swapped = true;
            }
        }

        if (!swapped) {
            break;
        }
    }
}
} // namespace bubble_sort
