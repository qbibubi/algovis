# AlgoVis

Linux terminal application for visualizing sorting algorithms in real-time using ncurses.

## Description

AlgoVis demonstrates sorting algorithms through animated visualizations in the terminal. Each algorithm is instrumented to emit step-by-step events, allowing you to observe how elements are compared, swapped, and sorted. The visualization displays bars of varying heights with color-coded markers indicating algorithm state.

## Architecture

```
┌─────────────────────────────────────────────────────────────┐
│                         Application                         │
│  ┌─────────────┐     ┌──────────────────┐                   │
│  │AlgorithmMenu│───▶│ SortingVisualizer│                   │
│  └─────────────┘     └────────┬─────────┘                   │
│                               │                             │
│                               │ implements                  │
│                               ▼                             │
│                     ┌─────────────────┐                     │
│                     │  SortObserver   │ (interface)         │
│                     └─────────────────┘                     │
└─────────────────────────────────────────────────────────────┘
```

### Core Components

| Layer | Components | Responsibility |
|-------|------------|----------------|
| **Core** | `SortObserver`, `AlgorithmRegistry` | Observer interface that algorithms use to emit events; global registry of available algorithms |
| **UI** | `ApplicationWindow`, `AlgorithmMenu`, `SortingVisualizer`, `NcursesWindow` | Window management, menu handling, visualization rendering |
| **Algorithms** | `BubbleSort`, `InsertionSort`, `SelectionSort`, `QuickSort`, `HeapSort` | Sorting algorithms instrumented with observer callbacks |

### Observer Pattern

The `SortObserver` interface decouples algorithms from visualization:

```cpp
class SortObserver {
    virtual void OnSetMarker(int barIndex, char label, int colorPair) = 0;
    virtual void OnClearMarkers() = 0;
    virtual void OnSetConnection(int startIndex, int endIndex) = 0;
    virtual void OnMarkSorted(int barIndex) = 0;
    virtual bool OnStep() = 0;
};
```

Algorithms call observer methods at each meaningful step without knowing how rendering works. This design allows:
- Testing algorithms with a mock observer (no terminal required)
- Swapping visualizations (e.g., bar chart → graph view) without changing algorithms
- Adding new algorithms by simply implementing the observer calls

### Visualization Rendering

The `SortingVisualizer` renders:
- **Bars**: Height proportional to value, arranged horizontally
- **Markers**: Single-character labels beneath bars indicating algorithm state
- **Connection bracket**: Visual span showing current comparison range
- **Color coding**: Different states (pointer, scan, sorted, pivot) use distinct colors

### Future: Pathfinding and Graph Algorithms

Planned updates include pathfinding algorithms (A*, Dijkstra, BFS, DFS) and graph algorithms. These operate on 2D grids or graph structures rather than 1D arrays.

**Required architecture changes:**
- New `GridObserver` interface for 2D grid-based visualization
- Extended marker system supporting:
  - Node-based markers (not just under-bar positioning)
  - Edge visualization for graph structures
  - Path and frontier highlighting
  - Multiple simultaneous marker types (visited, current, path)
- Separate rendering module for grid/graph visualization

## Prerequisites

- **C++ compiler** with C++20 support (GCC 10+ or Clang 12+)
- **ncurses** development libraries
- **CMake** 3.10 or higher
- **GNU Make** (or compatible build tool)

### Installing Dependencies

**Ubuntu/Debian:**
```bash
sudo apt-get install build-essential cmake libncurses5-dev libncursesw5-dev
```

**Fedora/RHEL:**
```bash
sudo dnf install gcc-c++ cmake ncurses-devel
```

**Arch Linux:**
```bash
sudo pacman -S base-devel cmake ncurses
```

## Building

```bash
# Clone the repository
git clone https://github.com/yourusername/algovis.git
cd algovis

# Create build directory
mkdir build && cd build

# Configure with CMake
cmake ..

# Build
make
```

The executable will be created at `build/sorting`.

## Running

```bash
./build/sorting
```

### Controls

| Key | Action |
|-----|--------|
| `W` / `K` | Move selection up |
| `S` / `J` | Move selection down |
| `Enter` | Select algorithm |
| `+` | Increase animation speed |
| `-` | Decrease animation speed |
| `Q` | Quit |

## Available Algorithms

| Algorithm | Time Complexity | Space Complexity |
|-----------|-----------------|------------------|
| Bubble Sort | O(n²) | O(1) |
| Insertion Sort | O(n²) | O(1) |
| Selection Sort | O(n²) | O(1) |
| Quick Sort | O(n log n) average | O(log n) |
| Heap Sort | O(n log n) | O(1) |

## Project Structure

```
algovis/
├── include/
│   ├── algorithms/       # Algorithm declarations
│   ├── core/             # Observer interface and registry
│   └── ui/               # Window, menu, and visualizer classes
├── src/
│   ├── algorithms/       # Algorithm implementations
│   ├── ui/               # UI component implementations
│   └── main.cpp          # Application entry point
├── CMakeLists.txt        # Build configuration
└── README.md
```
