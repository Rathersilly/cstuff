cmake_minimum_required(VERSION 3.16)
project(MyProj CXX)

set(CMAKE_CXX_STANDARD 20)

find_package(spdlog CONFIG REQUIRED)

add_executable(foo foo.cpp)
target_link_libraries(foo PRIVATE spdlog::spdlog)

