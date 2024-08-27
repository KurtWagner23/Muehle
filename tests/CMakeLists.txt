include(FetchContent)

FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        release-1.11.0
)
FetchContent_MakeAvailable(googletest)
add_library(GTest::GTest INTERFACE IMPORTED)
target_link_libraries(GTest::GTest INTERFACE gtest_main)


# Test-Verzeichnis CMake-Datei
set(TEST_SOURCES test_morris.cpp)

# Füge die Tests hinzu
add_executable(runTests ${TEST_SOURCES})

# Verknüpfe die Test-Executable mit der Hauptanwendung
target_link_libraries(runTests PRIVATE muehle_commandline_lib GTest::GTest)



# Registriere den Test mit CMake
add_test(NAME RunUnitTests COMMAND runTests)
