#pragma once
#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include <structmember.h>

#define _mgl_str(x) #x
#define _mgl_xstr(x) _mgl_str(x)
#define mgl_mod _mgl_xstr(MODERNGL_MODULE)
#define mgl_ext mgl_mod ".mgl"

#define ensure_num_args(count) if (nargs != count) { PyErr_BadInternalCall(); return NULL; }

/* Wrapper classes for internal objects are defined in python. They must have __slots__ defined.
 * A slot can be accessed in O(1) once detect_class(...) and slot_offset(...) is called.
 */

#define SLOT(obj, type, offset) (*(type **)((char *)obj + offset))

/* Shortcuts */

#define NEW_REF(obj) (Py_INCREF(obj), obj)

#ifndef Py_SETREF
#define Py_SETREF(op, op2)                      \
    do {                                        \
        PyObject *_py_tmp = (PyObject *)(op);   \
        (op) = (op2);                           \
        Py_DECREF(_py_tmp);                     \
    } while (0)
#endif

#ifndef Py_XSETREF
#define Py_XSETREF(op, op2)                     \
    do {                                        \
        PyObject *_py_tmp = (PyObject *)(op);   \
        (op) = (op2);                           \
        Py_XDECREF(_py_tmp);                    \
    } while (0)
#endif

/* Classes defined in python must be instantiated using new_object(...)
 * The allocated memory is initialized to zero.
 * Slots can be set using the SLOT(...) macro.
 */
inline PyObject * _new_object(PyTypeObject * type) {
    PyObject * res = 0;
    Py_INCREF(type);
    if (type->tp_flags & Py_TPFLAGS_HAVE_GC) {
        res = PyObject_GC_New(PyObject, type);
        for (int i = 0; res->ob_type->tp_members[i].name; ++i) {
            SLOT(res, PyObject, (int)res->ob_type->tp_members[i].offset) = 0;
        }
    } else {
        res = PyObject_New(PyObject, type);
    }
    return res;
}

#define new_object(type, typeobj) (type *)_new_object(typeobj)
#define call_function(function, ...) PyObject_CallFunctionObjArgs(function, __VA_ARGS__, (void *)0)

inline void replace_object(PyObject *& src, PyObject * dst) {
    Py_INCREF(dst);
    Py_DECREF(src);
    src = dst;
}
