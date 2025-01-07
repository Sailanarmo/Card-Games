project(Poker)

set(POKER_ROOT_DIR ${CMAKE_CURRENT_LIST_DIR})

add_subdirectory(Player)
add_subdirectory(Dealer)
add_subdirectory(Table)
add_subdirectory(Logic)
#add_subdirectory(Rules)

add_executable(Poker main.cpp)
target_include_directories(Poker PRIVATE ${POKER_ROOT_DIR} ${CARDS_ROOT_DIR})
target_link_libraries(Poker PRIVATE Poker::PokerPlayer Poker::PokerDealer Poker::PokerTable Poker::PokerLogic Cards::Deck)