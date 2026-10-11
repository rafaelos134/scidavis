# SciDAVis

**English** | [Português](README.pt-BR.md)

**SciDAVis** (*Sci*entific *D*ata *A*nalysis and *Vis*ualization) is a free application for
scientific data analysis and visualization: spreadsheets and matrices, publication quality 2D and
3D plots, curve fitting, FFT, integration, smoothing and statistics, with formulas and Python
scripting. It is written in C++20 with Qt 6 and runs on Linux, Windows and macOS.

<picture>
  <source media="(prefers-color-scheme: dark)" srcset="docs/screenshots/scidavis-dark.png">
  <img alt="SciDAVis with a table and a 2D plot" src="docs/screenshots/scidavis-light.png">
</picture>

- **Developer documentation**: [project wiki](https://github.com/rafaelos134/scidavis/wiki)
  (features, architecture, where the calculations are, themes and icons, ...)
- **User manual**: <https://highperformancecoder.github.io/scidavis-handbook/>
- **License**: GPL v2 or later, see [LICENSE](LICENSE) and [CREDITS.md](CREDITS.md)

## Source code organization

All the program logic lives in the `libscidavis` library, grouped by module. Every module folder is
on the include path, so headers are included by file name only (`#include "Graph.h"`).

```
libscidavis/src/
├── app/            Main window and infrastructure
├── project/        Project objects (child windows)
├── analysis/       Numerical operations on curves
│   └── fit/        Curve fitting (regression)
├── plot/           2D plots: layers, curves, axes, legends
│   ├── 3d/         3D plots
│   └── tools/      Interactive mouse tools
├── scripting/      muParser, Python, script editor, SIP bindings
├── dialogs/        Dialog boxes
├── widgets/        Reusable visual components
├── io/             Import/export of external formats
└── future/         "Aspect" framework (newer data layer)
    ├── core/       AbstractAspect, Project, Column, data type filters
    ├── table/      Table model/view (MVC)
    ├── matrix/     Matrix model/view (MVC)
    └── lib/        Utilities (Interval, XmlStreamReader, ActionManager)
```

The executable (`scidavis/`), tests, plugins, documentation and packaging are described on the
[Repository structure](https://github.com/rafaelos134/scidavis/wiki/Repository-Structure) wiki page.

## Building and testing

Requirements: **Qt 6.8 LTS** (Core, Gui, Widgets, Svg, PrintSupport, Xml, OpenGL, OpenGLWidgets and
LinguistTools), a **C++20** compiler (GCC 11+, Clang 14+, MSVC 2022), CMake 3.16+, GSL, muParser and
zlib. Qwt 5 and QwtPlot3D are built together with SciDAVis (do not use the distribution `libqwt*`
packages, they are built for Qt 5).

Example for Linux (Debian/Ubuntu). Distributions often ship a Qt 6 older than 6.8, so it is installed
in `~/Qt` with [aqtinstall](https://github.com/miurahr/aqtinstall), without `sudo`:

```bash
sudo apt install build-essential cmake ninja-build libgl1-mesa-dev libglu1-mesa-dev \
                 libxkbcommon-dev libxcb-cursor0 libmuparser-dev libgsl-dev zlib1g-dev libgtest-dev
pip install --user aqtinstall
python3 -m aqt install-qt linux desktop 6.8.3 linux_gcc_64 -O ~/Qt

git clone --recursive https://github.com/rafaelos134/scidavis.git
cd scidavis
cmake -S . -B build -G Ninja -DCMAKE_BUILD_TYPE=Release \
      -DCMAKE_PREFIX_PATH=$HOME/Qt/6.8.3/gcc_64 \
      -DSEARCH_FOR_UPDATES=OFF -DDOWNLOAD_LINKS=OFF   # optional: -DORIGIN_IMPORT=ON
cmake --build build -j$(nproc)
./build/scidavis/scidavis
```

Already cloned without `--recursive`? Run `git submodule update --init --recursive`.

Tests (GoogleTest):

```bash
cmake -S . -B build -DBUILD_TESTS=ON && cmake --build build -j$(nproc)
cd build && ctest --output-on-failure        # on a headless machine: xvfb-run ctest ...
```

CMake options: `SCRIPTING_MUPARSER` (ON), `SCRIPTING_PYTHON` (OFF), `ORIGIN_IMPORT` (OFF),
`BUILD_TESTS` (OFF), `SEARCH_FOR_UPDATES` (ON), `DOWNLOAD_LINKS` (ON).

### Python scripting (optional)

Python scripting needs SIP 6 and a **PyQt6 built against the same Qt** as SciDAVis: the `PyQt6`
packages on PyPI bundle their own copy of Qt and crash when loaded into SciDAVis. Example with a
virtual environment (building PyQt6 takes 30 to 60 minutes):

```bash
python3 -m venv --system-site-packages ~/Qt/pyqt6-venv
~/Qt/pyqt6-venv/bin/pip install "sip>=6.8" "PyQt-builder>=1.16" "PyQt6-sip>=13.8"
# download and extract the PyQt6 6.8 sources (pyqt6-6.8.1.tar.gz on PyPI), then inside them:
~/Qt/pyqt6-venv/bin/sip-install --qmake ~/Qt/6.8.3/gcc_64/bin/qmake --confirm-license \
    --no-designer-plugin --no-qml-plugin --no-dbus-python --jobs 4 \
    --enable QtCore --enable QtGui --enable QtWidgets --enable QtPrintSupport --enable QtSvg

cmake -S . -B build -DCMAKE_PREFIX_PATH=$HOME/Qt/6.8.3/gcc_64 -DSCRIPTING_PYTHON=ON \
      -DPython3_EXECUTABLE=$HOME/Qt/pyqt6-venv/bin/python
```

More details on the [Python scripting](https://github.com/rafaelos134/scidavis/wiki/Python-Scripting)
wiki page; other platforms are covered in [INSTALL.md](INSTALL.md).

## Contributing

Start with [CONTRIBUTING.md](CONTRIBUTING.md): environment setup, where each part of the program
lives, code rules, tests and pull requests. Planned improvements are listed in
[docs/ROADMAP.md](docs/ROADMAP.md) (in Portuguese), and the [wiki](https://github.com/rafaelos134/scidavis/wiki)
explains the architecture.

To add a new analysis: derive from `Filter` (or from `Fit` for curve fitting) in `analysis/`,
implement `calculateOutputData()` (or the model functions in `fit_gsl.cpp`) and create its dialog in
`dialogs/`.
