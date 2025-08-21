cmake_minimum_required(VERSION 3.10)

project(triangle)

# Variable for the main source file (change this to switch examples)
set(MAIN_FILE src/triangle.cpp)

add_executable(${PROJECT_NAME} ${MAIN_FILE} include/khrplatform.h include/glad.h src/glad.c)

target_include_directories(${PROJECT_NAME} PRIVATE include)

target_link_libraries(${PROJECT_NAME} glfw)