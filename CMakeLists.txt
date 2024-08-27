cmake_minimum_required(VERSION 3.20)
project(muehle_commandline VERSION 0.1.0 LANGUAGES C CXX)

set(SOURCE_DIR "${CMAKE_SOURCE_DIR}/src")
file(GLOB_RECURSE SOURCES
"${SOURCE_DIR}/*.hpp"
"${SOURCE_DIR}/*.cpp"
)

add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE ${SOURCE_DIR})

enable_testing()
add_subdirectory(tests)

# Exclude main.cpp from SOURCES for the library
list(FILTER SOURCES EXCLUDE REGEX ".*main\\.cpp")

add_library(${PROJECT_NAME}_lib STATIC ${SOURCES})
target_include_directories(${PROJECT_NAME}_lib PUBLIC src)


