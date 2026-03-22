#pragma once
#include "../../include/core/sort_observer.h"

#include <span>

/**
 * @brief Heap sort algorithm with visualization support.
 * @param observer Observer for step-by-step visualization callbacks.
 * @param data Span of integers to sort in-place.
 *
 * Two phases:
 *   Phase 1 - Build a max-heap in-place (Floyd's bottom-up heapify).
 *             Iterates from the last internal node down to the root.
 *   Phase 2 - Extraction: swap max (root) with last element of live heap,
 *             shrink heap by one, sift new root down.
 *             Each extracted element lands in its final sorted position.
 *
 * Visual markers during sift-down:
 *   r  (yellow)  - Root being sifted
 *   L  (cyan)    - Left child
 *   R  (red)     - Right child
 *   s  (magenta) - Swap target (the larger child)
 *
 * Connection bracket spans [root, swap_target] on each comparison.
 */
void HeapSort(SortObserver& observer, std::span<int> data);
