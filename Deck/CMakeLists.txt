project(Deck)

add_library(Deck STATIC card.cpp deck.cpp)
target_include_directories(Deck PRIVATE ${CMAKE_CURRENT_LIST_DIR})

add_library(Cards::Deck ALIAS Deck)