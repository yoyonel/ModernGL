#include "Framebuffer.hpp"

#include "Error.hpp"
#include "InvalidObject.hpp"
#include "Renderbuffer.hpp"
#include "Texture.hpp"

PyObject * MGLFramebuffer_tp_new(PyTypeObject * type, PyObject * args, PyObject * kwargs) {
	MGLFramebuffer * self = (MGLFramebuffer *)type->tp_alloc(type, 0);

	#ifdef MGL_VERBOSE
	printf("MGLFramebuffer_tp_new %p\n", self);
	#endif

	if (self) {
		self->color_attachments = 0;
		self->depth_attachment = 0;
	}

	return (PyObject *)self;
}

void MGLFramebuffer_tp_dealloc(MGLFramebuffer * self) {

	#ifdef MGL_VERBOSE
	printf("MGLFramebuffer_tp_dealloc %p\n", self);
	#endif

	MGLFramebuffer_Type.tp_free((PyObject *)self);
}

int MGLFramebuffer_tp_init(MGLFramebuffer * self, PyObject * args, PyObject * kwargs) {
	return -1;
}

PyObject * MGLFramebuffer_tp_str(MGLFramebuffer * self) {
	return PyUnicode_FromFormat("<ModernGL.Framebuffer>");
}

PyObject * MGLFramebuffer_release(MGLFramebuffer * self) {
	MGLFramebuffer_Invalidate(self);
	Py_RETURN_NONE;
}

PyObject * MGLFramebuffer_use(MGLFramebuffer * self) {
	self->context->gl.BindFramebuffer(GL_FRAMEBUFFER, self->obj);
	Py_RETURN_NONE;
}

const char * MGLFramebuffer_use_doc = R"(
	use()
)";

PyMethodDef MGLFramebuffer_tp_methods[] = {
	{"release", (PyCFunction)MGLFramebuffer_release, METH_NOARGS, 0},
	{"use", (PyCFunction)MGLFramebuffer_use, METH_NOARGS, 0},
	{0},
};

PyGetSetDef MGLFramebuffer_tp_getseters[] = {
	{0},
};

const char * MGLFramebuffer_tp_doc = R"(
	Framebuffer
)";

PyTypeObject MGLFramebuffer_Type = {
	PyVarObject_HEAD_INIT(0, 0)
	"ModernGL.Framebuffer",                                 // tp_name
	sizeof(MGLFramebuffer),                                 // tp_basicsize
	0,                                                      // tp_itemsize
	(destructor)MGLFramebuffer_tp_dealloc,                  // tp_dealloc
	0,                                                      // tp_print
	0,                                                      // tp_getattr
	0,                                                      // tp_setattr
	0,                                                      // tp_reserved
	(reprfunc)MGLFramebuffer_tp_str,                        // tp_repr
	0,                                                      // tp_as_number
	0,                                                      // tp_as_sequence
	0,                                                      // tp_as_mapping
	0,                                                      // tp_hash
	0,                                                      // tp_call
	(reprfunc)MGLFramebuffer_tp_str,                        // tp_str
	0,                                                      // tp_getattro
	0,                                                      // tp_setattro
	0,                                                      // tp_as_buffer
	Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,               // tp_flags
	MGLFramebuffer_tp_doc,                                  // tp_doc
	0,                                                      // tp_traverse
	0,                                                      // tp_clear
	0,                                                      // tp_richcompare
	0,                                                      // tp_weaklistoffset
	0,                                                      // tp_iter
	0,                                                      // tp_iternext
	MGLFramebuffer_tp_methods,                              // tp_methods
	0,                                                      // tp_members
	MGLFramebuffer_tp_getseters,                            // tp_getset
	&MGLContextMember_Type,                                 // tp_base
	0,                                                      // tp_dict
	0,                                                      // tp_descr_get
	0,                                                      // tp_descr_set
	0,                                                      // tp_dictoffset
	(initproc)MGLFramebuffer_tp_init,                       // tp_init
	0,                                                      // tp_alloc
	MGLFramebuffer_tp_new,                                  // tp_new
};

MGLFramebuffer * MGLFramebuffer_New() {
	MGLFramebuffer * self = (MGLFramebuffer *)MGLFramebuffer_tp_new(&MGLFramebuffer_Type, 0, 0);
	return self;
}

void MGLFramebuffer_Invalidate(MGLFramebuffer * framebuffer) {
	if (Py_TYPE(framebuffer) == &MGLInvalidObject_Type) {

		#ifdef MGL_VERBOSE
		printf("MGLFramebuffer_Invalidate %p already released\n", framebuffer);
		#endif

		return;
	}

	#ifdef MGL_VERBOSE
	printf("MGLFramebuffer_Invalidate %p\n", framebuffer);
	#endif

	framebuffer->context->gl.DeleteFramebuffers(1, (GLuint *)&framebuffer->obj);

	int color_attachments_len = PyList_GET_SIZE(framebuffer->color_attachments);

	for (int i = 0; i < color_attachments_len; ++i) {
		PyObject * attachment = PyList_GET_ITEM(framebuffer->color_attachments, i);

		if (Py_TYPE(attachment) == &MGLTexture_Type) {
			MGLTexture * texture = (MGLTexture *)attachment;
			if (Py_REFCNT(texture) == 2) {
				MGLTexture_Invalidate(texture);
			}
		} else {
			// TODO:
			printf("Unknown trace in %s (%s:%d)\n", __FUNCTION__, __FILE__, __LINE__);
		}
	}

	Py_DECREF(framebuffer->color_attachments);

	if (Py_TYPE(framebuffer->depth_attachment) == &MGLTexture_Type) {
		MGLTexture * texture = (MGLTexture *)framebuffer->depth_attachment;
		if (Py_REFCNT(texture) == 2) {
			MGLTexture_Invalidate(texture);
		}
	} else {
		// TODO:
		printf("Unknown trace in %s (%s:%d)\n", __FUNCTION__, __FILE__, __LINE__);
	}

	Py_DECREF(framebuffer->depth_attachment);

	Py_DECREF(framebuffer->context);

	framebuffer->ob_base.ob_type = &MGLInvalidObject_Type;
	framebuffer->initial_type = &MGLFramebuffer_Type;

	Py_DECREF(framebuffer);
}
