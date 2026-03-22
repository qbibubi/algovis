#include "../../include/algorithms/selection_sort.h"
#include "../../include/core/sort_observer.h"

void SelectionSort(SortObserver& observer, std::span<int> data) {
    auto const dataSize = data.size();

    for (std::size_t boundaryIndex = 0; boundaryIndex < dataSize - 1; ++boundaryIndex) {
        std::size_t minimumIndex = boundaryIndex;

        for (std::size_t scanIndex = boundaryIndex + 1; scanIndex < dataSize; ++scanIndex) {
            observer.OnClearMarkers();
            observer.OnSetMarker(static_cast<int>(boundaryIndex), 'i', static_cast<int>(ColorPair::Pointer));
            observer.OnSetMarker(static_cast<int>(minimumIndex), 'm', static_cast<int>(ColorPair::Pivot));
            observer.OnSetMarker(static_cast<int>(scanIndex), 'j', static_cast<int>(ColorPair::Scan));
            observer.OnSetConnection(static_cast<int>(boundaryIndex), static_cast<int>(scanIndex));
            if (!observer.OnStep())
                return;

            if (data[scanIndex] < data[minimumIndex])
                minimumIndex = scanIndex;
        }

        if (minimumIndex != boundaryIndex) {
            std::swap(data[boundaryIndex], data[minimumIndex]);
            observer.OnClearMarkers();
            observer.OnSetMarker(static_cast<int>(boundaryIndex), 'i', static_cast<int>(ColorPair::Sorted));
            if (!observer.OnStep())
                return;
        }

        observer.OnMarkSorted(static_cast<int>(boundaryIndex));
    }

    observer.OnMarkSorted(static_cast<int>(dataSize - 1));
    observer.OnClearMarkers();
}
