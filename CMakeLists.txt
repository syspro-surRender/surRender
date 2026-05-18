cmake_minimum_required(VERSION 3.28)

project(surRender)


file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/assets)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/assets/ 
     DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/assets/)

set(CMAKE_CXX_STANDARD 23)
set(CXX_STANDARD_REQUIRED ON)

find_package(PkgConfig REQUIRED)
find_package(OpenGL REQUIRED COMPONENTS OpenGL)
find_package(glfw3 REQUIRED)
find_package(GLEW REQUIRED)
find_package(spdlog REQUIRED)
# find_package(ASSIMP REQUIRED)

pkg_check_modules(ASSIMP REQUIRED assimp)

include_directories(${GLUT_INCLUDE_DIRS})
include_directories(include/ libs/)

file(GLOB source_files "*.h" "*.cpp" "src/*.cpp" "include/*.h" "libs/*.h" "libs/*.c")
file(GLOB_RECURSE lib_files "libs/*.h" "libs/*.c" "libs/*.cpp")
set(ALL_SRC_FILES ${source_files} ${lib_files})
add_executable(surRender ${ALL_SRC_FILES})

add_compile_options(surRender "-fsanitize=address")

target_link_libraries(surRender OpenGL::OpenGL glfw GLEW spdlog::spdlog ${ASSIMP_LIBRARIES})
