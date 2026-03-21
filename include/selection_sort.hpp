#pragma once
#include <utility>
#include <vector>
#include <cstdint>

namespace selection {
inline void sort(std::vector<uint32_t>& v) {
    auto const size = v.size();

    for (std::size_t i = 0; i < size - 1; ++i) {
        std::size_t min = i;

        for (std::size_t j = i + 1; j < size; ++j) {
            if (v[j] < v[min]) {
                min = j;
            }
        }

        std::swap(v[i], v[min]);
    }
}
} // namespace selection
