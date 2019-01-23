#include "bytecode.hpp"

#include "context.hpp"

#include "internal/modules.hpp"
#include "internal/wrapper.hpp"
#include "internal/tools.hpp"
#include "internal/glsl.hpp"

/*
glViewport(x=0, y=0, width=1280, height=720)
glUniformMatrix4fv(location=0, count=1, transpose=false, value=0000024EEE98BDB8)
glUniform3fv(location=1, count=1, value=0000024EE2DED590)
glClearBufferfv(buffer=GL_DEPTH, drawbuffer=0, value=0000024EE2422278)
glClearBufferfv(buffer=GL_COLOR, drawbuffer=0, value=0000024EE24222A8)
glEnable(cap=GL_DEPTH_TEST)
glActiveTexture(texture=GL_TEXTURE0)
glBindTexture(target=GL_TEXTURE_2D, texture=2)
glBindSampler(unit=0, sampler=2)
glBindVertexArray(array=1)
glDrawArraysInstanced(mode=GL_TRIANGLES, first=0, count=36, instancecount=1)
glActiveTexture(texture=GL_TEXTURE0)
glBindTexture(target=GL_TEXTURE_2D, texture=1)
glBindSampler(unit=0, sampler=1)
glBindVertexArray(array=2)
glDrawArraysInstanced(mode=GL_TRIANGLES, first=0, count=36, instancecount=1)
glActiveTexture(texture=GL_TEXTURE0)
glBindTexture(target=GL_TEXTURE_2D, texture=2)
glBindSampler(unit=0, sampler=2)
glBindVertexArray(array=3)
glDrawArraysInstanced(mode=GL_TRIANGLES, first=0, count=36, instancecount=1)
*/

PyTypeObject * MGLRecorder_class;

namespace {
enum Opcode {
    OP_glEnable,
    OP_glDisable,
    OP_glViewport,
    OP_glScissor,
    OP_glUniformMatrix4fv,
    OP_glUniform3fv,
    OP_glClearBufferfv,
    OP_glBindVertexArray,
    OP_glDrawArraysInstanced,
    OP_glActiveTexture,
    OP_glBindTexture,
    OP_glBindSampler,
};

char buffer[16384];
char * ptr = buffer;
GLMethods rec = {};
GLMethods gl = {};

template <typename T>
inline void write(const T & value) {
    *(T *)ptr = value;
    ptr += sizeof(T);
}

template <typename T>
inline void write(const T * array, int count) {
    memcpy(ptr, array, sizeof(T) * count);
    ptr += sizeof(T) * count;
}

template <typename T>
inline T read() {
    ptr += sizeof(T);
    return *(T *)(ptr - sizeof(T));
}

template <typename T>
inline T * read(int count) {
    ptr += sizeof(T) * count;
    return (T *)(ptr - sizeof(T) * count);
}

void GLAPI rec_glEnable(GLenum cap) {
    write(OP_glEnable);
    write(cap);
}

void GLAPI rec_glDisable(GLenum cap) {
    write(OP_glDisable);
    write(cap);
}

void GLAPI rec_glViewport(GLint x, GLint y, GLsizei width, GLsizei height) {
    write(OP_glViewport);
    write(height);
    write(width);
    write(y);
    write(x);
}

void GLAPI rec_glScissor(GLint x, GLint y, GLsizei width, GLsizei height) {
    write(OP_glScissor);
    write(height);
    write(width);
    write(y);
    write(x);
}

void GLAPI rec_glUniformMatrix4fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat * value) {
    write(OP_glUniformMatrix4fv);
    write(value, 16);
    write(transpose);
    write(count);
    write(location);
}

void GLAPI rec_glUniform3fv(GLint location, GLsizei count, const GLfloat * value) {
    write(OP_glUniform3fv);
    write(value, 3);
    write(count);
    write(location);
}

void GLAPI rec_glClearBufferfv(GLenum buffer, GLint drawbuffer, const GLfloat * value) {
    write(OP_glClearBufferfv);
    write(value, 4);
    write(drawbuffer);
    write(buffer);
}

void GLAPI rec_glBindVertexArray(GLuint array) {
    write(OP_glBindVertexArray);
    write(array);
}

void GLAPI rec_glDrawArraysInstanced(GLenum mode, GLint first, GLsizei count, GLsizei instancecount) {
    write(OP_glDrawArraysInstanced);
    write(instancecount);
    write(count);
    write(first);
    write(mode);
}

void GLAPI rec_glActiveTexture(GLenum texture) {
    write(OP_glActiveTexture);
    write(texture);
}

void GLAPI rec_glBindTexture(GLenum target, GLuint texture) {
    write(OP_glBindTexture);
    write(texture);
    write(target);
}

