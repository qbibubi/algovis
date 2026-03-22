#pragma once
#include "../../include/core/sort_observer.h"

#include <span>

/**
 * @brief Selection sort algorithm with visualization support.
 * @param observer Observer for step-by-step visualization callbacks.
 * @param data Span of integers to sort in-place.
 *
 * Visual markers:
 *   i  (cyan)    - Sorted boundary; everything left of here is done
 *   m  (yellow)  - Index of the running minimum
 *   j  (red)     - Scan pointer
 *
 * Connection bracket spans [i, j] showing the current scan range.
 */
void SelectionSort(SortObserver& observer, std::span<int> data);
