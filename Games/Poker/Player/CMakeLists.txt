project(PokerPlayer)

add_library(PokerPlayer STATIC player.cpp)
target_include_directories(PokerPlayer PRIVATE ${CARDS_ROOT_DIR} ${CMAKE_CURRENT_LIST_DIR})

add_library(Poker::PokerPlayer ALIAS PokerPlayer)
