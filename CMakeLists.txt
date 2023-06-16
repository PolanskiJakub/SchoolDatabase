cmake_minimum_required(VERSION 3.25)
project(school)

set(CMAKE_CXX_STANDARD 17)
file(STRINGS "student.txt" ASD)
add_executable(school main.cpp student.cpp subjectStudent.cpp)
