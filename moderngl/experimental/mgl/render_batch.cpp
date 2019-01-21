#include "render_batch.hpp"
#include "context.hpp"
#include "vertex_array.hpp"

#include "internal/wrapper.hpp"

#include "internal/modules.hpp"
#include "internal/tools.hpp"

/* MGLContext.render_batch()
 */
PyObject * MGLContext_meth_render_batch(MGLContext * self, PyObject * const * args, Py_ssize_t nargs) {
    if (nargs != 1) {
        // TODO: error
        return 0;
    }

    PyObject * seq = PySequence_Fast(args[0], "not iterable");
    if (!seq) {
        return 0;
    }

    MGLRenderBatch * render_batch = MGLContext_new_object(self, RenderBatch);

    int num_tasks = (int)PySequence_Fast_GET_SIZE(seq);
    render_batch->tasks = (MGLRenderBatchTask *)malloc(sizeof(MGLRenderBatchTask) * num_tasks);
    render_batch->num_tasks = num_tasks;

    for (int i = 0; i < num_tasks; ++i) {
        PyObject * item = PySequence_Fast(PySequence_Fast_GET_ITEM(seq, i), "");
        int num_params = (int)PySequence_Fast_GET_SIZE(item);
        int task = PyLong_AsLong(PySequence_Fast_GET_ITEM(item, 0));
        PyObject * wrapper = PySequence_Fast_GET_ITEM(item, 1);
        if (wrapper->ob_type != VertexArray_class) {
            return 0;
        }
        render_batch->tasks[i].task = task;
        render_batch->tasks[i].vertex_array = SLOT(wrapper, MGLVertexArray, VertexArray_class_mglo);

        switch (task) {
            case MGL_RENDER_TASK:
                render_batch->tasks[i].render_args.mode = PyLong_AsLong(PySequence_Fast_GET_ITEM(item, 2));
                render_batch->tasks[i].render_args.vertices = PyLong_AsLong(PySequence_Fast_GET_ITEM(item, 3));
                render_batch->tasks[i].render_args.first = PyLong_AsLong(PySequence_Fast_GET_ITEM(item, 4));
                render_batch->tasks[i].render_args.instances = PyLong_AsLong(PySequence_Fast_GET_ITEM(item, 5));
                render_batch->tasks[i].render_args.color_mask = PyLong_AsUnsignedLongLong(PySequence_Fast_GET_ITEM(item, 6));
                render_batch->tasks[i].render_args.depth_mask = (bool)PyObject_IsTrue(PySequence_Fast_GET_ITEM(item, 7));
                break;
        }

        Py_DECREF(item);
    }
    Py_DECREF(seq);

    return NEW_REF(render_batch->wrapper);
}

/* MGLRenderBatch.run()
 */
PyObject * MGLRenderBatch_meth_run(MGLRenderBatch * self) {
    for (int i = 0; i < self->num_tasks; ++i) {
        const MGLRenderBatchTask & task = self->tasks[i];
        switch (task.task) {
            case MGL_RENDER_TASK:
                MGLVertexArray_render_core(task.vertex_array, task.render_args.mode, task.render_args.vertices, task.render_args.first, task.render_args.instances, task.render_args.color_mask, task.render_args.depth_mask);
                break;
        }
    }
    Py_RETURN_NONE;
}

#if PY_VERSION_HEX >= 0x03070000

PyMethodDef MGLRenderBatch_methods[] = {
    {"run", (PyCFunction)MGLRenderBatch_meth_run, METH_NOARGS, 0},
    {0},
};

#else

PyMethodDef MGLRenderBatch_methods[] = {
    {"run", (PyCFunction)MGLRenderBatch_meth_run, METH_NOARGS, 0},
    {0},
};

#endif

PyType_Slot MGLRenderBatch_slots[] = {
    {Py_tp_methods, MGLRenderBatch_methods},
    {0},
};

PyType_Spec MGLRenderBatch_spec = {
    mgl_name ".RenderBatch",
    sizeof(MGLRenderBatch),
    0,
    Py_TPFLAGS_DEFAULT,
    MGLRenderBatch_slots,
};
