# this toolchain file works for cross compiling on Ubuntu when the following prerequisites are given:
# - all dependencies that would be needed for a normal build must be installed as i386 versions
# some of the packets interfere with their x86_64 version (e.g., libfuse-dev:i386, libglib2-dev:i386), so building on a
# normal system will most likely not work, but on systems like Travis it should work fine

set(CMAKE_SYSTEM_NAME Linux CACHE STRING "" FORCE)
set(CMAKE_SYSTEM_PROCESSOR i386 CACHE STRING "" FORCE)

set(CMAKE_C_FLAGS "-m32" CACHE STRING "" FORCE)
set(CMAKE_CXX_FLAGS "-m32" CACHE STRING "" FORCE)

# CMAKE_SHARED_LINKER_FLAGS, CMAKE_STATIC_LINKER_FLAGS etc. must not be set, but CMAKE_EXE_LINKER_FLAGS is necessary
set(CMAKE_EXE_LINKER_FLAGS "-m32" CACHE STRING "" FORCE)

# may help with some rare issues
set(CMAKE_PREFIX_PATH /usr/lib/i386-linux-gnu CACHE STRING "" FORCE)
