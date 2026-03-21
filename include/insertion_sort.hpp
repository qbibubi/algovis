#pragma once
#include <vector>
#include <cstdint>

namespace insertion {
inline void sort(std::vector<uint32_t> v) {
    for (auto i = 1; i < v.size(); ++i) {
        auto const key = v[i];
        auto j = i - 1;

        while (j >= 0 && v[j] > key) {
            v[j + 1] = v[i];
            --j;
        }

        v[j + 1] = key;
    }
}
} // namespace insertion_sort 
