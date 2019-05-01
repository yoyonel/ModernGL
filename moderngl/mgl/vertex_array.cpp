#include "vertex_array.hpp"
#include "buffer.hpp"
#include "context.hpp"
#include "program.hpp"
#include "scope.hpp"

#include "internal/wrapper.hpp"

/* MGLContext.vertex_array(program, content, index_buffer)
 */
PyObject * MGLContext_meth_vertex_array(MGLContext * self, PyObject * const * args, Py_ssize_t nargs) {
    ensure_num_args(3);

    PyObject * program = args[0];
    PyObject * content = args[1];
    PyObject * index_buffer = args[2];

    if (index_buffer != Py_None && index_buffer->ob_type != Buffer_class) {
        return 0;
    }

    PyObject * attributes = SLOT(program, PyObject, Program_class_attributes);

    content = PySequence_Fast(content, "content is not iterable");
    if (!content) {
        return 0;
    }

    MGLVertexArray * vertex_array = MGLContext_new_object(self, VertexArray);

    const GLMethods & gl = self->gl;
    gl.GenVertexArrays(1, (GLuint *)&vertex_array->vertex_array_obj);

    if (!vertex_array->vertex_array_obj) {
        PyErr_Format(moderngl_error, "cannot create vertex array");
        return 0;
    }

    self->bind_vertex_array(vertex_array->vertex_array_obj);

    int vertices = 0x7fffffff;
    int content_len = (int)PySequence_Fast_GET_SIZE(content);

    for (int i = 0; i < content_len; ++i) {
        PyObject * item = PySequence_Fast_GET_ITEM(content, i);
        int item_len = (int)PySequence_Fast_GET_SIZE(item);
        if (item_len < 3) {
            PyErr_Format(moderngl_error, "err1");
            return 0;
        }

        PyObject * buffer_wrapper = PySequence_Fast_GET_ITEM(item, 0);
        if (buffer_wrapper->ob_type != Buffer_class) {
            return 0;
        }

        PyObject * format = PySequence_Fast_GET_ITEM(item, 1);
        if (!PyUnicode_Check(format)) {
            PyErr_Format(moderngl_error, "err2");
            return 0;
        }

        PyObject * format_split = PyObject_CallFunctionObjArgs(moderngl_split_format, format, 0);
        if (!format_split) {
            return 0;
        }

        MGLBuffer * buffer = SLOT(buffer_wrapper, MGLBuffer, Buffer_class_mglo);
        self->bind_array_buffer(buffer->buffer_obj);

        PyObject * nodes = PyTuple_GET_ITEM(format_split, 0);
        int divisor = PyLong_AsLong(PyTuple_GET_ITEM(format_split, 1));
        int stride = PyLong_AsLong(PyTuple_GET_ITEM(format_split, 2));

        if (!i && divisor) {
            return 0;
        }

        if (!divisor) {
            int cap = (int)(buffer->size / stride);
            vertices = vertices < cap ? vertices : cap;
        }

        int nodes_len = (int)PySequence_Fast_GET_SIZE(nodes);
        int nodes_cnt = 0;

        char * ptr = 0;
        for (int j = 2; j < item_len; ++j) {
            PyObject * name = PySequence_Fast_GET_ITEM(item, j);

            if (!PyUnicode_Check(name)) {
                PyErr_Format(moderngl_error, "err4");
                return 0;
            }

            PyObject * attrib = PyDict_GetItem(attributes, name);
            if (!attrib) {
                ptr += stride;
                // PyErr_Format(moderngl_error, "err4");
                // return 0;
                continue;
            }

            int location = PyLong_AsLong(SLOT(attrib, PyObject, Attribute_class_location));
            int rows = PyLong_AsLong(SLOT(attrib, PyObject, Attribute_class_rows));
            int size = PyLong_AsLong(SLOT(attrib, PyObject, Attribute_class_size));

            int count = 0;
            int shape = 0;
            int bytes = 0;
            int type = 0;

            while (true) {
                if (nodes_cnt == nodes_len) {
                    PyErr_Format(moderngl_error, "err4");
                    return 0;
                }

                PyObject * tup = PySequence_Fast_GET_ITEM(nodes, nodes_cnt);
                count = PyLong_AsLong(PyTuple_GET_ITEM(tup, 0));
                shape = PyUnicode_READ_CHAR(PyTuple_GET_ITEM(tup, 1), 0);
                bytes = PyLong_AsLong(PyTuple_GET_ITEM(tup, 2));
                nodes_cnt += 1;

                if (shape != 'x') {
                    break;
                }
            }

            switch (shape) {
                case 'f':
                    switch (bytes) {
                        case 1: type = GL_UNSIGNED_BYTE; break;
                        case 2: type = GL_HALF_FLOAT; break;
                        case 4: type = GL_FLOAT; break;
                        case 8: type = GL_DOUBLE; break;
                    }
                    break;
                case 'i':
                    switch (bytes) {
                        case 1: type = GL_BYTE; break;
                        case 2: type = GL_SHORT; break;
                        case 4: type = GL_INT; break;
                    }
                    break;
                case 'u':
                    switch (bytes) {
                        case 1: type = GL_UNSIGNED_BYTE; break;
                        case 2: type = GL_UNSIGNED_SHORT; break;
                        case 4: type = GL_UNSIGNED_INT; break;
                    }
                    break;
            }

            if (!type) {
                return 0;
            }

            int locations = rows * size;
            int vsize = count / rows;

            for (int r = 0; r < locations; ++r) {
                switch (shape) {
                    case 'f': gl.VertexAttribPointer(location, vsize, type, shape == 'f' && bytes == 1, stride, ptr); break;
                    case 'i': gl.VertexAttribIPointer(location, vsize, type, stride, ptr); break;
                    case 'u': gl.VertexAttribIPointer(location, vsize, type, stride, ptr); break;
                    case 'd': gl.VertexAttribLPointer(location, vsize, type, stride, ptr); break;
                }

                gl.VertexAttribDivisor(location, divisor);
                gl.EnableVertexAttribArray(location);
                ptr += count * bytes / rows;
                location += 1;
            }
        }

        Py_DECREF(item);
    }

    vertex_array->max_vertices = vertices;

    SLOT(vertex_array->wrapper, PyObject, VertexArray_class_ibo) = NEW_REF(Py_None);
    SLOT(vertex_array->wrapper, PyObject, VertexArray_class_program) = NEW_REF(program);
    SLOT(vertex_array->wrapper, PyObject, VertexArray_class_scope) = NEW_REF(Py_None);
    SLOT(vertex_array->wrapper, PyObject, VertexArray_class_mode) = NEW_REF(Py_None);
    SLOT(vertex_array->wrapper, PyObject, VertexArray_class_vertices) = PyLong_FromLong(vertices);

    if (PyObject_SetAttrString(vertex_array->wrapper, "index_buffer", index_buffer)) {
        return 0;
    }

    return NEW_REF(vertex_array->wrapper);
}

