#include "../../include/algorithms/heap_sort.h"
#include "../../include/core/sort_observer.h"

namespace {

[[nodiscard]] bool SiftDown(SortObserver& observer, std::span<int> data, std::size_t rootIndex, std::size_t heapSize) {
    while (true) {
        auto const leftChild = 2 * rootIndex + 1;
        auto const rightChild = 2 * rootIndex + 2;
        auto largest = rootIndex;

        if (leftChild < heapSize && data[leftChild] > data[largest])
            largest = leftChild;
        if (rightChild < heapSize && data[rightChild] > data[largest])
            largest = rightChild;

        observer.OnClearMarkers();
        observer.OnSetMarker(static_cast<int>(rootIndex), 'r', static_cast<int>(ColorPair::Pivot));

        if (leftChild < heapSize)
            observer.OnSetMarker(static_cast<int>(leftChild), 'L', static_cast<int>(ColorPair::Pointer));
        if (rightChild < heapSize)
            observer.OnSetMarker(static_cast<int>(rightChild), 'R', static_cast<int>(ColorPair::Scan));
        if (largest != rootIndex) {
            observer.OnSetMarker(static_cast<int>(largest), 's', static_cast<int>(ColorPair::Partition));
            observer.OnSetConnection(static_cast<int>(rootIndex), static_cast<int>(largest));
        }

        if (!observer.OnStep())
            return false;
        if (largest == rootIndex)
            break;

        std::swap(data[rootIndex], data[largest]);
        if (!observer.OnStep())
            return false;

        rootIndex = largest;
    }
    return true;
}

} // namespace

void HeapSort(SortObserver& observer, std::span<int> data) {
    auto const dataSize = data.size();
    if (dataSize < 2)
        return;

    for (auto heapifyIndex = static_cast<std::ptrdiff_t>(dataSize / 2) - 1; heapifyIndex >= 0; --heapifyIndex) {
        if (!SiftDown(observer, data, static_cast<std::size_t>(heapifyIndex), dataSize))
            return;
    }

    for (auto extractIndex = dataSize - 1; extractIndex > 0; --extractIndex) {
        std::swap(data[0], data[extractIndex]);
        observer.OnMarkSorted(static_cast<int>(extractIndex));

        observer.OnClearMarkers();
        observer.OnSetMarker(static_cast<int>(extractIndex), 's', static_cast<int>(ColorPair::Sorted));
        if (!observer.OnStep())
            return;

        if (!SiftDown(observer, data, 0, extractIndex))
            return;
    }

    observer.OnMarkSorted(0);
    observer.OnClearMarkers();
}
