#pragma once

struct FormatNode {
	unsigned type;
	int count;
	int size;
};

struct FormatInfo {
	int nodes;
	int size;
	bool valid;
	bool per_instance;
};

struct FormatIterator {
	const char * ptr;
	FormatNode node;

	FormatIterator(const char * str);

	FormatInfo info();
	FormatNode * next();
};

extern FormatNode * InvalidFormat;
