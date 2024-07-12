cmake_minimum_required(VERSION 3.20)
project(FreeFTPClient LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/3rdparty/libcurl-vc-x64-release-dll-ipv6-sspi-schannel")

set(QT_PATH "E:/Qt/6.5.3/msvc2019_64")
set (CMAKE_PREFIX_PATH ${QT_PATH})
find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets StateMachine)
find_package(curl REQUIRED MODULE)

FILE(GLOB INCLUDE "include/*.h" "include/*.hpp")
FILE(GLOB UI "ui/*.ui")
FILE(GLOB SRC "src/*.cpp")

set(CMAKE_AUTOUIC_SEARCH_PATHS "./ui")
set(PROJECT_SOURCES ${INCLUDE} ${UI} ${SRC})

add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})
set_target_properties(${PROJECT_NAME} PROPERTIES WIN32_EXECUTABLE FALSE)
target_link_libraries(${PROJECT_NAME} PUBLIC
        Qt6::Core
        Qt6::Gui
        Qt6::Widgets
        Qt6::StateMachine
        curl
)

target_include_directories(${PROJECT_NAME} PRIVATE "./include")

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:curl> $<TARGET_FILE_DIR:${PROJECT_NAME}>
        COMMAND ${CMAKE_COMMAND} -E remove_directory "${CMAKE_CURRENT_BINARY_DIR}/windeployqt"
        COMMAND "${QT_PATH}/bin/windeployqt.exe" --dir "${CMAKE_CURRENT_BINARY_DIR}" "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}.exe"
)
