project(muehle_cli LANGUAGES CXX)

add_executable(muehle_cli main.cpp)
target_link_libraries(muehle_cli PRIVATE muehle_lib)
target_include_directories(muehle_cli PRIVATE ${CMAKE_SOURCE_DIR}/libmuehle)
