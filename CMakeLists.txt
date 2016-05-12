cmake_minimum_required(VERSION 3.5)
project(cs1d_huffman_coding)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp BinaryTree.h)
add_executable(cs1d_huffman_coding ${SOURCE_FILES})