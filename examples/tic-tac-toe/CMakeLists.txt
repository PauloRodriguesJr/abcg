cmake_minimum_required(VERSION 3.11)

# Project wich will be created on /build/bin
project(tic-tac-toe)

add_executable(${PROJECT_NAME} main.cpp openglwindow.cpp)

enable_abcg(${PROJECT_NAME})