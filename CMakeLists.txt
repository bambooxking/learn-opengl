cmake_minimum_required(VERSION 3.2)
project(demo)

set(CMAKE_CXX_STANDARD 11)

find_package(OpenGL REQUIRED)

include(${CMAKE_CURRENT_LIST_DIR}/cmake/Dependencies.cmake)

include_directories(
    ${libglfw_INCLUDE_DIRS}
 
    src
    src/glad
)
link_directories(
    
)

file(GLOB_RECURSE SOURCE_FILES
    src/*.c*
    main.cc
)

add_executable(demo ${SOURCE_FILES})

target_link_libraries(demo
    "-framework OpenGL"
)

# install(TARGETS demo DESTINATION .)