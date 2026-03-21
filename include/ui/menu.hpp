#include <ncurses.h>
#include <string>
#include <vector>
#include <cstdint>
#include <numeric>
#include <ranges>
#include <algorithm>
#include <array>

enum class keys : int {
    enter = 10,

    w = 119,
    a = 97,
    s = 115,
    d = 100,

    j = 106,
    k = 107
};

auto constexpr algorithms = std::to_array<std::string_view>({
    "Bubble sort",
    "Insertion sort",
    "Selection sort",
    "Quick sort",
    "Heap sort"
});

class menu_t {
public:
    menu_t() {
        auto const menu_padding_x = 6;
        auto const menu_padding_y = 2;

        auto it = std::ranges::max_element(algorithms, {}, &std::string_view::size); 
        auto const max_string_length = (it != algorithms.end()) ? it->size() : 0;

        width = std::max<int>(max_string_length + menu_padding_x, title.size() + menu_padding_x);
        height = algorithms.size() + menu_padding_y;

        auto const center_x = (COLS - width) / 2;
        auto const center_y = (LINES - height) / 2;

        view = newwin(height, width, center_y, center_x);
        if (!view) return;
        
        keypad(view, true);
    }

    ~menu_t() {
        if(view) delwin(view);
    }

public:
    void draw() {
        box(view, 0, 0);
        
        mvwprintw(view, 0, (width - title.size()) / 2, "%.*s", static_cast<int>(title.size()), title.data());
        
        for (size_t i = 0; i < algorithms.size(); ++i) {
            if (i == selected_index) wattron(view, A_REVERSE);
        
            mvwprintw(
                view, 
                i + 1, 2, 
                "%-*.*s", 
                width - 4, 
                static_cast<int>(algorithms[i].size()), algorithms[i].data()
            );

            if (i == selected_index) wattroff(view, A_REVERSE);
        }

        wrefresh(view);
    }

    void input() {
        auto const key = static_cast<keys>(wgetch(view));

        switch (key) {
            case keys::enter:
                is_running = false;
                break;
            case keys::w:
            case keys::k:
                selected_index--;
                if (selected_index< 0) selected_index= algorithms.size() - 1;
                break;
            case keys::s:
            case keys::j:
                selected_index++;
                if (selected_index >= static_cast<int>(algorithms.size())) selected_index = 0;
                break;
            case keys::a: break;
            case keys::d: break;
        }
    }

public:
    [[nodiscard]] bool running() const {
        return is_running;
    }
            
    [[nodiscard]] int get_selected_index() const {
        return selected_index;
    }

private:
    std::string_view title = "Select an algorithm";
    WINDOW* view = nullptr;
    int width = 0, height = 0;
    int selected_index = 0;
    bool is_running = true;
};

class sorting_t {
public:
    explicit sorting_t(std::string_view algo_name) : algorithm(algo_name) {
        width = COLS - 4;
        height = LINES - 2;

        int center_x = (COLS- width) / 2;
        int center_y = (LINES- height) / 2;

        view = newwin(height, width, center_y, center_x);
        if (!view) {
            return;
        }

        keypad(view, TRUE);
        is_running = true;
    }

    ~sorting_t() {
        if (view) {
            delwin(view);
        }
    }

    void draw() {
        box(view, 0, 0);

        mvwprintw(view, 0, 2, "[ %.*s Visualizer ]", 
                  static_cast<int>(algorithm.size()), algorithm.data());

        mvwprintw(view, height / 2, (width - 35) / 2, 
                  "Visualizer is running! Press 'q' to quit.");

        wrefresh(view);
    }

    void input() {
        auto const key = wgetch(view);

        if (key == 'q' || key == 'Q') {
            is_running = false;
        }
    }

    [[nodiscard]] bool running() const {
        return is_running;
    }

private:
    std::string_view algorithm;
    WINDOW* view = nullptr;
    int width = 0, height = 0;
    bool is_running = false;
};

class window_t {
public:
    window_t() {
        m_window = initscr();
        if (!m_window) {
            exit(1);
        }

        if (start_color() == ERR || !has_colors()) {
            endwin();
            exit(1);
        }
        
        clear();
        noecho();
        cbreak();
        curs_set(0);

        m_is_running = true;
    }

    ~window_t() {
        endwin();
    }

public:
    [[nodiscard]] auto* window() const {
        return m_window;
    }

private:
    WINDOW* m_window = nullptr;
    bool m_is_running = false;
};
