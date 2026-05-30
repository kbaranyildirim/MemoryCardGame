cmake_minimum_required(VERSION 3.10)
project(MemoryCardGame C)

set(CMAKE_C_STANDARD 99)


include_directories(${CMAKE_CURRENT_SOURCE_DIR}/lib/include)


link_directories(${CMAKE_CURRENT_SOURCE_DIR}/lib/bin)


add_executable(MemoryCardGame main.c)


target_link_libraries(MemoryCardGame allegro allegro_main allegro_primitives allegro_font allegro_ttf)