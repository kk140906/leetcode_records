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

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(BuildType "dbg_")
endif ()

# add all to executable target
foreach (SRC IN LISTS SOURCES)
    string(REGEX REPLACE "(^.+)\\.(.+$)" \\1 TMP_SRC ${SRC})
    string(REPLACE " " "_" TARGET_NAME ${TMP_SRC})
    add_executable(${TARGET_NAME} ${SRC})
    target_include_directories(${TARGET_NAME} PRIVATE include)
    if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
        target_compile_options(${TARGET_NAME} PRIVATE -fsanitize=address)
        # set link directories
        target_link_directories(${TARGET_NAME} PRIVATE
                "D:/Microsoft Visual Studio/2019/Enterprise/VC/Tools/MSVC/14.28.29333/lib/x64/")
        target_link_libraries(${TARGET_NAME} PRIVATE
                clang_rt.asan_${BuildType}dynamic-x86_64
                clang_rt.asan_${BuildType}dynamic_runtime_thunk-x86_64)
        target_link_options(${TARGET_NAME} PRIVATE
                /wholearchive:clang_rt.asan_${BuildType}dynamic_runtime_thunk-x86_64.lib)
    endif ()
endforeach ()