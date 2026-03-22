#pragma once
#include "../../include/core/sort_observer.h"

#include <span>

/**
 * @brief Bubble sort algorithm with visualization support.
 * @param observer Observer for step-by-step visualization callbacks.
 * @param data Span of integers to sort in-place.
 *
 * Visual markers:
 *   j  (cyan)   - Left element of current comparison pair
 *   J  (red)    - Right element of current comparison pair
 *
 * Connection bracket spans [j, j+1] and advances rightward each step.
 * After each outer pass, the rightmost unsorted bar is marked sorted (green).
 */
void BubbleSort(SortObserver& observer, std::span<int> data);
