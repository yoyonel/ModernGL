#pragma once
#include "python.hpp"

struct GLTypeInfo {
    int cols;
    int rows;
    int shape;
};

void clean_glsl_name(char * name, int & name_len);

int swizzle_from_char(char c);
char char_from_swizzle(int c);

GLTypeInfo type_info(int type);

