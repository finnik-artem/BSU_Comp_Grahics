cmake_minimum_required(VERSION 3.16)
project(ColorConverter LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Core GUI)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Core GUI)

add_executable(ColorConverter
    main.cpp
    colorconverter.h
    colorconverter.cpp
    mainwindow.h
    mainwindow.cpp
)

target_link_libraries(ColorConverter PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
