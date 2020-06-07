cmake_minimum_required(VERSION 3.1)

# enable and enforce C++11
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# enable LTO -- not really necessary, but also doesn't hurt
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -flto -Wall -Werror")

# create fully static builds; this should work flawlessly, the code is pretty portable
# libstdc++ is technically GPL (although they claim they won't punish one if linked statically)
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${CMAKE_CXX_FLAGS} -static -static-libgcc -static-libstdc++")

# enable -fPIC/-fPIE
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

add_subdirectory(bluenebula-crypto)

add_subdirectory(python)

add_executable(bluenebula-auth main.cpp)
target_link_libraries(bluenebula-auth PUBLIC bluenebula-crypto)
set_target_properties(bluenebula-auth PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)