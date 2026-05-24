cmake_minimum_required(VERSION 3.20)

project(sort LANGUAGES CXX)

add_executable(sort
        source/main.cpp

        source/core/application.cpp

        source/infrastructure/timer/timer.cpp
        source/infrastructure/files/files.cpp

        source/sort_algorithm/bubble_sort.cpp
        source/sort_algorithm/insert_sort.cpp
        source/sort_algorithm/selection_sort.cpp
        source/sort_algorithm/shell_sort.cpp
        source/sort_algorithm/quick_sort.cpp

        source/ui/console.cpp
        source/ui/menus/main_menu.cpp
        source/ui/menus/matrix_menu.cpp

        source/utils/random.cpp
        source/utils/algorithm_factory.cpp
        source/utils/matrix_utils.cpp

        source/tests/tests.cpp
)

target_include_directories(sort PRIVATE source)
target_compile_features(sort PRIVATE cxx_std_20)

set_target_properties(sort PROPERTIES CXX_EXTENSIONS OFF)

if(MSVC)
    target_compile_options(sort PRIVATE /W4)
else()
    target_compile_options(sort PRIVATE -Wall -Wextra -Wpedantic)
endif()
