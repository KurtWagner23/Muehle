cmake_minimum_required(VERSION 3.20)
project(muehle VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Unterverzeichnisse für Library, CLI, GUI und Tests
add_subdirectory(libmuehle)
add_subdirectory(cli)
add_subdirectory(gui)
add_subdirectory(tests)
