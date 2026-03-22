cmake_minimum_required(VERSION 4.3)

project(SORTING VERSION 0.1 LANGUAGES CXX)

set(CURSES_NEED_NCURSES TRUE)
set(CURSES_NEED_WIDE TRUE)
find_package(Curses REQUIRED)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

add_compile_options(
    -Wall
    -Wpedantic
    -Wextra
)

add_executable(sorting
    src/main.cpp

    src/ui/menu.cpp
    src/ui/visualizer.cpp
    src/ui/window.cpp

    src/algorithms/bubble_sort.cpp
    src/algorithms/insertion_sort.cpp
    src/algorithms/quick_sort.cpp
    src/algorithms/selection_sort.cpp
    src/algorithms/heap_sort.cpp
)

target_compile_features(sorting PRIVATE cxx_std_20)

target_include_directories(sorting PRIVATE 
    include
    ${CURSES_INCLUDE_DIRS}
)

target_link_libraries(sorting PRIVATE
    ${CURSES_LIBRARIES}
)

