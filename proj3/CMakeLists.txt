cmake_minimum_required(VERSION 3.10)
# set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(QT_APP "Whether to build desktop app with GUI" ON)

project(min_max)
set(FILES
    board.cpp
    node.cpp
)
set(FLAGS -Wall -pedantic -Wextra)

add_library(lib_core STATIC ${FILES})
target_compile_options(lib_core PRIVATE ${FLAGS})

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} lib_core)
target_compile_options(${PROJECT_NAME} PRIVATE ${FLAGS})

if(QT_APP)
    add_subdirectory(tic_tac_toe)
endif()
