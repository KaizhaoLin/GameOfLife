cmake_minimum_required(VERSION 3.16)

project(GameOfLife VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

include_directories(inc)

list(APPEND CMAKE_AUTOUIC_SEARCH_PATHS "resources")

set(PROJECT_SOURCES
    src/main.cpp
    src/BoardWidget.cpp
    src/Canvas.cpp
    src/GameBoard.cpp
    src/GameOfLife.cpp
    src/GameRule.cpp
    src/SelectModePage.cpp
    src/SettingWindow.cpp
    src/TemplatePage.cpp
    inc/BoardWidget.h
    inc/Canvas.h
    inc/GameBoard.h
    inc/GameOfLife.h
    inc/GameRule.h
    inc/SelectModePage.h
    inc/SettingWindow.h
    inc/TemplatePage.h
    resources/Canvas.ui
    resources/GameOfLife.qrc
    resources/GameOfLife.ui
    resources/SelectModePage.ui
    resources/SettingPage.ui
    resources/TemplatePage.ui
)

qt_add_executable(GameOfLife
    MANUAL_FINALIZATION
    ${PROJECT_SOURCES}
)

target_link_libraries(GameOfLife PRIVATE Qt6::Widgets)

set_target_properties(GameOfLife PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS GameOfLife
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

qt_finalize_executable(GameOfLife)