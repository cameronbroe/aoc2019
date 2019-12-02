cmake_minimum_required(VERSION 3.15)
project(aoc2019)

set(CMAKE_CXX_STANDARD 17)

macro(AOCLIST result curdir)
    file(GLOB children RELATIVE ${curdir} ${curdir}/*)
    set(dirlist "")
    foreach(child ${children})
        if(IS_DIRECTORY ${curdir}/${child})
            if(${child} MATCHES "day")
                list(APPEND dirlist ${child})
            endif()
        endif()
    endforeach()
    set(${result} ${dirlist})
endmacro()

AOCLIST(AOCDAYS ${CMAKE_SOURCE_DIR})

add_compile_definitions(PROJECT_ROOT="${CMAKE_SOURCE_DIR}")

add_library(aoc_utils utils/utils.cpp)
target_link_libraries(aoc_utils boost_filesystem)
#target_link_libraries(aoc_utils c++fs)
#target_link_libraries(aoc_utils stdc++fs)

foreach(aocday ${AOCDAYS})
    add_executable(aoc-${aocday} ${aocday}/${aocday}.cpp)
    target_link_libraries(aoc-${aocday} aoc_utils)
endforeach()