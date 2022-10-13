cmake_minimum_required(VERSION 3.8)

project(FloppaExampleGame)

add_executable(FloppaExampleGame main.cpp)

target_link_libraries(FloppaExampleGame FloppaEngine)
