cmake_minimum_required(VERSION 3.6)

project(LowLatencyApp)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_COMPILER g++)
set(CMAKE_CXX_FLAGS "-std=c++2a -Wall -Wextra -Werror -Wpedantic")
set(CMAKE_VERBOSE_MAKEFILE on)

# everytime I create a new .cpp file, I must add it here,
# as the cmake configuration is done only once.
file(GLOB SOURCES "test.cpp" "threads.cpp" "thread_example.cpp mem_pool_example.cpp")

include_directories(${PROJECT_SOURCE_DIR})

# add the build code as a libcommon library (code is inside 
# libcommon.a
add_library(libcommon STATIC ${SOURCES})

# add this custom, just-defined libcommon onto the LIBS variable
list(APPEND LIBS libcommon)
# pthread stands for POSIX Threads. 
# It is the standard, built-in multithreading library for 
# Linux (and other Unix-like systems). 
# It lives deep in the system folders (usually somewhere like /usr/lib)
list(APPEND LIBS pthread)

# have different executables used in this chapter ready to be 
# built

# build this runnable executable out of this .cpp file
add_executable(thread_example thread_example.cpp)
add_executable(mem_pool_example mem_pool_example.cpp)
# when finding the code this exec depends on, go to the LIBS variable
target_link_libraries(thread_example PUBLIC ${LIBS})

add_executable(threads threads.cpp)
target_link_libraries(threads PUBLIC ${LIBS})
