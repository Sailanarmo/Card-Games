project(PokerDealer)

add_library(PokerDealer STATIC dealer.cpp)
target_include_directories(PokerDealer PRIVATE ${CMAKE_CURRENT_LIST_DIR} ${CARDS_ROOT_DIR})

add_library(Poker::PokerDealer ALIAS PokerDealer)