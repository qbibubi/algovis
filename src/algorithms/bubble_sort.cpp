#include "../../include/algorithms/bubble_sort.h"

void bubble_sort(std::vector<uint32_t>& v) {
    std::size_t const size = v.size();

    for (std::size_t i = 0; i < size; ++i) {
        for (std::size_t j = 0; j < size - 1; ++j) {
            if (v[j] > v[j + 1]) {
                std::swap(v[j], v[j + 1]);
            }
        }
    }
}

void bubble_sort_extended(std::vector<uint32_t>& v) {
    std::size_t const size = v.size();

    for (std::size_t i = 0; i < size; ++i) {
        for (std::size_t j = 0; j < size - i - 1; ++j) {
            if (v[j] > v[j + 1]) {
                std::swap(v[j], v[j + 1]);
            }
        }
    }
}

void bubble_sort_extended_flag(std::vector<uint32_t> & v) {
    std::size_t size = v.size();

    bool swapped;

    for (std::size_t i = 0; i < size - 1; ++i) {
        swapped = false;

        for (std::size_t j = 0; j < size - i - 1; ++j) {
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
