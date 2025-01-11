project(GoFishPlayer)

add_library(GoFishPlayer STATIC player.cpp)
target_include_directories(GoFishPlayer PRIVATE ${CMAKE_CURRENT_SOURCE_DIR} ${CARDS_ROOT_DIR})

add_library(GoFish::GoFishPlayer ALIAS GoFishPlayer)