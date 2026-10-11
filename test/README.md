# Tests

- `*.cpp` — C++ tests with GoogleTest (the `unittest` executable); `utils.h` and
  `ApplicationWindowTest.h` hold the helpers.
- `python/` — scripts run inside SciDAVis (`scidavis -x script.py`) when the project is configured
  with `-DSCRIPTING_PYTHON=ON`.
- `data/` — projects (`.sciprj`) and Origin files (`.opj`) opened by the tests; copied to the build
  folder by `CMakeLists.txt`.
- `reference/menus/` — expected menus, compared with the menus written by the test run.

Run them: configure with `-DBUILD_TESTS=ON` and use `ctest --output-on-failure` in the build folder
(on headless machines, `xvfb-run ctest ...`).
