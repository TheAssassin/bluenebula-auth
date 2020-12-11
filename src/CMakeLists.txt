cmake_minimum_required(VERSION 3.1)

# enable and enforce C++11
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# since we're (likely) building static binaries on the CI, we should add the architecture as a suffix to the binaries' names
set(CMAKE_EXECUTABLE_SUFFIX -${CMAKE_SYSTEM_PROCESSOR}${CMAKE_EXECUTABLE_SUFFIX})

set(BUILD_PYTHON_MODULE ON CACHE BOOL "")

if(NOT BUILD_PYTHON_MODULE)
    # enable LTO -- not really necessary, but also doesn't hurt
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -flto -Wall -Werror")

    # create fully static builds; this should work flawlessly, the code is pretty portable
    # libstdc++ is technically GPL (although they claim they won't punish one if linked statically)
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${CMAKE_CXX_FLAGS} -static -static-libgcc -static-libstdc++")
endif()

# enable -fPIC/-fPIE
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

add_subdirectory(bluenebula-crypto)

set(BUILD_PYTHON_MODULE ON CACHE BOOL "")
if(BUILD_PYTHON_MODULE)
    add_subdirectory(python)
endif()

add_executable(bluenebula-auth main.cpp)
target_link_libraries(bluenebula-auth PUBLIC bluenebula-crypto)
set_target_properties(bluenebula-auth PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)