void GLAPI rec_glBindSampler(GLuint unit, GLuint sampler) {
    write(OP_glBindSampler);
    write(sampler);
    write(unit);
}
}

PyObject * MGLContext_meth_replay(MGLContext * self, PyObject * bytecode) {
    memcpy(&gl, &self->gl, sizeof(GLMethods));

    Py_buffer view = {};
    PyObject_GetBuffer(bytecode, &view, PyBUF_STRIDED_RO);
    PyBuffer_ToContiguous(buffer, &view, view.len, 'C');
    PyBuffer_Release(&view);

    ptr = buffer;
    char * end = buffer + view.len;

    while (ptr < end) {
        switch (read<Opcode>()) {
            case OP_glEnable: gl.Enable(read<GLenum>()); break;
            case OP_glDisable: gl.Disable(read<GLenum>()); break;
            case OP_glViewport: gl.Viewport(read<GLint>(), read<GLint>(), read<GLsizei>(), read<GLsizei>()); break;
            case OP_glScissor: gl.Scissor(read<GLint>(), read<GLint>(), read<GLsizei>(), read<GLsizei>()); break;
            case OP_glUniformMatrix4fv: gl.UniformMatrix4fv(read<GLint>(), read<GLsizei>(), read<GLboolean>(), read<GLfloat>(16)); break;
            case OP_glUniform3fv: gl.Uniform3fv(read<GLint>(), read<GLsizei>(), read<GLfloat>(3)); break;
            case OP_glClearBufferfv: gl.ClearBufferfv(read<GLenum>(), read<GLint>(), read<GLfloat>(4)); break;
            case OP_glBindVertexArray: gl.BindVertexArray(read<GLuint>()); break;
            case OP_glDrawArraysInstanced: gl.DrawArraysInstanced(read<GLenum>(), read<GLint>(), read<GLsizei>(), read<GLsizei>()); break;
            case OP_glActiveTexture: gl.ActiveTexture(read<GLenum>()); break;
            case OP_glBindTexture: gl.BindTexture(read<GLenum>(), read<GLuint>()); break;
            case OP_glBindSampler: gl.BindSampler(read<GLuint>(), read<GLuint>()); break;
        }
    }
    Py_RETURN_NONE;
}

// read<>(), read<>(), read<>(), read<>(), read<>(), read<>(), read<>(), read<>(), read<>(), read<>(), read<>(),

MGLRecorder * MGLRecorder_meth_enter(MGLRecorder * self) {
    memcpy(&gl, &self->context->gl, sizeof(GLMethods));
    void ** src = (void **)&rec;
    void ** dst = (void **)&self->context->gl;
    int size = sizeof(GLMethods) / sizeof(void *);
    for (int i = 0; i < size; ++i) {
        if (dst[i]) {
            dst[i] = src[i];
        }
    }
    return NEW_REF(self);
}

PyObject * MGLRecorder_meth_exit(MGLRecorder * self) {
    memcpy(&self->context->gl, &gl, sizeof(GLMethods));
    Py_RETURN_NONE;
}

PyObject * MGLRecorder_meth_dump(MGLRecorder * self) {
    PyObject * res = PyBytes_FromStringAndSize(buffer, ptr - buffer);
    ptr = buffer;
    return res;
}

PyMethodDef MGLRecorder_methods[] = {
    {"__enter__", (PyCFunction)MGLRecorder_meth_enter, METH_NOARGS, 0},
    {"__exit__", (PyCFunction)MGLRecorder_meth_exit, METH_VARARGS, 0},
    {"dump", (PyCFunction)MGLRecorder_meth_dump, METH_NOARGS, 0},
    {0},
};

PyType_Slot MGLRecorder_slots[] = {
    {Py_tp_methods, MGLRecorder_methods},
    {0},
};

PyType_Spec MGLRecorder_spec = {
    mgl_name ".Recording",
    sizeof(MGLRecorder),
    0,
    Py_TPFLAGS_DEFAULT,
    MGLRecorder_slots,
};

void initialize_recording() {
    rec.Enable = rec_glEnable;
    rec.Disable = rec_glDisable;
    rec.Viewport = rec_glViewport;
    rec.Scissor = rec_glScissor;
    rec.UniformMatrix4fv = rec_glUniformMatrix4fv;
    rec.Uniform3fv = rec_glUniform3fv;
    rec.ClearBufferfv = rec_glClearBufferfv;
    rec.BindVertexArray = rec_glBindVertexArray;
    rec.DrawArraysInstanced = rec_glDrawArraysInstanced;
    rec.ActiveTexture = rec_glActiveTexture;
    rec.BindTexture = rec_glBindTexture;
    rec.BindSampler = rec_glBindSampler;

    MGLRecorder_class = (PyTypeObject *)PyType_FromSpec(&MGLRecorder_spec);
}
