cmake_minimum_required(VERSION 3.0)
project(unitTest VERSION 0.0.1)



file(GLOB_RECURSE TEST_SRC_LIST *.c)
foreach(v ${TEST_SRC_LIST})
    string(REGEX MATCH "test/.*" relative_path ${v})
    string(REGEX REPLACE "test/" "" target_name ${relative_path})
    string(REGEX REPLACE "\\.c" "" target_name ${target_name})

    add_executable(${target_name} ${v})
    add_test(NAME ${target_name} COMMAND ${target_name})
    TARGET_LINK_LIBRARIES(${target_name} ND)
endforeach()