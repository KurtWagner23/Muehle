project(libmuehle LANGUAGES CXX)

file(GLOB_RECURSE SOURCES "*.cpp" "*.hpp")

# Statische Library erzeugen
add_library(muehle_lib STATIC ${SOURCES})
target_include_directories(muehle_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