/* MGLVertexArray.render(mode, vertices, first, instances, color_mask, depth_mask)
 */
PyObject * MGLVertexArray_meth_render(MGLVertexArray * self, PyObject * const * args, Py_ssize_t nargs) {
    ensure_num_args(6);

    PyObject * mode = args[0];
    int vertices = PyLong_AsLong(args[1]);
    int first = PyLong_AsLong(args[2]);
    int instances = PyLong_AsLong(args[3]);
    unsigned long long color_mask = PyLong_AsUnsignedLongLong(args[4]);
    bool depth_mask = (bool)PyObject_IsTrue(args[5]);

    if (vertices < 0) {
        vertices = PyLong_AsLong(SLOT(self->wrapper, PyObject, VertexArray_class_vertices));
    }

    if (mode == Py_None) {
        mode = SLOT(self->wrapper, PyObject, VertexArray_class_mode);
        if (mode == Py_None) {
            mode = triangles_long;
        }
    }

    int render_mode = PyLong_AsLong(mode);
    if (PyErr_Occurred()) {
        return 0;
    }

    const GLMethods & gl = self->context->gl;

    PyObject * program = SLOT(self->wrapper, PyObject, VertexArray_class_program);
    self->context->use_program(SLOT(program, MGLProgram, Program_class_mglo)->program_obj);
    self->context->bind_vertex_array(self->vertex_array_obj);
    self->context->set_write_mask(color_mask, depth_mask);

    bool scoped = false;
    PyObject * scope = SLOT(self->wrapper, PyObject, VertexArray_class_scope);
    MGLScope * scope_mglo = 0;

    if (scope != Py_None) {
        scope_mglo = SLOT(scope, MGLScope, Scope_class_mglo);
        if (self->context->bound_scope != scope_mglo) {
            MGLScope_begin_core(scope_mglo);
            scoped = true;
        }
    } else if (self->context->bound_scope != self->context->active_scope) {
        scope_mglo = self->context->bound_scope;
        MGLScope_begin_core(scope_mglo);
        scoped = true;
    }

    if (SLOT(self->wrapper, PyObject, VertexArray_class_ibo) != Py_None) {
        const void * ptr = (const void *)((GLintptr)first * 4);
        gl.DrawElementsInstanced(render_mode, vertices, GL_UNSIGNED_INT, ptr, instances);
    } else {
        gl.DrawArraysInstanced(render_mode, first, vertices, instances);
    }

    if (scoped) {
        MGLScope_end_core(scope_mglo);
    }

    Py_RETURN_NONE;
}

