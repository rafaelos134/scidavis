#!/bin/bash
# Build with coverage instrumentation, run the test suite and write an HTML report to
# build-coverage/coverage/index.html (needs lcov). Qt 6 is located through CMAKE_PREFIX_PATH:
#   CMAKE_PREFIX_PATH=$HOME/Qt/6.8.3/gcc_64 scripts/run-coverage.sh
cd "$(dirname "$0")/.." || exit 1   # run from the repository root
build=build-coverage
cmake -S . -B $build -DCMAKE_BUILD_TYPE=Debug -DBUILD_TESTS=ON \
      -DSEARCH_FOR_UPDATES=OFF -DDOWNLOAD_LINKS=OFF \
      -DCMAKE_CXX_FLAGS=--coverage -DCMAKE_C_FLAGS=--coverage || exit 1
cmake --build $build -j"$(nproc)" || exit 1
(cd $build && ctest --output-on-failure)
lcov --capture --directory $build --no-external --base-directory . -o $build/lcov.info
lcov --remove $build/lcov.info '*/3rdparty/*' '*/test/*' '*_autogen/*' -o $build/lcov.info
genhtml --ignore-errors source -o $build/coverage $build/lcov.info
echo "report: $build/coverage/index.html"
