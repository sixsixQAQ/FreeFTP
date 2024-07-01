cmake_minimum_required(VERSION 3.20)
project(FreeFTPClient LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/3rdparty/libcurl-vc-x64-release-dll-ipv6-sspi-schannel")

find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets StateMachine)
find_package(curl REQUIRED MODULE)

FILE(GLOB INCLUDE "include/*.h" "include/*.hpp")
FILE(GLOB UI "ui/*.ui")
FILE(GLOB SRC "src/*.cpp")

set(CMAKE_AUTOUIC_SEARCH_PATHS "./ui")
set(PROJECT_SOURCES
	${INCLUDE}
	${UI}
	${SRC}
)

add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})
set_target_properties(${PROJECT_NAME} PROPERTIES WIN32_EXECUTABLE FALSE)
target_link_libraries(${PROJECT_NAME} PUBLIC
	Qt::Core
	Qt::Gui
	Qt::Widgets
    Qt::StateMachine
	curl
)

target_include_directories(${PROJECT_NAME} PRIVATE "./include")
