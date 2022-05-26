cmake_minimum_required(VERSION 3.1)

project (proj-6-task-1)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_VERBOSE_MAKEFILE OFF)
set(CMAKE_COLOR_MAKEFILE   ON)
set(CMAKE_CXX_FLAGS "-Wall")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG}")
set(CMAKE_CXX_FLAGS_RELEASE "-DNDEBUG -O2")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(PROJECT_LINK_DIRECTORY ${PROJECT_SOURCE_DIR})
add_compile_options(${CMAKE_CXX_FLAGS})

include_directories(${PROJECT_SOURCE_DIR}/headers)
file(GLOB SOURCES ${PROJECT_SOURCE_DIR}/sources/*.cpp)

add_executable(${PROJECT_NAME}.exe main.cpp ${SOURCES})

add_custom_target(run ./proj-6-task-1.exe)
add_custom_target(check valgrind ./proj-6-task-1.exe)