/* MGLVertexArray.render_indirect(buffer, mode, count, first, color_mask, depth_mask)
 */
PyObject * MGLVertexArray_meth_render_indirect(MGLVertexArray * self, PyObject * const * args, Py_ssize_t nargs) {
    ensure_num_args(4);

    if (args[0]->ob_type != Buffer_class) {
        // TODO: error
        return 0;
    }

    MGLBuffer * indirect_buffer = SLOT(args[0], MGLBuffer, Buffer_class_mglo);
    PyObject * mode = args[1];
    int count = PyLong_AsLong(args[2]);
    int first = PyLong_AsLong(args[3]);
    unsigned long long color_mask = PyLong_AsUnsignedLongLong(args[4]);
    bool depth_mask = (bool)PyObject_IsTrue(args[5]);

    MGLBuffer * index_buffer = SLOT(self->wrapper, MGLBuffer, VertexArray_class_ibo);

    if (count < 0) {
        count = (int)((PyObject *)index_buffer != Py_None ? index_buffer->size / 4 : indirect_buffer->size / 20);
    }

    if (mode == Py_None) {
        mode = SLOT(self->wrapper, PyObject, VertexArray_class_mode);
        if (mode == Py_None) {
            mode = triangles_long;
        }
    }

    int render_mode = PyLong_AsLong(mode);
    if (PyErr_Occurred()) {
        return 0;
    }

    const GLMethods & gl = self->context->gl;

    PyObject * program = SLOT(self->wrapper, PyObject, VertexArray_class_program);
    self->context->use_program(SLOT(program, MGLProgram, Program_class_mglo)->program_obj);
    self->context->bind_vertex_array(self->vertex_array_obj);
    self->context->set_write_mask(color_mask, depth_mask);

    bool scoped = false;
    PyObject * scope = SLOT(self->wrapper, PyObject, VertexArray_class_scope);
    MGLScope * scope_mglo = 0;

    if (scope != Py_None) {
        scope_mglo = SLOT(scope, MGLScope, Scope_class_mglo);
        if (self->context->bound_scope != scope_mglo) {
            MGLScope_begin_core(scope_mglo);
            scoped = true;
        }
    } else if (self->context->bound_scope != self->context->active_scope) {
        scope_mglo = self->context->bound_scope;
        MGLScope_begin_core(scope_mglo);
        scoped = true;
    }

	gl.BindBuffer(GL_DRAW_INDIRECT_BUFFER, indirect_buffer->buffer_obj);

	const void * ptr = (const void *)((GLintptr)first * 20);

	if ((PyObject *)index_buffer != Py_None) {
		gl.MultiDrawElementsIndirect(render_mode, GL_UNSIGNED_INT, ptr, count, 20);
	} else {
		gl.MultiDrawArraysIndirect(render_mode, ptr, count, 20);
	}

    if (scoped) {
        MGLScope_end_core(scope_mglo);
    }

    Py_RETURN_NONE;
}

/* MGLVertexArray.transform(output, mode, vertices, first, instances, flush)
 */
