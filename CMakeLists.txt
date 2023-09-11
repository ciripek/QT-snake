cmake_minimum_required(VERSION 3.26)
project(qt_snake)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)


find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        Sql
        REQUIRED)

add_executable(qt_snake src/main.cpp
        src/Database.cpp
        src/Database.hpp
        src/Player.hpp
        src/MainWindow.cpp
        src/MainWindow.hpp
        src/RenderArea.cpp
        src/RenderArea.hpp
        src/Snake.cpp
        src/Snake.hpp)
target_link_libraries(qt_snake
        Qt::Core
        Qt::Gui
        Qt::Widgets
        Qt::Sql
)

