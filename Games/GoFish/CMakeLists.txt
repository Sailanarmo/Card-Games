project(GoFish)

add_subdirectory(Player)
add_subdirectory(Table)

add_executable(GoFish main.cpp)
target_include_directories(GoFish PRIVATE ${CMAKE_CURRENT_SOURCE_DIR} ${CARDS_ROOT_DIR})
target_link_libraries(GoFish GoFish::GoFishPlayer GoFish::GoFishTable Cards::Deck)