PyObject * MGLVertexArray_meth_transform(MGLVertexArray * self, PyObject * const * args, Py_ssize_t nargs) {
    ensure_num_args(6);

    if (args[0]->ob_type != Buffer_class) {
        // TODO: error
        return 0;
    }

    MGLBuffer * output_buffer = SLOT(args[0], MGLBuffer, Buffer_class_mglo);
    PyObject * mode = args[1];
    int vertices = PyLong_AsLong(args[2]);
    int first = PyLong_AsLong(args[3]);
    int instances = PyLong_AsLong(args[4]);
    int flush = PyObject_IsTrue(args[5]);

    if (vertices < 0) {
        vertices = PyLong_AsLong(SLOT(self->wrapper, PyObject, VertexArray_class_vertices));
    }

    if (mode == Py_None) {
        mode = SLOT(self->wrapper, PyObject, VertexArray_class_mode);
        if (mode == Py_None) {
            mode = points_long;
        }
    }

    int render_mode = PyLong_AsLong(mode);
    if (PyErr_Occurred()) {
        return 0;
    }

    const GLMethods & gl = self->context->gl;

    PyObject * program = SLOT(self->wrapper, PyObject, VertexArray_class_program);
    self->context->use_program(SLOT(program, MGLProgram, Program_class_mglo)->program_obj);
    self->context->bind_vertex_array(self->vertex_array_obj);

    bool scoped = false;
    PyObject * scope = SLOT(self->wrapper, PyObject, VertexArray_class_scope);
    MGLScope * scope_mglo = 0;

    if (scope != Py_None) {
        scope_mglo = SLOT(scope, MGLScope, Scope_class_mglo);
        if (self->context->bound_scope != scope_mglo) {
            MGLScope_begin_core(scope_mglo);
            scoped = true;
        }
    } else if (self->context->bound_scope != self->context->active_scope) {
        scope_mglo = self->context->bound_scope;
        MGLScope_begin_core(scope_mglo);
        scoped = true;
    }

    gl.BindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, 0, output_buffer->buffer_obj);
    gl.Enable(GL_RASTERIZER_DISCARD);
    gl.BeginTransformFeedback(render_mode);

    if (SLOT(self->wrapper, PyObject, VertexArray_class_ibo) != Py_None) {
        const void * ptr = (const void *)((GLintptr)first * 4);
        gl.DrawElementsInstanced(render_mode, vertices, GL_UNSIGNED_INT, ptr, instances);
    } else {
        gl.DrawArraysInstanced(render_mode, first, vertices, instances);
    }

    gl.EndTransformFeedback();
    if (~self->context->current_enable_only & MGL_RASTERIZER_DISCARD) {
        gl.Disable(GL_RASTERIZER_DISCARD);
    }

    if (scoped) {
        MGLScope_end_core(scope_mglo);
    }

    if (flush) {
        gl.Flush();
    }

    Py_RETURN_NONE;
}

/* MGLVertexArray.transform_indirect(output, buffer, mode, count, first, flush)
 */
PyObject * MGLVertexArray_meth_transform_indirect(MGLVertexArray * self, PyObject * const * args, Py_ssize_t nargs) {
    ensure_num_args(6);

    if (args[0]->ob_type != Buffer_class) {
        // TODO: error
        return 0;
    }

    if (args[1]->ob_type != Buffer_class) {
        // TODO: error
        return 0;
    }

    MGLBuffer * output_buffer = SLOT(args[0], MGLBuffer, Buffer_class_mglo);
    MGLBuffer * indirect_buffer = SLOT(args[1], MGLBuffer, Buffer_class_mglo);

    PyObject * mode = args[2];
    int count = PyLong_AsLong(args[3]);
    int first = PyLong_AsLong(args[4]);
    int flush = PyObject_IsTrue(args[5]);

    MGLBuffer * index_buffer = SLOT(self->wrapper, MGLBuffer, VertexArray_class_ibo);

    if (count < 0) {
        count = (int)((PyObject *)index_buffer != Py_None ? index_buffer->size / 4 : indirect_buffer->size / 20);
    }

    if (mode == Py_None) {
        mode = SLOT(self->wrapper, PyObject, VertexArray_class_mode);
        if (mode == Py_None) {
            mode = points_long;
        }
    }

    int render_mode = PyLong_AsLong(mode);
    if (PyErr_Occurred()) {
        return 0;
    }

    const GLMethods & gl = self->context->gl;

    PyObject * program = SLOT(self->wrapper, PyObject, VertexArray_class_program);
    self->context->use_program(SLOT(program, MGLProgram, Program_class_mglo)->program_obj);
    self->context->bind_vertex_array(self->vertex_array_obj);

    MGLBuffer * output = SLOT(output_buffer, MGLBuffer, Buffer_class_mglo);
    gl.BindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, 0, output->buffer_obj);
    gl.Enable(GL_RASTERIZER_DISCARD);
    gl.BeginTransformFeedback(render_mode);

    bool scoped = false;
    PyObject * scope = SLOT(self->wrapper, PyObject, VertexArray_class_scope);
    MGLScope * scope_mglo = 0;

    if (scope != Py_None) {
        scope_mglo = SLOT(scope, MGLScope, Scope_class_mglo);
        if (self->context->bound_scope != scope_mglo) {
            MGLScope_begin_core(scope_mglo);
            scoped = true;
        }
    } else if (self->context->bound_scope != self->context->active_scope) {
        scope_mglo = self->context->bound_scope;
        MGLScope_begin_core(scope_mglo);
        scoped = true;
    }

	gl.BindBuffer(GL_DRAW_INDIRECT_BUFFER, indirect_buffer->buffer_obj);

	const void * ptr = (const void *)((GLintptr)first * 20);

	if ((PyObject *)index_buffer != Py_None) {
		gl.MultiDrawElementsIndirect(render_mode, GL_UNSIGNED_INT, ptr, count, 20);
	} else {
		gl.MultiDrawArraysIndirect(render_mode, ptr, count, 20);
	}

    gl.EndTransformFeedback();
    if (~self->context->current_enable_only & MGL_RASTERIZER_DISCARD) {
        gl.Disable(GL_RASTERIZER_DISCARD);
    }

    if (scoped) {
        MGLScope_end_core(scope_mglo);
    }

    if (flush) {
        gl.Flush();
    }

    Py_RETURN_NONE;
}

