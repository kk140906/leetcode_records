cmake_minimum_required(VERSION 3.17)
project(LeetCode VERSION 1.0.0 LANGUAGES CXX)

# Retrieve all cpp file in the current cmake source directory
file(GLOB SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.cpp)

# debug message
function(debug_message MESSAGE)
    message("==============================")
    message(${MESSAGE})
    message("==============================")
endfunction()

# add all to executable target
foreach (SRC IN LISTS SOURCES)
    string(REGEX REPLACE "(^.+)\\.(.+$)" \\1 TMP_SRC ${SRC})
    string(REPLACE " " "_" TARGET_NAME ${TMP_SRC})
    add_executable(${TARGET_NAME} ${SRC})
endforeach ()