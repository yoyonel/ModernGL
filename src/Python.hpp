#include <Python.h>

#if PY_MAJOR_VERSION >= 3

// TODO:

#else

// TODO: fix memleak
#define PyUnicode_AsUTF8(obj) PyUnicode_AS_DATA(PyUnicode_AsASCIIString(obj))

// TODO: check for compatibility
#define PyException_HEAD PyObject_HEAD PyObject * dict; PyObject * args; PyObject * traceback; PyObject * context; PyObject * cause;

#endif
