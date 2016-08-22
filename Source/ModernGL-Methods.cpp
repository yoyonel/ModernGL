#include "ModernGL.hpp"

const int implementations = sizeof(implementation) / sizeof(Implementation);

PyMethodDef methods[implementations + 1];

void InitMethods() {
	for (int i = 0; i < implementations; ++i) {
		methods[i].ml_name = (char *)implementation[i].name;
		methods[i].ml_doc = (char *)implementation[i].doc;
		methods[i].ml_flags = implementation[i].flags;
		methods[i].ml_meth = implementation[i].dummy;
	}
}

void LoadMethods() {
	for (int i = 0; i < implementations; ++i) {
		if (versionNumber >= implementation[i].version) {
			methods[i].ml_meth = implementation[i].method;
		}
	}
}
