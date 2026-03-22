#pragma once
#include "../../include/core/sort_observer.h"

#include <span>

/**
 * @brief Insertion sort algorithm with visualization support.
 * @param observer Observer for step-by-step visualization callbacks.
 * @param data Span of integers to sort in-place.
 *
 * Visual markers:
 *   i  (cyan)   - Hole position (where the key will land)
 *   j  (red)    - Element currently being shifted right
 *
 * Connection bracket spans [j, i] and shrinks leftward as j searches for the slot.
 */
void InsertionSort(SortObserver& observer, std::span<int> data);
