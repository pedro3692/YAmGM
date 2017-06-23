cmake_minimum_required(VERSION 3.7)
project(YAmGE)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp Window.cpp Window.h Graph/Mesh.cpp Graph/Mesh.h Graph/Shader.cpp Graph/Shader.h Graph/Transform.cpp Graph/Transform.h Graph/Texture.cpp Graph/Texture.h Graph/stb_image.h Graph/Camera.cpp Graph/Camera.h Graph/OBJLoader.cpp Graph/OBJLoader.h)
add_executable(YAmGE ${SOURCE_FILES})

find_package(PkgConfig REQUIRED)

pkg_search_module(GLEW REQUIRED glew)
target_link_libraries(YAmGE ${GLEW_LIBRARIES})
target_include_directories(YAmGE PUBLIC ${GLEW_INCLUDE_DIRS})
target_compile_options(YAmGE PUBLIC ${GLEW_CFLAGS_OTHER})

target_link_libraries(YAmGE glfw)