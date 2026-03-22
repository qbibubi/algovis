#include "../../include/algorithms/bubble_sort.h"
#include "../../include/core/sort_observer.h"

void BubbleSort(SortObserver& observer, std::span<int> data) {
    auto const dataSize = data.size();

    for (std::size_t outerIndex = 0; outerIndex < dataSize; ++outerIndex) {
        for (std::size_t innerIndex = 0; innerIndex < dataSize - outerIndex - 1; ++innerIndex) {
            observer.OnClearMarkers();
            observer.OnSetMarker(static_cast<int>(innerIndex), 'j', static_cast<int>(ColorPair::Pointer));
            observer.OnSetMarker(static_cast<int>(innerIndex + 1), 'J', static_cast<int>(ColorPair::Scan));
            observer.OnSetConnection(static_cast<int>(innerIndex), static_cast<int>(innerIndex + 1));
            if (!observer.OnStep())
                return;

            if (data[innerIndex] > data[innerIndex + 1]) {
                std::swap(data[innerIndex], data[innerIndex + 1]);
                if (!observer.OnStep())
                    return;
            }
        }
        observer.OnMarkSorted(static_cast<int>(dataSize - outerIndex - 1));
    }

    observer.OnClearMarkers();
}
