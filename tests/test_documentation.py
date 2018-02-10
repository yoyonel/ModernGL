import re
import os
import unittest

import moderngl


EMPTY_SET = set()


def read_docs(filename, classname):
    root = os.path.dirname(os.path.dirname(__file__))
    with open(os.path.normpath(os.path.join(root, 'docs', 'reference', filename))) as f:
        docs = f.read()
    # classes = re.findall(r'^\.\. autoclass:: ([^\(\n]+)', docs, flags=re.M)
    methods = re.findall(r'^\.\. automethod:: ([^\(\n]+)', docs, flags=re.M)
    attributes = re.findall(r'^\.\. autoattribute:: ([^\(\n]+)', docs, flags=re.M)
    res = filter(lambda x: x.startswith(classname), methods + attributes)
    return set(res)



def detect_impl(classname):
    return set(classname + '.' + x for x in dir(getattr(moderngl, classname)) if not x.startswith('_'))


class TestCase(unittest.TestCase):

    def validate(self, filename, classname, ignore):
        documented = read_docs(filename, classname)
        implemented = detect_impl(classname)
        ignored = set(classname + '.' + x for x in ignore)
        self.assertSetEqual(implemented - documented - ignored, EMPTY_SET, msg='Implemented but not Documented')
        self.assertSetEqual(documented - implemented, EMPTY_SET, msg='Documented but not Implemented')

    def test_context_docs(self):
        self.validate('context.rst', 'Context', ['release', 'mglo', 'extra'])

    def test_buffer_docs(self):
        self.validate('buffer.rst', 'Buffer', ['release', 'mglo', 'glo', 'extra'])

    def test_compute_shader_docs(self):
        self.validate('compute_shader.rst', 'ComputeShader', ['release', 'mglo', 'glo', 'extra'])

    def test_framebuffer_docs(self):
        self.validate('framebuffer.rst', 'Framebuffer', ['release', 'mglo', 'glo', 'extra'])

    def test_program_docs(self):
        self.validate('program.rst', 'Program', ['release', 'mglo', 'glo', 'extra'])

    def test_renderbuffer_docs(self):
        self.validate('renderbuffer.rst', 'Renderbuffer', ['release', 'mglo', 'glo', 'extra'])

    def test_subroutine_docs(self):
        self.validate('subroutine.rst', 'Subroutine', ['mglo', 'extra'])

    def test_texture_docs(self):
        self.validate('texture.rst', 'Texture', ['release', 'mglo', 'glo', 'extra'])

    def test_texture3d_docs(self):
        self.validate('texture3d.rst', 'Texture3D', ['release', 'mglo', 'glo', 'extra'])

    def test_texture_cube_docs(self):
        self.validate('texture_cube.rst', 'TextureCube', ['release', 'mglo', 'glo', 'extra'])

    def test_uniform_docs(self):
        self.validate('uniform.rst', 'Uniform', ['mglo', 'extra'])

    def test_uniform_block_docs(self):
        self.validate('uniform_block.rst', 'UniformBlock', ['mglo', 'extra'])

    def test_varying_docs(self):
        self.validate('varying.rst', 'Varying', ['mglo', 'extra'])

    def test_vertex_array_docs(self):
        self.validate('vertex_array.rst', 'VertexArray', ['release', 'mglo', 'glo', 'extra'])


if __name__ == '__main__':
    unittest.main()
