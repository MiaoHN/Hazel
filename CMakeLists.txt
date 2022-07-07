cmake_minimum_required(VERSION 3.10)
project(Hazel)

set(CMAKE_CXX_STANDARD 11)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

link_directories(${PROJECT_SOURCE_DIR}/lib)

# ##############################################################################
# Hazel
# ##############################################################################

# spdlog
add_subdirectory(hazel/vendor/spdlog)
include_directories(hazel/vendor/spdlog/include)

# glad
set(GLAD_SRC hazel/vendor/glad/src/glad.c)
if(NOT WIN32)
  LIST(APPEND LIBS dl)
endif(NOT WIN32)
include_directories(hazel/vendor/glad/include)

# glfw
option(GLFW_BUILD_DOCS OFF)
option(GLFW_BUILD_EXAMPLES OFF)
option(GLFW_BUILD_TESTS OFF)
add_subdirectory(hazel/vendor/glfw)
include_directories(hazel/vendor/glfw/include)
list(APPEND LIBS glfw ${GLFW_LIBRARIES})

include_directories(hazel/src)

file(GLOB HZ_SRC "hazel/src/hazel/*.cpp")
file(GLOB HZ_WIN "hazel/src/platform/windows/*.cpp")
add_library(hazel STATIC ${HZ_SRC} ${HZ_WIN} ${GLAD_SRC})
target_link_libraries(hazel PUBLIC ${LIBS} Opengl32)

# ##############################################################################
# Sandbox
# ##############################################################################

add_executable(sandbox sandbox/sandbox_app.cpp)
target_link_libraries(sandbox PUBLIC hazel ${LIBS})
