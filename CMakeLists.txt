cmake_minimum_required(VERSION 3.23)
project(project3)

set(CMAKE_CXX_STANDARD 14)

add_executable(project3 main.cpp BinTree.h Node.h Term.cpp Term.h)
