cmake_minimum_required(VERSION 3.10)
project(Hazel)

set(CMAKE_CXX_STANDARD 11)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

link_directories(${PROJECT_SOURCE_DIR}/lib)

include_directories(hazel/src)

add_subdirectory(hazel/vendor/spdlog)
include_directories(hazel/vendor/spdlog/include)

file(GLOB HZ_SRC "hazel/src/hazel/*.cpp")
add_library(hazel STATIC ${HZ_SRC})

add_executable(sandbox sandbox/sandbox_app.cpp)
target_link_libraries(sandbox PUBLIC hazel)