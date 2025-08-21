cmake_minimum_required(VERSION 3.10)

project(helloTriangle)

add_executable(helloTriangle main.cpp glad.c glad.h khrplatform.h)

target_link_libraries(helloTriangle glfw)