cmake_minimum_required(VERSION 3.20)
project(Numerical_differentiation)
include_directories ("include")
aux_source_directory("src" DIR_SRCS)
aux_source_directory("." DIR_SRCS)

# add_executable(Numerical_differentiation ${DIR_SRCS})

add_library(ND STATIC ${DIR_SRCS})
# add_executable(sqp ${DIR_SRCS})
enable_testing()
add_subdirectory(test)

find_package(OpenMP)
if(OpenMP_CXX_FOUND)
    target_link_libraries(ND PUBLIC OpenMP::OpenMP_CXX)
    message("OPENMP FOUND")

endif()