#!/bin/bash
# Test that the code builds with the optional features enabled
# (Origin import, update search and download links) in a Debug build.
# Qt 6 is located through CMAKE_PREFIX_PATH, e.g.
#   CMAKE_PREFIX_PATH=$HOME/Qt/6.8.3/gcc_64 scripts/compileTest.sh
cd "$(dirname "$0")/.." || exit 1   # run from the repository root
build=build-compiletest
rm -rf $build
cmake -S . -B $build -DCMAKE_BUILD_TYPE=Debug -DORIGIN_IMPORT=ON \
      -DSEARCH_FOR_UPDATES=ON -DDOWNLOAD_LINKS=ON -DBUILD_TESTS=ON \
    && cmake --build $build -j"$(nproc)"
if [ $? -ne 0 ]; then
    echo "FAILED"
    exit 1
fi
echo "PASSED"
