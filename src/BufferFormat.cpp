#include "BufferFormat.hpp"

#include "OpenGL.hpp"

FormatNode * InvalidFormat = (FormatNode *)(-1);

FormatIterator::FormatIterator(const char * str) : ptr(str) {
}

FormatInfo FormatIterator::info() {
	FormatInfo info;
	info.nodes = 0;
	info.size = 0;
	info.valid = true;
	info.per_instance = false;

	FormatIterator it = FormatIterator(ptr);
	while (FormatNode * node = it.next()) {
		if (node == InvalidFormat) {
			info.valid = false;
			break;
		}
		info.size += node->count * node->size;
		if (node->type) {
			++info.nodes;
		}
	}

	char post_chr = *it.ptr++;

	if (post_chr == '/') {
		char per_type = *it.ptr++;

		switch (per_type) {
			case 'i':
				info.per_instance = true;
				break;

			case 'v':
				break;

			default:
				info.valid = false;
				break;
		}

		if (*it.ptr) {
			info.valid = false;
		}
	}

	return info;
}

FormatNode * FormatIterator::next() {
	node.count = 0;
	while (true) {
		char chr = *ptr++;
		switch (chr) {
			case '0':
			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '8':
			case '9':
				node.count = node.count * 10 + chr - '0';
				break;

			case 'f':
				if (node.count == 0) {
					node.count = 1;
				}
				if (node.count > 4) {
					return InvalidFormat;
				}
				node.type = GL_FLOAT;
				node.size = 4;
				return &node;

			case 'd':
				if (node.count == 0) {
					node.count = 1;
				}
				if (node.count > 4) {
					return InvalidFormat;
				}
				node.type = GL_DOUBLE;
				node.size = 8;
				return &node;

			case 'i':
				if (node.count == 0) {
					node.count = 1;
				}
				if (node.count > 4) {
					return InvalidFormat;
				}
				node.type = GL_INT;
				node.size = 4;
				return &node;

			case 'x':
				if (node.count == 0) {
					node.count = 1;
				}
				node.type = 0;
				node.size = 1;
				return &node;

			case 0:
			case '/':
				--ptr;
				return node.count ? InvalidFormat : 0;

			default:
				return InvalidFormat;
		}
	}
}
