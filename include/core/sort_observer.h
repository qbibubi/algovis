#pragma once

/**
 * @file sort_observer.h
 * @brief Observer interface for sorting algorithm visualization.
 *
 * This is the contract between a sorting algorithm and whoever is observing it.
 * Algorithms call these methods at each meaningful pause point and never
 * include anything from include/ui/. This means:
 *   - Algorithms have zero knowledge of ncurses, windows, or rendering.
 *   - A test observer can record every event without opening a terminal.
 *   - A different visualizer (e.g. a graph view) implements this same
 *     interface and the algorithms slot straight in.
 *
 * Color pair IDs used for ncurses rendering:
 *   ColorPairDefault    = 1 (white, default bar)
 *   ColorPairPointer    = 2 (cyan, first pointer / left element)
 *   ColorPairScan       = 3 (red, second pointer / right element)
 *   ColorPairSorted     = 4 (green, sorted / placed)
 *   ColorPairPivot      = 5 (yellow, pivot / minimum)
 *   ColorPairPartition  = 6 (magenta, partition pointer)
 */
enum class ColorPair : int { Default = 1, Pointer = 2, Scan = 3, Sorted = 4, Pivot = 5, Partition = 6 };

class SortObserver {
  public:
    virtual ~SortObserver() = default;

    /**
     * @brief Place a labelled, colored marker under a bar.
     * @param barIndex Bar index under which the marker gets placed.
     * @param label Single character label displayed under the bar.
     * @param colorPair ncurses color pair ID (see color conventions above).
     */
    virtual void OnSetMarker(int barIndex, char label, int colorPair) = 0;

    /**
     * @brief Remove all markers and reset the connection bracket.
     */
    virtual void OnClearMarkers() = 0;

    /**
     * @brief Draw a bracket spanning a range of bars below the visualization.
     * @param startIndex Bar index where the bracket starts.
     * @param endIndex Bar index where the bracket ends.
     */
    virtual void OnSetConnection(int startIndex, int endIndex) = 0;

    /**
     * @brief Mark a bar as permanently in its final sorted position.
     * @param barIndex Bar index to mark as sorted (displayed in green).
     */
    virtual void OnMarkSorted(int barIndex) = 0;

    /**
     * @brief Advance one visual frame: render current state, poll input, sleep.
     * @return false when the observer wants the algorithm to stop (e.g. user pressed 'q').
     *         Algorithms must check the return value after every call and return early when false.
     */
    [[nodiscard]] virtual bool OnStep() = 0;
};
