#include "../../include/algorithms/insertion_sort.h"

void insertion_sort(std::vector<uint32_t> v) {
    for (std::size_t i = 1; i < v.size(); ++i) {
        std::size_t j = i - 1;
        auto const key = v[i];

        while (j >= 0 && v[j] > key) {
            v[j + 1] = v[i];
            --j;
        }

        v[j + 1] = key;
    }
}
