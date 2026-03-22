#include "../../include/algorithms/quick_sort.h"
#include "../../include/core/sort_observer.h"

namespace {

bool PartitionAndRecurse(SortObserver& observer, std::span<int> data, std::size_t leftBound, std::size_t rightBound) {
    if (leftBound == rightBound) {
        observer.OnMarkSorted(static_cast<int>(leftBound));
        return true;
    }
    if (leftBound > rightBound)
        return true;

    auto const pivotValue = data[rightBound];
    auto partitionIndex = leftBound;

    for (std::size_t scanIndex = leftBound; scanIndex < rightBound; ++scanIndex) {
        observer.OnClearMarkers();
        observer.OnSetMarker(static_cast<int>(leftBound), 'l', static_cast<int>(ColorPair::Pointer));
        observer.OnSetMarker(static_cast<int>(rightBound), 'h', static_cast<int>(ColorPair::Pointer));
        observer.OnSetMarker(static_cast<int>(rightBound), 'p', static_cast<int>(ColorPair::Pivot));
        observer.OnSetMarker(static_cast<int>(partitionIndex), 'i', static_cast<int>(ColorPair::Partition));
        observer.OnSetMarker(static_cast<int>(scanIndex), 'j', static_cast<int>(ColorPair::Scan));
        observer.OnSetConnection(static_cast<int>(leftBound), static_cast<int>(rightBound));
        if (!observer.OnStep())
            return false;

        if (data[scanIndex] < pivotValue) {
            std::swap(data[partitionIndex], data[scanIndex]);
            if (!observer.OnStep())
                return false;
            ++partitionIndex;
        }
    }

    std::swap(data[partitionIndex], data[rightBound]);
    observer.OnMarkSorted(static_cast<int>(partitionIndex));

    observer.OnClearMarkers();
    observer.OnSetMarker(static_cast<int>(partitionIndex), 'p', static_cast<int>(ColorPair::Sorted));
    observer.OnSetConnection(static_cast<int>(leftBound), static_cast<int>(rightBound));
    if (!observer.OnStep())
        return false;

    if (partitionIndex > leftBound && !PartitionAndRecurse(observer, data, leftBound, partitionIndex - 1))
        return false;
    return PartitionAndRecurse(observer, data, partitionIndex + 1, rightBound);
}

} // namespace

void QuickSort(SortObserver& observer, std::span<int> data) {
    if (data.size() > 1)
        PartitionAndRecurse(observer, data, 0, data.size() - 1);

    observer.OnClearMarkers();
}
