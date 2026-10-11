/***************************************************************************
    File                 : PythonGilLock.h
    Project              : SciDAVis
    Description          : RAII guard for the Python global interpreter lock
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *  This program is free software; you can redistribute it and/or modify  *
 *  it under the terms of the GNU General Public License as published by  *
 *  the Free Software Foundation; either version 2 of the License, or      *
 *  (at your option) any later version.                                    *
 *                                                                         *
 ***************************************************************************/
#ifndef PYTHONGILLOCK_H
#define PYTHONGILLOCK_H

// must be included after Python.h

//! Holds the Python GIL for the lifetime of the object (may be nested).
/**
 * PyQt6 releases the GIL around calls from Python into C++, so any C++ entry point that uses
 * the Python C API must take it back. Only valid after Py_Initialize().
 */
struct PythonGilLock
{
    PythonGilLock() : state(PyGILState_Ensure()) { }
    ~PythonGilLock() { PyGILState_Release(state); }
    PythonGilLock(const PythonGilLock &) = delete;
    PythonGilLock &operator=(const PythonGilLock &) = delete;
    PyGILState_STATE state;
};

#endif // PYTHONGILLOCK_H
