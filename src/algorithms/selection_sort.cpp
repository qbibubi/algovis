#include "../../include/algorithms/selection_sort.h"

void selection_sort(std::vector<uint32_t>& v) {
    std::size_t const size = v.size();

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
