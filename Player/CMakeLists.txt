project(Player)

add_library(Player STATIC player.cpp)
target_include_directories(Player PRIVATE ${CMAKE_CURRENT_LIST_DIR})

add_library(Cards::Player ALIAS Player)