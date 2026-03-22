#pragma once
#include "sort_observer.h"

#include <array>
#include <functional>
#include <span>
#include <string_view>

void BubbleSort(SortObserver& observer, std::span<int> data);
void InsertionSort(SortObserver& observer, std::span<int> data);
void SelectionSort(SortObserver& observer, std::span<int> data);
void QuickSort(SortObserver& observer, std::span<int> data);
void HeapSort(SortObserver& observer, std::span<int> data);

/**
 * @brief Entry in the algorithm registry.
 * @struct AlgorithmEntry
 */
struct AlgorithmEntry {
    std::string_view Name;
    std::function<void(SortObserver&, std::span<int>)> Execute;
};

/**
 * @brief Global registry mapping algorithm names to their executable functions.
 * @details Add new algorithms here to make them available in the menu.
 */
inline const auto AlgorithmRegistry = std::to_array<AlgorithmEntry>({
    {"Bubble sort", BubbleSort},
    {"Insertion sort", InsertionSort},
    {"Selection sort", SelectionSort},
    {"Quick sort", QuickSort},
    {"Heap sort", HeapSort},
});
