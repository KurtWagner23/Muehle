project(muehle_gui LANGUAGES CXX)

# FetchContent für Raylib
include(FetchContent)

FetchContent_Declare(
    raylib
    GIT_REPOSITORY https://github.com/raysan5/raylib.git
    GIT_TAG 5.0
)
FetchContent_MakeAvailable(raylib)

add_executable(muehle_gui main.cpp)
target_link_libraries(muehle_gui PRIVATE muehle_lib raylib)
target_include_directories(muehle_gui PRIVATE ${CMAKE_SOURCE_DIR}/libmuehle)

file(COPY ${CMAKE_SOURCE_DIR}/assets DESTINATION ${CMAKE_BINARY_DIR}/gui)

