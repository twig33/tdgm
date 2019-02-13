# Specify the minimum version for CMake

cmake_minimum_required(VERSION 3.7)

# Project's name

project(gaym)

# Set the output folder where your program will be created

set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)
set(SDL2_PATH "SDL2 path" CACHE STRING "")
SET(SDL2_IMAGELIB "${SDL2_PATH}/lib/libSDL2_image.dll.a")
# The following folder will be included

include_directories("${PROJECT_SOURCE_DIR}")

find_package(SDL2 REQUIRED)

include_directories(${SDL2_INCLUDE_DIR}
                    ${SDL2_IMAGE_INCLUDE_DIR}
                    ${SDL2_TTF_INCLUDE_DIR})

add_executable(gaym ${PROJECT_SOURCE_DIR}/main.cpp ${PROJECT_SOURCE_DIR}/input.cpp ${PROJECT_SOURCE_DIR}/graphics.cpp ${PROJECT_SOURCE_DIR}/entities.cpp ${PROJECT_SOURCE_DIR}/math.cpp ${PROJECT_SOURCE_DIR}/physics.cpp ${PROJECT_SOURCE_DIR}/gamestate.cpp)

target_link_libraries(gaym ${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARIES} ${SDL2_TTF_LIBRARIES} ${SDL2_IMAGELIB})