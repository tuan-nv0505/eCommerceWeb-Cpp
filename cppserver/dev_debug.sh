#!/bin/bash

set -e

BUILD_DIR="build_debug"
APP="cppserver"

configure() {
    if [ ! -d "$BUILD_DIR" ]; then
        echo ">>> Configure Debug..."

        cmake -S . -B "$BUILD_DIR" \
            -G Ninja \
            -DCMAKE_BUILD_TYPE=Debug \
            -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
    fi
}

build() {
    configure

    echo ">>> Building Debug..."
    cmake --build "$BUILD_DIR" -j
}

run() {
    build

    echo ">>> Running Debug..."
    cd "$BUILD_DIR" || exit 1
    ./"$APP"
}

clean() {
    rm -rf "$BUILD_DIR"
}

rebuild() {
    clean
    build
}

case "$1" in
build)
    build
    ;;
run)
    run
    ;;
clean)
    clean
    ;;
rebuild)
    rebuild
    ;;
*)
    echo "Usage: ./dev_debug.sh {build|run|clean|rebuild}"
    ;;
esac