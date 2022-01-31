cmake_minimum_required(VERSION 3.17)
project(mandelbrot C)

set(CMAKE_C_STANDARD 11)

if (CMAKE_BUILD_TYPE MATCHES Debug)
    set(GCC_COMPILE_FLAGS "-Wall -Wextra -Wconversion -pedantic -fsanitize=undefined -fsanitize=address")
    if(CMAKE_SYSTEM_NAME MATCHES "Linux")
        set(GCC_COMPILE_FLAGS "${GCC_COMPILE_FLAGS} -fsanitize=leak")
    endif()
elseif(CMAKE_BUILD_TYPE MATCHES Release)
    set(GCC_COMPILE_FLAGS "-O3")
endif()

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${GCC_COMPILE_FLAGS}")

find_package(MPI REQUIRED)
include_directories(${MPI_C_INCLUDE_PATH})

add_executable(mandelbrot sequential.c complex.h complex.c)

target_link_libraries(mandelbrot ${MPI_C_LIBRARIES} -lm)
