#include "../../include/ui/visualizer.h"
#include "../../include/core/sort_observer.h"

#include <algorithm>
#include <chrono>
#include <random>
#include <string>
#include <thread>

SortingVisualizer::SortingVisualizer(std::string_view algoName) : AlgorithmName(algoName) {
    Width = COLS - 4;
    Height = LINES - 2;

    auto const centerX = (COLS - Width) / 2;
    auto const centerY = (LINES - Height) / 2;

    View = NcursesWindow{newwin(Height, Width, centerY, centerX)};
    if (!View) {
        return;
    }

    start_color();
    init_pair(static_cast<int>(ColorPair::Default), COLOR_WHITE, COLOR_BLACK);
    init_pair(static_cast<int>(ColorPair::Pointer), COLOR_CYAN, COLOR_BLACK);
    init_pair(static_cast<int>(ColorPair::Scan), COLOR_RED, COLOR_BLACK);
    init_pair(static_cast<int>(ColorPair::Sorted), COLOR_GREEN, COLOR_BLACK);
    init_pair(static_cast<int>(ColorPair::Pivot), COLOR_YELLOW, COLOR_BLACK);
    init_pair(static_cast<int>(ColorPair::Partition), COLOR_MAGENTA, COLOR_BLACK);

    keypad(View.Get(), TRUE);
    nodelay(View.Get(), TRUE);

    IsRunning = true;
}

void SortingVisualizer::GenerateData(int elementCount, int maxValue) {
    elementCount = (elementCount <= 0) ? std::min((Width - 3) / 2, COLS) : std::max(elementCount, 2);

    Data.resize(static_cast<std::size_t>(elementCount));
    for (int i = 0; i < elementCount; ++i) {
        Data[static_cast<std::size_t>(i)] = (i % maxValue) + 1;
    }

    std::mt19937 rng{std::random_device{}()};
    std::ranges::shuffle(Data, rng);

    SortedIndices.clear();
    Markers.clear();
    ConnectionRange = {-1, -1};
}

void SortingVisualizer::OnSetMarker(int barIndex, char label, int colorPair) {
    if (barIndex >= 0 && barIndex < static_cast<int>(Data.size())) {
        Markers[barIndex] = {.Label = label, .ColorPair = colorPair};
    }
}

void SortingVisualizer::OnClearMarkers() {
    Markers.clear();
    ConnectionRange = {-1, -1};
}

void SortingVisualizer::OnSetConnection(int startIndex, int endIndex) {
    ConnectionRange = {startIndex, endIndex};
}

void SortingVisualizer::OnMarkSorted(int barIndex) {
    SortedIndices.insert(barIndex);
}

bool SortingVisualizer::OnStep() {
    Input();
    Draw();

    std::this_thread::sleep_for(std::chrono::milliseconds(DelayMs));

    return IsRunning;
}

void SortingVisualizer::Draw() {
    werase(View.Get());
    box(View.Get(), 0, 0);

    auto const titleStr = " " + AlgorithmName + " ";
    auto const speedStr = " [-] " + std::to_string(DelayMs) + "ms [+] ";

    mvwprintw(View.Get(), 0, (Width - static_cast<int>(titleStr.size())) / 2, "%s", titleStr.c_str());
    mvwprintw(View.Get(), 0, Width - static_cast<int>(speedStr.size()) - 1, "%s", speedStr.c_str());

    if (Data.empty()) {
        wrefresh(View.Get());
        return;
    }

    auto const floorY = Height - 5;
    auto const maxBarHeight = floorY - 10;
    auto const maxVal = std::ranges::max(Data);

    for (std::size_t i = 0; i < Data.size(); ++i) {
        if (Data[i] <= 0) {
            continue;
        }

        auto const x = 2 + static_cast<int>(i) * 2;
        if (x >= Width - 1) {
            break;
        }

        auto const barHeight = (maxVal > 0) ? (Data[i] * maxBarHeight) / maxVal : 0;
        if (barHeight <= 0) {
            continue;
        }

        int colorPair = static_cast<int>(ColorPair::Default);
        if (SortedIndices.count(i)) {
            colorPair = static_cast<int>(ColorPair::Sorted);
        }

        if (Markers.count(i)) {
            colorPair = Markers.at(i).ColorPair;
        }

        wattron(View.Get(), COLOR_PAIR(colorPair) | A_REVERSE);
        mvwvline(View.Get(), floorY - barHeight + 1, x, ' ', barHeight);
        wattroff(View.Get(), COLOR_PAIR(colorPair) | A_REVERSE);
    }

    if (ConnectionRange.first >= 0 && ConnectionRange.second >= 0) {
        auto x1 = 2 + ConnectionRange.first * 2;
        auto x2 = 2 + ConnectionRange.second * 2;

        if (x1 > x2) {
            std::swap(x1, x2);
        }

        mvwaddch(View.Get(), floorY + 1, x1, ACS_VLINE);
        mvwaddch(View.Get(), floorY + 1, x2, ACS_VLINE);
        mvwaddch(View.Get(), floorY + 2, x1, ACS_LLCORNER);

        for (int x = x1 + 1; x < x2; ++x) {
            mvwaddch(View.Get(), floorY + 2, x, ACS_HLINE);
        }

        mvwaddch(View.Get(), floorY + 2, x2, ACS_LRCORNER);
    }

    for (auto const& [barIndex, markerInfo] : Markers) {
        auto const x = 2 + barIndex * 2;
        if (x < 1 || x >= Width - 1) {
            continue;
        }

        wattron(View.Get(), COLOR_PAIR(markerInfo.ColorPair) | A_BOLD);
        mvwaddch(View.Get(), floorY + 3, x, static_cast<chtype>(markerInfo.Label));
        wattroff(View.Get(), COLOR_PAIR(markerInfo.ColorPair) | A_BOLD);
    }

    mvwprintw(View.Get(), Height - 1, 2, " q: quit | +/-: speed ");
    wrefresh(View.Get());
}

void SortingVisualizer::Input() {
    switch (wgetch(View.Get())) {
    case 'q':
    case 'Q':
        IsRunning = false;
        break;
    case '+':
        DelayMs = std::max(10, DelayMs - 10);
        break;
    case '-':
        DelayMs += 10;
        break;
    default:
        break;
    }
}
