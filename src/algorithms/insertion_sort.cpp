#include "../../include/algorithms/insertion_sort.h"
#include "../../include/core/sort_observer.h"

void InsertionSort(SortObserver& observer, std::span<int> data) {
    for (std::size_t currentIndex = 1; currentIndex < data.size(); ++currentIndex) {
        auto const key = data[currentIndex];
        auto searchIndex = static_cast<std::ptrdiff_t>(currentIndex) - 1;

        while (searchIndex >= 0 && data[static_cast<std::size_t>(searchIndex)] > key) {
            auto const writeIndex = static_cast<std::size_t>(searchIndex);

            observer.OnClearMarkers();
            observer.OnSetMarker(static_cast<int>(writeIndex + 1), 'i', static_cast<int>(ColorPair::Pointer));
            observer.OnSetMarker(static_cast<int>(writeIndex), 'j', static_cast<int>(ColorPair::Scan));
            observer.OnSetConnection(static_cast<int>(writeIndex), static_cast<int>(currentIndex));
            if (!observer.OnStep())
                return;

            data[writeIndex + 1] = data[writeIndex];
            --searchIndex;
        }

        data[static_cast<std::size_t>(searchIndex + 1)] = key;
        observer.OnMarkSorted(static_cast<int>(currentIndex));

        observer.OnClearMarkers();
        observer.OnSetMarker(static_cast<int>(searchIndex + 1), 'i', static_cast<int>(ColorPair::Sorted));
        if (!observer.OnStep())
            return;
    }

    observer.OnMarkSorted(0);
    observer.OnClearMarkers();
}
