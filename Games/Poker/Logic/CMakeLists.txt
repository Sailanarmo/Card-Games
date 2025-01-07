project(PokerLogic)

add_library(PokerLogic STATIC hands.cpp states.cpp)
target_include_directories(PokerLogic PRIVATE ${CMAKE_CURRENT_LIST_DIR} ${CARDS_ROOT_DIR})

add_library(Poker::PokerLogic ALIAS PokerLogic)
