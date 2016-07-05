#ifdef _WIN64
#ifndef MS_WIN64
#define MS_WIN64
#endif
#endif

#define REPORT_ARG_TYPE_ERROR(arg, var, type) \
if (!PyObject_TypeCheck((PyObject *)var, &type)) { \
	const char * expected = ((PyTypeObject *)&type)->tp_name; \
	const char * got = ((PyTypeObject *)PyObject_Type((PyObject *)var))->tp_name; \
	PyErr_Format(PyExc_TypeError, __FUNCTION__ "() argument `" arg "` must be %s, not %s", expected, got); \
	return 0; \
}
