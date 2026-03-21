#pragma once
#include <algorithm>
#include <random>
#include <vector>
#include <iostream>
#include <string_view> 
#include <chrono>

namespace {
    std::random_device random;
    std::mt19937 device(random());
} // namespace

namespace test_suite {
[[nodiscard]] inline std::vector<uint32_t> get_test_case(std::size_t const size) {
    auto constexpr MIN_ELEMENT = 100;
    auto constexpr MAX_ELEMENT = 1'000'000;

    std::vector<uint32_t> result(size);

    for (std::size_t i = 0; i < size; ++i) {
        auto uniform_distribution = std::uniform_int_distribution<uint32_t>(MIN_ELEMENT, MAX_ELEMENT);
        auto const number = uniform_distribution(device);

        result.push_back(number);
    }

    return result;
}


[[nodiscard]] inline bool is_sorted(std::vector<uint32_t> const& v) {
    std::cout << "Vector of size " << v.size() << " is ";

    auto const sorted = std::is_sorted(v.begin(), v.end());
    auto const string = (sorted) ? std::string_view{"sorted"} : std::string_view{"not sorted"};

    std::cout << string << std::endl;

    return sorted;
}

inline void print(std::vector<uint32_t> const& v) {
    std::size_t constexpr PRINTALBE_SIZE = 25;

    if (v.size() > PRINTALBE_SIZE) {
        std::cout << "{ ";

        for (std::size_t i = 0; i < PRINTALBE_SIZE; ++i) {
            std::cout << v[i] << ", ";
        }

        std::cout << "..., ";
        std::cout << v[v.size() - 1] << " }" << std::endl; 
    }
}

template<typename T>
inline void measure(T const& lambda) {
    auto const start = std::chrono::high_resolution_clock::now();

    lambda();

    auto const end = std::chrono::high_resolution_clock::now();

    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << std::endl;
}
} // namespace test_suite
