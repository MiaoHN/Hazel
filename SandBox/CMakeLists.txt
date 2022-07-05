project(Sandbox)

include_directories(../hazel/src)

add_executable(sandbox sandbox_app.cpp)
target_link_libraries(sandbox PUBLIC hazel)