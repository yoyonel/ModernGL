#include "gl_context.hpp"
#include "../modules.hpp"

bool GLContext::load(bool standalone) {
    this->standalone = standalone;

    if (standalone) {
    }

    this->window = 0;
    this->display = 0;
    this->context = 0;

    PyErr_Format(moderngl_error, "android is not yet supported");
    return false;
}

void GLContext::enter() {
}

void GLContext::exit() {
}

bool GLContext::active() {
}
