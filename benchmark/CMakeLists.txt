cmake_minimum_required(VERSION 3.5)

add_executable(ecc_benchmark benchmark.cpp)
target_link_libraries(ecc_benchmark ecc)
