#include "batch.hpp"
#include "context.hpp"

#include "framebuffer.hpp"
#include "scope.hpp"
#include "sampler.hpp"
#include "program.hpp"
#include "texture.hpp"
#include "vertex_array.hpp"

#include "internal/wrapper.hpp"

#include "internal/modules.hpp"
#include "internal/tools.hpp"

/* MGLContext.batch()
 */
PyObject * MGLContext_meth_batch(MGLContext * self, PyObject * const * args, Py_ssize_t nargs) {
    if (nargs != 1) {
        // TODO: error
        return 0;
    }

    PyObject * seq = PySequence_Fast(args[0], "not iterable");
    if (!seq) {
        return 0;
    }

    MGLBatch * batch = MGLContext_new_object(self, Batch);

    int num_tasks = (int)PySequence_Fast_GET_SIZE(seq);
    batch->tasks = (MGLBatchTask *)malloc(sizeof(MGLBatchTask) * num_tasks);
    batch->num_tasks = num_tasks;

    for (int i = 0; i < num_tasks; ++i) {
        MGLBatchTask & task = batch->tasks[i];

        PyObject * item = PySequence_Fast(PySequence_Fast_GET_ITEM(seq, i), "");
        // if (PySequence_Fast_GET_SIZE(item) ...)
        task.task_code = PyLong_AsLong(PySequence_Fast_GET_ITEM(item, 0));
        PyObject * wrapper = PySequence_Fast_GET_ITEM(item, 1);
        PyObject * args = PySequence_Fast_GET_ITEM(item, 2);

        Py_buffer view = {};
        PyObject_GetBuffer(args, &view, PyBUF_STRIDED_RO);
        // if (view.len ...)
        PyBuffer_ToContiguous(task.raw, &view, view.len, 'C');
        PyBuffer_Release(&view);

        switch (task.task_code) {
            case MGL_SCOPE_USE_TASK: {
                task.scope = SLOT(wrapper, MGLScope, Scope_class_mglo);
                break;
            }

            case MGL_VAO_SIMPLE_RENDER_TASK: {
                task.vertex_array = SLOT(wrapper, MGLVertexArray, VertexArray_class_mglo);
                break;
            }

            case MGL_FBO_SIMPLE_CLEAR_TASK: {
                task.framebuffer = SLOT(wrapper, MGLFramebuffer, Framebuffer_class_mglo);
                break;
            }
        }

        Py_DECREF(item);
    }
    Py_DECREF(seq);

    return NEW_REF(batch->wrapper);
}

/* MGLBatch.run()
 */
PyObject * MGLBatch_meth_run(MGLBatch * self) {
    MGLContext * ctx = self->context;
    const GLMethods & gl = ctx->gl;

    for (int i = 0; i < self->num_tasks; ++i) {
        const MGLBatchTask & task = self->tasks[i];
        switch (task.task_code) {
            case MGL_SCOPE_USE_TASK: {
                if (task.scope->enable_only >= 0) {
                    task.scope->old_enable_only = ctx->current_enable_only;
                    ctx->enable(task.scope->enable_only);
                }

                if (task.scope->framebuffer) {
                    MGLFramebuffer_use_core(task.scope->framebuffer);
                }

                if (task.scope->bindings) {
                    MGLScopeBinding * ptr = task.scope->bindings;

                    for (int i = 0; i < task.scope->num_samplers; ++i) {
                        PyObject * wrapper = SLOT(ptr->sampler->wrapper, PyObject, Sampler_class_texture);
                        MGLTexture * texture = SLOT(wrapper, MGLTexture, Texture_class_mglo);
                        ctx->bind_sampler(ptr->binding, texture->texture_target, texture->texture_obj, ptr->sampler->sampler_obj);
                        ++ptr;
                    }

                    for (int i = 0; i < task.scope->num_uniform_buffers; ++i) {
                        ++ptr;
                    }

                    for (int i = 0; i < task.scope->num_storage_buffers; ++i) {
                        ++ptr;
                    }
                }
                ctx->active_scope = task.scope;
                break;
            }

            case MGL_VAO_SIMPLE_RENDER_TASK: {
                PyObject * program = SLOT(task.vertex_array->wrapper, PyObject, VertexArray_class_program);
                task.vertex_array->context->use_program(SLOT(program, MGLProgram, Program_class_mglo)->program_obj);
                task.vertex_array->context->bind_vertex_array(task.vertex_array->vertex_array_obj);
                task.vertex_array->context->set_write_mask(task.vao_simple_render.color_mask, task.vao_simple_render.depth_mask);

                if (SLOT(task.vertex_array->wrapper, PyObject, VertexArray_class_ibo) != Py_None) {
                    gl.DrawElementsInstanced(task.vao_simple_render.mode, task.vao_simple_render.vertices, GL_UNSIGNED_INT, 0, 1);
                } else {
                    gl.DrawArraysInstanced(task.vao_simple_render.mode, 0, task.vao_simple_render.vertices, 1);
                }
                break;
            }

            case MGL_FBO_SIMPLE_CLEAR_TASK: {
                ctx->bind_framebuffer(task.framebuffer->framebuffer_obj);

                if (task.fbo_simple_clear.attachment < 0) {
                    if (!ctx->current_depth_mask) {
                        gl.DepthMask(true);
                    }
                    gl.ClearBufferfv(GL_DEPTH, 0, (float *)task.fbo_simple_clear.color);
                    if (!ctx->current_depth_mask) {
                        gl.DepthMask(false);
                    }
                } else {
                    const char shape = task.framebuffer->attachment_type[task.fbo_simple_clear.attachment];
                    int old_mask = ctx->current_color_mask >> (task.fbo_simple_clear.attachment * 4) & 0xF;
                    int color_mask = task.fbo_simple_clear.color_mask;
                    if (old_mask != color_mask) {
                        gl.ColorMaski(task.fbo_simple_clear.attachment, color_mask & 1, color_mask & 2, color_mask & 4, color_mask & 8);
                    }
                    switch (shape) {
                        case 'f': gl.ClearBufferfv(GL_COLOR, task.fbo_simple_clear.attachment, (float *)task.fbo_simple_clear.color); break;
                        case 'i': gl.ClearBufferiv(GL_COLOR, task.fbo_simple_clear.attachment, (int *)task.fbo_simple_clear.color); break;
                        case 'u': gl.ClearBufferuiv(GL_COLOR, task.fbo_simple_clear.attachment, (unsigned *)task.fbo_simple_clear.color); break;
                    }
                    if (old_mask != color_mask) {
                        gl.ColorMaski(task.fbo_simple_clear.attachment, old_mask & 1, old_mask & 2, old_mask & 4, old_mask & 8);
                    }
                }
                break;
            }
        }
    }
    Py_RETURN_NONE;
}

#if PY_VERSION_HEX >= 0x03070000

PyMethodDef MGLBatch_methods[] = {
    {"run", (PyCFunction)MGLBatch_meth_run, METH_NOARGS, 0},
    {0},
};

#else

PyMethodDef MGLBatch_methods[] = {
    {"run", (PyCFunction)MGLBatch_meth_run, METH_NOARGS, 0},
    {0},
};

#endif

PyType_Slot MGLBatch_slots[] = {
    {Py_tp_methods, MGLBatch_methods},
    {0},
};

PyType_Spec MGLBatch_spec = {
    mgl_name ".Batch",
    sizeof(MGLBatch),
    0,
    Py_TPFLAGS_DEFAULT,
    MGLBatch_slots,
};
