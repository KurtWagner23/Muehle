cmake_minimum_required(VERSION 3.0.0)
project(muehle_commandline VERSION 0.1.0 LANGUAGES C CXX)

set(SOURCE_DIR "${CMAKE_SOURCE_DIR}/src")
file(GLOB_RECURSE SOURCES
    "${SOURCE_DIR}/*.hpp"
    "${SOURCE_DIR}/*.cpp"
)

add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE ${SOURCE_DIR})

