cmake_minimum_required(VERSION 3.10)

project(core)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 11)
file(GLOB SOURCES "src/*.c" "src/*.cc")
add_library(gcom_core STATIC ${SOURCES})
target_include_directories(gcom_core PUBLIC "inc")

