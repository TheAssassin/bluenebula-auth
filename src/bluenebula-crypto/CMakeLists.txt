cmake_minimum_required(VERSION 3.1)

set(library_name bluenebula-crypto)

add_library(${library_name} STATIC tools.h crypto.h crypto_lowlevel.cpp crypto_highlevel.cpp)
target_include_directories(${library_name} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
