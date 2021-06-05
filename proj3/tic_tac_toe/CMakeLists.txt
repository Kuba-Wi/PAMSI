cmake_minimum_required(VERSION 3.14)

project(tic_tac_toe LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Core Quick REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core Quick REQUIRED)

set(PROJECT_SOURCES
        main.cpp
        ../board.cpp
        ../node.cpp
        ticTacModel.cpp
        qml.qrc
)

set(FLAGS -Wall -pedantic -Wextra)
include_directories(..)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(tic_tac_toe ${PROJECT_SOURCES})
else()
    add_executable(tic_tac_toe ${PROJECT_SOURCES})
endif()

target_compile_options(tic_tac_toe PRIVATE ${FLAGS})

target_compile_definitions(tic_tac_toe
  PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
target_link_libraries(tic_tac_toe
  PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Quick)
