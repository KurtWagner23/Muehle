project(muehle_tests LANGUAGES CXX)

# GoogleTest mit FetchContent holen
include(FetchContent)

FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG release-1.12.1
)
FetchContent_MakeAvailable(googletest)

enable_testing()

# Test-Executable erstellen
add_executable(muehle_tests test_morris.cpp)
target_link_libraries(muehle_tests PRIVATE muehle_lib gtest gtest_main)
target_include_directories(muehle_tests PRIVATE ${CMAKE_SOURCE_DIR}/libmuehle)

# Tests registrieren
add_test(NAME MuehleTests COMMAND muehle_tests)
