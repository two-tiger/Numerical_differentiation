cmake_minimum_required(VERSION 3.20)
project(Numerical_differentiation)
include_directories ("include")
aux_source_directory("src" DIR_SRCS)
aux_source_directory("." DIR_SRCS)

add_executable(Numerical_differentiation ${DIR_SRCS})

