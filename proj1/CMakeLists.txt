cmake_minimum_required(VERSION 3.10)
#set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(sort_functions)
set(FLAGS -Wall -pedantic -Wextra)

add_executable(${PROJECT_NAME} main.cpp)
target_compile_options(${PROJECT_NAME} PRIVATE ${FLAGS})

add_executable(${PROJECT_NAME}-ut tests.cpp catch_main.cpp)
target_compile_options(${PROJECT_NAME}-ut PRIVATE ${FLAGS})

enable_testing()
add_test(NAME ${PROJECT_NAME}_tests COMMAND ${PROJECT_NAME}-ut)