/* MGLVertexArray.ibo
 */
int MGLVertexArray_set_ibo(MGLVertexArray * self, PyObject * value) {
    if (value != Py_None && value->ob_type != Buffer_class) {
        PyErr_Format(PyExc_TypeError, "expected Buffer got %s", value->ob_type->tp_name);
        return -1;
    }

    PyObject *& ibo_slot = SLOT(self->wrapper, PyObject, VertexArray_class_ibo);
    replace_object(ibo_slot, value);

    PyObject *& vertices_slot = SLOT(self->wrapper, PyObject, VertexArray_class_vertices);
    Py_DECREF(vertices_slot);

    self->context->bind_vertex_array(self->vertex_array_obj);

    if (value == Py_None) {
        vertices_slot = PyLong_FromLong(self->max_vertices);
        self->context->gl.BindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    } else {
        MGLBuffer * ibo = SLOT(value, MGLBuffer, Buffer_class_mglo);
        vertices_slot = PyLong_FromLong((int)(ibo->size / 4));
        self->context->gl.BindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo->buffer_obj);
    }

    return 0;
}

void MGLVertexArray_dealloc(MGLVertexArray * self) {
    Py_TYPE(self)->tp_free(self);
}

fastcallable(MGLVertexArray_meth_render)
fastcallable(MGLVertexArray_meth_render_indirect)
fastcallable(MGLVertexArray_meth_transform)
fastcallable(MGLVertexArray_meth_transform_indirect)

PyMethodDef MGLVertexArray_methods[] = {
    {"render", fastcall(MGLVertexArray_meth_render), fastcall_flags, NULL},
    {"render_indirect", fastcall(MGLVertexArray_meth_render_indirect), fastcall_flags, NULL},
    {"transform", fastcall(MGLVertexArray_meth_transform), fastcall_flags, NULL},
    {"transform_indirect", fastcall(MGLVertexArray_meth_transform_indirect), fastcall_flags, NULL},
    {0},
};

PyGetSetDef MGLVertexArray_getset[] = {
    {"ibo", 0, (setter)MGLVertexArray_set_ibo, 0, 0},
    {0},
};

PyType_Slot MGLVertexArray_slots[] = {
    {Py_tp_methods, MGLVertexArray_methods},
    {Py_tp_getset, MGLVertexArray_getset},
    {Py_tp_dealloc, (void *)MGLVertexArray_dealloc},
    {0},
};

PyType_Spec MGLVertexArray_spec = {
    "moderngl.mgl.new.MGLVertexArray",
    sizeof(MGLVertexArray),
    0,
    Py_TPFLAGS_DEFAULT,
    MGLVertexArray_slots,
};
