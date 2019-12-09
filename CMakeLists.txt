cmake_minimum_required(VERSION 3.13)
project(fekt_pc1t_bingo)

set(CMAKE_CXX_STANDARD 17)

find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})


add_executable(fekt_pc1t_bingo main.c generator.c generator.h board.c board.h options.h options.c)
target_link_libraries(fekt_pc1t_bingo ${CURSES_LIBRARIES})