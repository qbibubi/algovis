#pragma once
#include "../../include/core/sort_observer.h"

#include <span>

/**
 * @brief Quick sort algorithm with visualization support (Lomuto partition scheme).
 * @param observer Observer for step-by-step visualization callbacks.
 * @param data Span of integers to sort in-place.
 *
 * Visual markers:
 *   l  (cyan)    - Left bound of current sub-array
 *   h  (cyan)    - Right bound / pivot home
 *   p  (yellow)  - Pivot element
 *   i  (magenta) - Partition pointer
 *   j  (red)     - Scan pointer
 *
 * Connection bracket spans [l, h] throughout each recursive call.
 */
void QuickSort(SortObserver& observer, std::span<int> data);
