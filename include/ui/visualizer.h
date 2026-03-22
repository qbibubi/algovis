#pragma once
#include "../core/sort_observer.h"
#include "ncurses_window.h"

#include <map>
#include <set>
#include <span>
#include <string>
#include <vector>

/**
 * @brief Visualization window for sorting algorithm execution.
 * @class SortingVisualizer
 *
 * Implements the SortObserver interface to render sorting algorithms in real-time.
 * Displays bars, markers, connection brackets, and color-coded elements.
 *
 * Row layout (0-indexed from top):
 *   0            title bar with algorithm name and speed indicator
 *   1            padding
 *   2..floorY    bars growing upward from floorY
 *   floorY+1    bracket vertical lines
 *   floorY+2    bracket bottom edge
 *   floorY+3    variable/marker labels
 *   height-1     bottom border with key hints
 */
class SortingVisualizer : public SortObserver {
  public:
    /**
     * @param algoName Name to display in the title bar.
     */
    explicit SortingVisualizer(std::string_view algoName);

    SortingVisualizer(SortingVisualizer const&) = delete;
    SortingVisualizer& operator=(SortingVisualizer const&) = delete;

    /**
     * @brief Generate random data for sorting.
     * @param elementCount Number of elements (0 = auto-calculate based on terminal width).
     * @param maxValue Maximum value for generated elements.
     */
    void GenerateData(int elementCount = 0, int maxValue = 10);

    /**
     * @return Reference to the data vector being sorted.
     */
    [[nodiscard]] std::vector<int>& GetData() { return Data; }

    void OnSetMarker(int barIndex, char label, int colorPair) override;
    void OnClearMarkers() override;
    void OnSetConnection(int startIndex, int endIndex) override;
    void OnMarkSorted(int barIndex) override;

    /**
     * @brief Advance one visual frame: process input, render, and sleep.
     * @return false if the user requested to quit. Algorithms must check this.
     */
    [[nodiscard]] bool OnStep() override;

    /**
     * @return true if the visualizer is still running.
     */
    [[nodiscard]] bool GetIsRunning() const { return IsRunning; }

    /**
     * @brief Render the current state of the visualization.
     */
    void Draw();

    /**
     * @brief Handle keyboard input (+/- for speed, q to quit).
     */
    void Input();

  private:
    /**
     * @brief Information about a marker displayed under a bar.
     * @struct MarkerInfo
     */
    struct MarkerInfo {
        char Label;
        int ColorPair;
    };

    NcursesWindow View;
    bool IsRunning = false;
    int Width = 0;
    int Height = 0;

    std::string AlgorithmName;
    std::vector<int> Data;
    std::map<int, MarkerInfo> Markers;
    std::set<int> SortedIndices;
    std::pair<int, int> ConnectionRange = {-1, -1};
    int DelayMs = 50;
};
