# Contributing to SciDAVis

**English** | [Português](CONTRIBUTING.pt-BR.md)

Thanks for your interest! This guide is the shortest path from zero to your first contribution.
To understand the project from the inside (modules, architecture, where the calculations are), see
the [README](README.md) and the [wiki](https://github.com/rafaelos134/scidavis/wiki).

## 1. Set up the environment

Requirements: Qt 6.8 LTS, a C++20 compiler (GCC 11+, Clang 14+ or MSVC 2022), CMake 3.16+, GSL,
muParser and zlib. The complete Linux walkthrough is in the README; in short:

```bash
git clone --recursive https://github.com/rafaelos134/scidavis.git
cd scidavis
cmake -S . -B build -G Ninja -DCMAKE_PREFIX_PATH=$HOME/Qt/6.8.3/gcc_64 -DBUILD_TESTS=ON
cmake --build build -j$(nproc)
./build/scidavis/scidavis
```

Cloned without `--recursive`? Run `git submodule update --init --recursive`.

## 2. Find something to work on

- [docs/ROADMAP.md](docs/ROADMAP.md) (in Portuguese) lists planned improvements, with the steps and
  the files involved in each of them.
- Bugs and feature requests are tracked in the GitHub issues.

## 3. Where things are

| I want to work on... | Folder |
|---|---|
| Calculations (fits, FFT, integration, statistics) | `libscidavis/src/analysis/` |
| 2D and 3D plots | `libscidavis/src/plot/` |
| Tables, matrices, notes, project folders | `libscidavis/src/project/` and `libscidavis/src/future/` |
| Dialog boxes | `libscidavis/src/dialogs/` |
| Reusable visual components | `libscidavis/src/widgets/` |
| Formulas and scripts (muParser/Python) | `libscidavis/src/scripting/` |
| Main window, themes, icons | `libscidavis/src/app/` and `scidavis/resources/` |
| Translations | `scidavis/translations/` |
| Tests | `test/` |
| Documentation | `docs/` and the [wiki](https://github.com/rafaelos134/scidavis/wiki) |

## 4. Code rules

- **New file**: put it in the module folder and add it to the `HEADERS`/`SRCS` lists of
  `libscidavis/CMakeLists.txt`. Includes use the file name only (`#include "Graph.h"`): every module
  folder is already on the include path.
- **Style**: run `clang-format -i <file>` before committing (rules in `.clang-format`). To do it
  automatically: `ln -s ../../scripts/pre-commit.py .git/hooks/pre-commit`.
- **Icons**: always `IconLoader::load("name")`, with the SVG in `scidavis/resources/icons/themed/`
  (see [Themes and icons](https://github.com/rafaelos134/scidavis/wiki/Themes-and-Icons) on the
  wiki). No bitmaps and no hard-coded colors in the interface.
- **Formula inputs**: call `BracketHighlighter::attach(input)` to color the brackets.
- **Signals and slots**: prefer `connect(obj, &Class::signal, ...)`. The `SIGNAL()`/`SLOT()` form
  is not checked by the compiler.
- **User-visible text**: always inside `tr("...")`, in English. Translations live in the `.ts` files.
- **Moving files**: use `git mv` to keep the history.

## 5. Test

```bash
cd build && ctest --output-on-failure     # on a headless machine: xvfb-run ctest ...
```

Changed something visible? Check it with the light and the dark theme (Edit → Preferences → Theme).
Touched numbers? Check it with the interface in Portuguese (decimal comma) and in English (decimal
point).

## 6. Submit your contribution

1. Create a branch from `master` (`git checkout -b my-improvement`).
2. Make small commits, each with a message that explains *what* and *why*.
3. Open a pull request describing the change and how you tested it. The CI builds and tests on
   Linux, Windows and macOS automatically.
