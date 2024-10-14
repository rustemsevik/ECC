cmake_minimum_required(VERSION 3.5)
project(ecc VERSION 1.0 DESCRIPTION "3 bit ecc library for encoding and decoding")

add_library(ecc src/ecc.c)

target_include_directories(ecc PUBLIC 
                            "${PROJECT_BINARY_DIR}"
                            "${PROJECT_SOURCE_DIR}/src/"
                            "${PROJECT_SOURCE_DIR}/include/"
                            )

target_sources(ecc PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/src/ecc.c")
target_sources(ecc PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/src/ecc_util.c")

# add option for static and shared build
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

# optionally build example, benchmark or test
option(BUILD_EXAMPLE "Build the example" OFF)
option(BUILD_BENCHMARK "Build the benchmark" OFF)
option(BUILD_TEST "Build the test" OFF)

if (BUILD_EXAMPLE)
    add_subdirectory(example)
endif()

if (BUILD_BENCHMARK)
    add_subdirectory(benchmark)
endif()

if (BUILD_TEST)
    add_subdirectory(test)
endif()


# compiler specific options 
if(UNIX)
#     do something
elseif(WIN32)
#     do something
elseif (MSVC)
#     do something
endif()