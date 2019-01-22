#include "batch.hpp"
#include "context.hpp"
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
        PyObject * item = PySequence_Fast(PySequence_Fast_GET_ITEM(seq, i), "");
        int num_params = (int)PySequence_Fast_GET_SIZE(item);
        int task = PyLong_AsLong(PySequence_Fast_GET_ITEM(item, 0));
        PyObject * wrapper = PySequence_Fast_GET_ITEM(item, 1);
        if (wrapper->ob_type != VertexArray_class) {
            return 0;
        }
        batch->tasks[i].task = task;
        batch->tasks[i].vertex_array = SLOT(wrapper, MGLVertexArray, VertexArray_class_mglo);

        switch (task) {
            case MGL_RENDER_TASK:
                batch->tasks[i].render_args.mode = PyLong_AsLong(PySequence_Fast_GET_ITEM(item, 2));
                batch->tasks[i].render_args.vertices = PyLong_AsLong(PySequence_Fast_GET_ITEM(item, 3));
                batch->tasks[i].render_args.first = PyLong_AsLong(PySequence_Fast_GET_ITEM(item, 4));
                batch->tasks[i].render_args.instances = PyLong_AsLong(PySequence_Fast_GET_ITEM(item, 5));
                batch->tasks[i].render_args.color_mask = PyLong_AsUnsignedLongLong(PySequence_Fast_GET_ITEM(item, 6));
                batch->tasks[i].render_args.depth_mask = (bool)PyObject_IsTrue(PySequence_Fast_GET_ITEM(item, 7));
                break;
        }

        Py_DECREF(item);
    }
    Py_DECREF(seq);

    return NEW_REF(batch->wrapper);
}

/* MGLBatch.run()
 */
PyObject * MGLBatch_meth_run(MGLBatch * self) {
    for (int i = 0; i < self->num_tasks; ++i) {
        const MGLBatchTask & task = self->tasks[i];
        switch (task.task) {
            case MGL_RENDER_TASK:
                MGLVertexArray_render_core(task.vertex_array, task.render_args.mode, task.render_args.vertices, task.render_args.first, task.render_args.instances, task.render_args.color_mask, task.render_args.depth_mask);
                break;
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
