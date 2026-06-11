#!/bin/bash

set -e

BUILD_DIR="build_release"
APP="cppserver"

configure() {
    if [ ! -d "$BUILD_DIR" ]; then
        echo ">>> Configure project..."
        cmake -S . -B "$BUILD_DIR" \
            -G Ninja \
            -DCMAKE_BUILD_TYPE=Release \
            -DCMAKE_EXPORT_COMPILE_COMMANDS=ON

        ln -sf "$BUILD_DIR/compile_commands.json" compile_commands.json
    fi
}

build() {
    configure

    echo ">>> Building..."
    cmake --build "$BUILD_DIR" -j
}

run() {
    build
    echo ">>> Running..."
    cd "$BUILD_DIR" || exit 1
    ./"$APP"
}

clean() {
    echo ">>> Cleaning..."
    rm -rf "$BUILD_DIR"
    rm -f compile_commands.json
}

rebuild() {
    clean
    build
}

test_project() {
    build

    echo ">>> Running tests..."
    ctest --test-dir "$BUILD_DIR" --output-on-failure
}

format() {
    if ! command -v clang-format &>/dev/null; then
        echo "clang-format not found"
        exit 1
    fi

    echo ">>> Formatting..."

    find . \
        \( -path "./$BUILD_DIR" -o -path "./.git" \) -prune \
        -o \
        \( -name "*.cpp" -o -name "*.cc" -o -name "*.hpp" -o -name "*.h" \) \
        -exec clang-format -i {} \;
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
test)
    test_project
    ;;
format)
    format
    ;;
*)
    echo "Usage:"
    echo "  ./dev.sh build"
    echo "  ./dev.sh run"
    echo "  ./dev.sh clean"
    echo "  ./dev.sh rebuild"
    echo "  ./dev.sh test"
    echo "  ./dev.sh format"
    exit 1
    ;;
esac