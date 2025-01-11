project(GoFishTable)

add_library(GoFishTable STATIC table.cpp)
target_include_directories(GoFishTable PRIVATE ${CMAKE_CURRENT_SOURCE_DIR} ${CARDS_ROOT_DIR})

add_library(GoFish::GoFishTable ALIAS GoFishTable)