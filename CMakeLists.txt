cmake_minimum_required(VERSION 3.20)
project(FreeFTPClient LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets StateMachine)

FILE(GLOB INCLUDE "include/*.h")
FILE(GLOB UI "ui/*.ui")
FILE(GLOB SRC "src/*.cpp")

set(CMAKE_AUTOUIC_SEARCH_PATHS "./ui")
set(PROJECT_SOURCES
	${INCLUDE}
	${UI}
	${SRC}
)


add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})
set_target_properties(${PROJECT_NAME} PROPERTIES WIN32_EXECUTABLE TRUE)
target_link_libraries(${PROJECT_NAME} PRIVATE
	Qt::Core
	Qt::Gui
	Qt::Widgets
    Qt::StateMachine
)

target_include_directories(${PROJECT_NAME} PRIVATE "./include")
