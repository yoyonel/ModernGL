#include "Types.hpp"

static int f1_internal_format[5] = {0, GL_R8, GL_RG8, GL_RGB8, GL_RGBA8};
static int f2_internal_format[5] = {0, GL_R16F, GL_RG16F, GL_RGB16F, GL_RGBA16F};
static int f4_internal_format[5] = {0, GL_R32F, GL_RG32F, GL_RGB32F, GL_RGBA32F};
static int u1_internal_format[5] = {0, GL_R8UI, GL_RG8UI, GL_RGB8UI, GL_RGBA8UI};
static int u2_internal_format[5] = {0, GL_R16UI, GL_RG16UI, GL_RGB16UI, GL_RGBA16UI};
static int u4_internal_format[5] = {0, GL_R32UI, GL_RG32UI, GL_RGB32UI, GL_RGBA32UI};
static int i1_internal_format[5] = {0, GL_R8I, GL_RG8I, GL_RGB8I, GL_RGBA8I};
static int i2_internal_format[5] = {0, GL_R16I, GL_RG16I, GL_RGB16I, GL_RGBA16I};
static int i4_internal_format[5] = {0, GL_R32I, GL_RG32I, GL_RGB32I, GL_RGBA32I};

static MGLDataType f1 = {f1_internal_format, GL_UNSIGNED_BYTE, 1};
static MGLDataType f2 = {f2_internal_format, GL_HALF_FLOAT, 2};
static MGLDataType f4 = {f4_internal_format, GL_FLOAT, 4};
static MGLDataType u1 = {u1_internal_format, GL_UNSIGNED_BYTE, 1};
static MGLDataType u2 = {u2_internal_format, GL_UNSIGNED_SHORT, 2};
static MGLDataType u4 = {u4_internal_format, GL_UNSIGNED_INT, 4};
static MGLDataType i1 = {i1_internal_format, GL_BYTE, 1};
static MGLDataType i2 = {i2_internal_format, GL_SHORT, 2};
static MGLDataType i4 = {i4_internal_format, GL_INT, 4};

// static int invalid_internal_format[5] = {0, 0, 0, 0, 0};
static MGLDataType invalid_data_type = {0, 0, 0};

MGLDataType from_dtype(const char * dtype) {
	// TODO: add switch case with unsigned shorts
	if (!strcmp(dtype, "f1")) {
		return f1;
	}
	if (!strcmp(dtype, "f2")) {
		return f2;
	}
	if (!strcmp(dtype, "f4")) {
		return f4;
	}
	if (!strcmp(dtype, "u1")) {
		return u1;
	}
	if (!strcmp(dtype, "u2")) {
		return u2;
	}
	if (!strcmp(dtype, "u4")) {
		return u4;
	}
	if (!strcmp(dtype, "i1")) {
		return i1;
	}
	if (!strcmp(dtype, "i2")) {
		return i2;
	}
	if (!strcmp(dtype, "i4")) {
		return i4;
	}
	return invalid_data_type;
}
