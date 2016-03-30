cmake_minimum_required(VERSION 2.8)
project(CppLab2)

if (MSVC)
    add_definitions(/W4)
else()
    add_definitions(-Wall)
    add_definitions(-std=c++11)
endif()

include_directories(Catch/include)
include_directories(include)

enable_testing()

set(SOURCES src/string.cpp)


add_executable(test_string tests/test_string.cpp ${SOURCES})

add_test(NAME ${PROJECT_NAME} COMMAND test_string)