cmake_minimum_required(VERSION 3.9)
project(card_game)

include_directories(include)

add_subdirectory(engine)

add_executable(${CMAKE_PROJECT_NAME} main.cpp)

