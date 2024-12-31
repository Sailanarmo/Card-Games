project(PokerTable)

add_library(PokerTable STATIC table.cpp)
target_include_directories(PokerTable PRIVATE ${CMAKE_CURRENT_LIST_DIR} ${CARDS_ROOT_DIR})

add_library(Poker::PokerTable ALIAS PokerTable)