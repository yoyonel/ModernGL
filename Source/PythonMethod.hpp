#pragma once

struct PythonMethod {
	int version;
	PyCFunction method;
	PyCFunction dummy;
	int flags;

	const char * name;
	const char * doc;
};

extern int pythonMethods;
extern PythonMethod pythonMethod[];

void RegisterMethod(const PythonMethod & method);
