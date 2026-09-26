cmake_minimum_required(VERSION 3.20)
project(tree)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# Genera compile_commands.json para tu LSP en Neovim
set(CMAKE_EXPORT_COMPILE_COMMANDS ON) 

add_executable(${PROJECT_NAME} src/main.cpp)
