cmake_minimum_required(VERSION 3.25)
project(school)

set(CMAKE_CXX_STANDARD 17)
add_executable(school main.cpp student.cpp subjectStudent.cpp teacher.cpp subjectTeacher.cpp classYear.cpp)
