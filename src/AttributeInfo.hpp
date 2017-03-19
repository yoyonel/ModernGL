struct AttributeInfo {
	void * gl_attrib_ptr_proc;
	void * gl_attrib_getter_proc;
	void * gl_attrib_setter_proc;

	int type;
	int scalar_type;

	int dimension;
	int array_length;

	int rows_length;
	int row_length;
	int row_size;

	char shape;
	bool normalizable;
};
