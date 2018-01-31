import re
import os
import unittest

import moderngl


EMPTY_SET = set()


def read_docs(filename):
    root = os.path.dirname(os.path.dirname(__file__))
    f = open(os.path.normpath(os.path.join(root, 'docs', filename)))
    docs = f.read()
    f.close()
    return docs


def detect_members(docs):
    search = re.search(r':members: ([^\n]+)$', docs, re.M)
    return re.split(r', ', search.group(1)) if search else []


def detect_methods(docs):
    return re.findall(r'.. automethod:: ([^\(]+)\(', docs, re.M)


def detect_class(filename, classname):
    lines = read_docs(filename).splitlines()
    start = lines.index('.. autoclass:: ' + classname)
    end = next(i for i in range(start + 1, len(lines)) if not re.match(r'^\s|^$', lines[i]))
    docs = '\n'.join(lines[start:end])
    members = detect_members(docs)
    methods = detect_methods(docs)
    return set(members + methods)


def detect_implementation(classname):
    return set(x for x in dir(getattr(moderngl, classname)) if not x.startswith('_'))


class TestCase(unittest.TestCase):

    def test_context_docs(self):
        documented = detect_class('Context.rst', 'Context')
        implemented = detect_implementation('Context')
        ignored = {'release', 'mglo'}
        self.assertSetEqual(implemented - documented - ignored, EMPTY_SET, msg='Context')
        self.assertSetEqual(documented - implemented, EMPTY_SET, msg='Context')

    def test_buffer_docs(self):
        documented = detect_class('Buffers.rst', 'Buffer')
        implemented = detect_implementation('Buffer')
        ignored = {'release', 'mglo', 'glo'}
        self.assertSetEqual(implemented - documented - ignored, EMPTY_SET, msg='Buffer')
        self.assertSetEqual(documented - implemented, EMPTY_SET, msg='Buffer')

    def test_buffer_access_docs(self):
        documented = detect_class('Buffers.rst', 'BufferAccess')
        implemented = detect_implementation('BufferAccess')
        ignored = {'mglo'}
        self.assertSetEqual(implemented - documented - ignored, EMPTY_SET, msg='BufferAccess')
        self.assertSetEqual(documented - implemented, EMPTY_SET, msg='BufferAccess')

    def test_compute_shader_docs(self):
        documented = detect_class('ComputeShaders.rst', 'ComputeShader')
        implemented = detect_implementation('ComputeShader')
        ignored = {'release', 'mglo', 'glo'}
        self.assertSetEqual(implemented - documented - ignored, EMPTY_SET, msg='ComputeShader')
        self.assertSetEqual(documented - implemented, EMPTY_SET, msg='ComputeShader')

    def test_framebuffer_docs(self):
        documented = detect_class('Framebuffers.rst', 'Framebuffer')
        implemented = detect_implementation('Framebuffer')
        ignored = {'release', 'mglo', 'glo'}
        self.assertSetEqual(implemented - documented - ignored, EMPTY_SET, msg='Framebuffer')
        self.assertSetEqual(documented - implemented, EMPTY_SET, msg='Framebuffer')

    def test_program_docs(self):
        documented = detect_class('ShadersAndPrograms.rst', 'Program')
        implemented = detect_implementation('Program')
        ignored = {'release', 'mglo', 'glo'}
        self.assertSetEqual(implemented - documented - ignored, EMPTY_SET, msg='Program')
        self.assertSetEqual(documented - implemented, EMPTY_SET, msg='Program')

    def test_shader_docs(self):
        documented = detect_class('ShadersAndPrograms.rst', 'Shader')
        implemented = detect_implementation('Shader')
        ignored = {'release', 'mglo', 'glo'}
        self.assertSetEqual(implemented - documented - ignored, EMPTY_SET, msg='Shader')
        self.assertSetEqual(documented - implemented, EMPTY_SET, msg='Shader')

    def test_renderbuffer_docs(self):
        documented = detect_class('Renderbuffers.rst', 'Renderbuffer')
        implemented = detect_implementation('Renderbuffer')
        ignored = {'release', 'mglo', 'glo'}
        self.assertSetEqual(implemented - documented - ignored, EMPTY_SET, msg='Renderbuffer')
        self.assertSetEqual(documented - implemented, EMPTY_SET, msg='Renderbuffer')

    def test_subroutine_docs(self):
        documented = detect_class('Subroutines.rst', 'Subroutine')
        implemented = detect_implementation('Subroutine')
        ignored = {'mglo'}
        self.assertSetEqual(implemented - documented - ignored, EMPTY_SET, msg='Subroutine')
        self.assertSetEqual(documented - implemented, EMPTY_SET, msg='Subroutine')

    def test_texture_docs(self):
        documented = detect_class('Textures.rst', 'Texture')
        implemented = detect_implementation('Texture')
        ignored = {'release', 'mglo', 'glo'}
        self.assertSetEqual(implemented - documented - ignored, EMPTY_SET, msg='Texture')
        self.assertSetEqual(documented - implemented, EMPTY_SET, msg='Texture')

    def test_texture3d_docs(self):
        documented = detect_class('Textures.rst', 'Texture3D')
        implemented = detect_implementation('Texture3D')
        ignored = {'release', 'mglo', 'glo'}
        self.assertSetEqual(implemented - documented - ignored, EMPTY_SET, msg='Texture3D')
        self.assertSetEqual(documented - implemented, EMPTY_SET, msg='Texture3D')

    def test_texture_cube_docs(self):
        documented = detect_class('Textures.rst', 'TextureCube')
        implemented = detect_implementation('TextureCube')
        ignored = {'release', 'mglo', 'glo'}
        self.assertSetEqual(implemented - documented - ignored, EMPTY_SET, msg='TextureCube')
        self.assertSetEqual(documented - implemented, EMPTY_SET, msg='TextureCube')

    def test_uniform_docs(self):
        documented = detect_class('Uniforms.rst', 'Uniform')
        implemented = detect_implementation('Uniform')
        ignored = {'mglo'}
        self.assertSetEqual(implemented - documented - ignored, EMPTY_SET, msg='Uniform')
        self.assertSetEqual(documented - implemented, EMPTY_SET, msg='Uniform')

    def test_uniform_block_docs(self):
        documented = detect_class('UniformBlocks.rst', 'UniformBlock')
        implemented = detect_implementation('UniformBlock')
        ignored = {'mglo'}
        self.assertSetEqual(implemented - documented - ignored, EMPTY_SET, msg='UniformBlock')
        self.assertSetEqual(documented - implemented, EMPTY_SET, msg='UniformBlock')

    def test_varying_docs(self):
        documented = detect_class('Varyings.rst', 'Varying')
        implemented = detect_implementation('Varying')
        ignored = {'mglo'}
        self.assertSetEqual(implemented - documented - ignored, EMPTY_SET, msg='Varying')
        self.assertSetEqual(documented - implemented, EMPTY_SET, msg='Varying')

    def test_vertex_array_docs(self):
        documented = detect_class('VertexArrays.rst', 'VertexArray')
        implemented = detect_implementation('VertexArray')
        ignored = {'release', 'mglo', 'glo'}
        self.assertSetEqual(implemented - documented - ignored, EMPTY_SET, msg='VertexArray')
        self.assertSetEqual(documented - implemented, EMPTY_SET, msg='VertexArray')


if __name__ == '__main__':
    unittest.main()
