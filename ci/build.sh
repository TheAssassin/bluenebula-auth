#! /bin/bash

# use RAM disk if possible
if [ "$CI" == "" ] && [ -d /dev/shm ]; then
    TEMP_BASE=/dev/shm
else
    TEMP_BASE=/tmp
fi

if [ "$CI" == "" ]; then
    # reserve one core for the rest of the system on dev machines
    NPROC=$(nproc --ignore=1)
else
    # on the CI, we can just use everything we have
    NPROC=$(nproc)
fi

BUILD_DIR=$(mktemp -d -p "$TEMP_BASE" blue-nebula-build-XXXXXX)

cleanup () {
    if [ -d "$BUILD_DIR" ]; then
        rm -rf "$BUILD_DIR"
    fi
}

trap cleanup EXIT

# store repo root as variable
REPO_ROOT="$(readlink -f "$(dirname "$0")")/.."
OLD_CWD="$(readlink -f .)"

pushd "$BUILD_DIR"

# we don't need the Python module
cmake "$REPO_ROOT" -DCMAKE_BUILD_TYPE=Release -DBUILD_PYTHON_MODULE=Off

make -j"$(nproc --ignore=1)"

cp bin/bluenebula-auth "$OLD_CWD"
