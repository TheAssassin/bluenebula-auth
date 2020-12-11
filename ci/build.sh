#! /bin/bash

set -e
set -x

# use RAM disk if possible
if [ "$CI" == "" ] && [ -d /dev/shm ]; then
    temp_base=/dev/shm
else
    temp_base=/tmp
fi

if [ "$CI" == "" ]; then
    # reserve one core for the rest of the system on dev machines
    nproc=$(nproc --ignore=1)
else
    # on the CI, we can just use everything we have
    nproc=$(nproc)
fi

build_dir=$(mktemp -d -p "$temp_base" blue-nebula-build-XXXXXX)

cleanup () {
    if [ -d "$build_dir" ]; then
        rm -rf "$build_dir"
    fi
}

trap cleanup EXIT

# store repo root as variable
repo_root="$(readlink -f "$(dirname "$0")")/.."
old_cwd="$(readlink -f .)"

pushd "$build_dir"

extra_cmake_args=()
if [[ "$ARCH" == "i386" ]]; then
    extra_cmake_args+=("-DCMAKE_TOOLCHAIN_FILE=$repo_root/cmake/toolchains/i386-linux-gnu.cmake")
fi

# we don't need the Python module
cmake "$repo_root" -DCMAKE_BUILD_TYPE=Release -DBUILD_PYTHON_MODULE=Off "${extra_cmake_args[@]}"

make -j"$(nproc --ignore=1)"

cp bin/bluenebula-auth-* "$old_cwd"
