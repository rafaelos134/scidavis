# runs the coverage test, building HTML display of test-covered code
# build first with coverage instrumentation, e.g.
#cmake -S . -B build -DBUILD_TESTS=ON -DCMAKE_CXX_FLAGS=--coverage
#cmake --build build -j4
cd "$(dirname "$0")/.." || exit 1   # run from the repository root
for i in test/00/*; do
    sh $i
done

# gen_info source path rewriting no longer seems to cope with the
# scidavis file layout, so just fake it by creating some symbolic
# links where lcov and genhtml expect the source files to be
ln -sf `pwd`/libscidavis/src tmp
ln -sf `pwd`/test/*.{h,cpp} tmp/test
dir=tmp/libscidavis

lcov -i -c -d . --exclude tmp/test --no-external -o lcovi.info
lcov -c -d . --exclude tmp/test  --no-external -o lcovt.info
rm lcov.info
lcov -a lcovi.info -a lcovt.info -o lcov.info
genhtml --ignore-errors source -o coverage lcov.info
