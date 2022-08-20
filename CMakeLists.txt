cmake_minimum_required(VERSION 3.10)
project(Hazel)

set(CMAKE_CXX_STANDARD 11)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

link_directories(${PROJECT_SOURCE_DIR}/lib)

# ##############################################################################
# Hazel
# ##############################################################################

# spdlog add_subdirectory(hazel/vendor/spdlog)
include_directories(hazel/vendor/spdlog/include)

# glad
set(GLAD_SRC hazel/vendor/glad/src/glad.c)
if(NOT WIN32)
  list(APPEND LIBS dl)
else()
  list(APPEND LIBS Opengl32)
endif(NOT WIN32)
include_directories(hazel/vendor/glad/include)

# glfw
option(GLFW_BUILD_DOCS OFF)
option(GLFW_BUILD_EXAMPLES OFF)
option(GLFW_BUILD_TESTS OFF)
add_subdirectory(hazel/vendor/glfw)
include_directories(hazel/vendor/glfw/include)
list(APPEND LIBS glfw ${GLFW_LIBRARIES})

# Imgui
include_directories(hazel/vendor/imgui)

# glm
include_directories(hazel/vendor/glm)

set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -DHZ_DEBUG")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DHZ_DEBUG")
include_directories(hazel/src)

# stb_image
include_directories(hazel/vendor/stb_image)

file(
  GLOB
  HZ_SRC
  "hazel/src/hazel/core/*.cpp"
  "hazel/src/hazel/imgui/*.cpp"
  "hazel/src/hazel/renderer/*.cpp"
  "hazel/src/platform/windows/*.cpp"
  "hazel/src/platform/opengl/*.cpp"
  "hazel/vendor/imgui/*.cpp"
  "hazel/vendor/stb_image/*.cpp")
add_library(hazel STATIC ${HZ_SRC} ${GLAD_SRC})
target_link_libraries(hazel PUBLIC ${LIBS})

# ##############################################################################
# Sandbox
# ##############################################################################

add_executable(sandbox sandbox/sandbox_app.cpp)
target_link_libraries(sandbox PUBLIC hazel ${LIBS})

add_custom_command(TARGET sandbox
  PRE_BUILD
  COMMAND ${CMAKE_COMMAND}
  -E copy_directory
  ${PROJECT_SOURCE_DIR}/sandbox/assets
  $<TARGET_FILE_DIR:sandbox>/assets
)