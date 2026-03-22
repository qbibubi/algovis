#include "../../include/ui/menu.h"

#include <algorithm>
#include <ranges>

namespace {
constexpr int KeyEnter = 10;
constexpr int KeyW = 119;
constexpr int KeyS = 115;
constexpr int KeyJ = 106;
constexpr int KeyK = 107;
} // namespace

AlgorithmMenu::AlgorithmMenu() {
    constexpr int paddingX = 6;
    constexpr int paddingY = 2;

    auto const longest = std::ranges::max_element(AlgorithmRegistry, {}, [](AlgorithmEntry const& entry) { return entry.Name.size(); });
    auto const maxNameLen = (longest != AlgorithmRegistry.end()) ? longest->Name.size() : 0u;

    Width = static_cast<int>(std::max(maxNameLen, Title.size())) + paddingX;
    Height = static_cast<int>(AlgorithmRegistry.size()) + paddingY;

    auto const centerX = (COLS - Width) / 2;
    auto const centerY = (LINES - Height) / 2;

    View = NcursesWindow{newwin(Height, Width, centerY, centerX)};
    if (!View) {
        return;
    }

    keypad(View.Get(), TRUE);

    IsRunning = true;
}

void AlgorithmMenu::Draw() {
    box(View.Get(), 0, 0);

    auto const titleX = static_cast<int>((Width - static_cast<int>(Title.size())) / 2);
    auto const titleSize = static_cast<int>(Title.size());

    mvwprintw(View.Get(), 0, titleX, "%.*s", titleSize, Title.data());

    for (std::size_t i = 0; i < AlgorithmRegistry.size(); ++i) {
        if (i == SelectedIndex) {
            wattron(View.Get(), A_REVERSE);
        }

        mvwprintw(View.Get(), static_cast<int>(i) + 1, 2, "%-*.*s", Width - 4, static_cast<int>(AlgorithmRegistry[i].Name.size()), AlgorithmRegistry[i].Name.data());

        if (i == SelectedIndex) {
            wattroff(View.Get(), A_REVERSE);
        }
    }

    wrefresh(View.Get());
}

void AlgorithmMenu::Input() {
    switch (wgetch(View.Get())) {
    case KeyEnter:
        IsRunning = false;
        break;
    case KeyW:
    case KeyK:
        SelectedIndex = (SelectedIndex == 0) ? AlgorithmRegistry.size() - 1 : SelectedIndex - 1;
        break;
    case KeyS:
    case KeyJ:
        SelectedIndex = (SelectedIndex + 1 >= AlgorithmRegistry.size()) ? 0 : SelectedIndex + 1;
        break;
    default:
        break;
    }
}
