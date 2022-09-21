cmake_minimum_required(VERSION 3.1)

project(StockMarket)

set(CMAKE_CXX_STANDARD 17)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

include_directories(library)
add_subdirectory(source)

add_executable(market main.cpp)
target_link_libraries(market Source)

add_executable(tests tests/tests.cpp)
target_link_libraries(tests Source)

# add_executable(tests tests/test.cpp)