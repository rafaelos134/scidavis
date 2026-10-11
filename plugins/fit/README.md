# Curve fitting plugins

Examples of fit functions loaded by the fit wizard (Analysis → Fit Wizard) from shared libraries.
Each subfolder is an independent plugin in C or C++ using GSL; the loader is
`libscidavis/src/analysis/fit/PluginFit.cpp`.

To create a plugin, copy one of the examples (e.g. `explin/`), change the function and add an
`add_subdirectory(...)` line and the target to `plugins/fit/CMakeLists.txt`.
