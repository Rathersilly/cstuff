cmake_minimum_required(VERSION 3.16)
project(MyProj CXX)

set(CMAKE_CXX_STANDARD 20)

find_package(spdlog CONFIG REQUIRED)

add_executable(foo foo.cpp)
target_link_libraries(foo PRIVATE spdlog::spdlog)

find_package(Catch2 3 REQUIRED)

# These tests can use the Catch2-provided main
target_link_libraries(foo PRIVATE Catch2::Catch2WithMain)

# These tests need their own main
# add_executable(custom-main-tests test.cpp test-main.cpp)
# target_link_libraries(custom-main-tests PRIVATE Catch2::Catch2)
