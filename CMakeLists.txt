cmake_minimum_required(VERSION 3.21)

project(Cards)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CARDS_ROOT_DIR ${CMAKE_CURRENT_LIST_DIR})

add_subdirectory(Deck)
add_subdirectory(Games)