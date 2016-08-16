#include "PythonMethod.hpp"

int pythonMethods = 0;
PythonMethod pythonMethod[1024];

void RegisterMethod(const PythonMethod & method) {
	pythonMethod[pythonMethods++] = method;
}
