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
)

target_include_directories(sorting PRIVATE 
    ${CMAKE_SOURCE_DIR}/include/*.hpp
    ${CMAKE_SOURCE_DIR}/include/ui/*.hpp
    ${CURSES_INCLUDE_DIRS}
)

target_link_libraries(sorting PRIVATE
    ${CURSES_LIBRARIES}
)

