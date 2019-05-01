#pragma once
#include "context.hpp"

enum MGLQueryKeys {
    TIME_ELAPSED,
    PRIMITIVES_GENERATED,
    SAMPLES_PASSED,
    ANY_SAMPLES_PASSED,
};

struct MGLQuery : public MGLContextObject {
    int query_obj[4];
};

extern PyType_Spec MGLQuery_spec;
PyObject * MGLContext_meth_query(MGLContext * self, PyObject * const * args, Py_ssize_t nargs);
