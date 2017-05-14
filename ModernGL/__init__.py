'''
    ModernGL: PyOpenGL alternative
'''

# pylint: disable=too-many-public-methods

from .errors import Error

from .common import (
    Object, InvalidObject, Version, EnableFlag, Primitive,
    CORE_330, CORE_400, CORE_410, CORE_420, CORE_430, CORE_440, CORE_450,
    BLEND, DEPTH_TEST, CULL_FACE, MULTISAMPLE,
    TRIANGLES, TRIANGLE_STRIP, TRIANGLE_FAN, LINES, LINE_STRIP, LINE_LOOP, POINTS,
    LINE_STRIP_ADJACENCY, LINES_ADJACENCY, TRIANGLE_STRIP_ADJACENCY, TRIANGLES_ADJACENCY,
)

from .program_members import (
    Uniform, UniformMap, UniformBlock, Varying, Attribute, AttributeMap,
    Subroutine, SubroutineUniform,
)

from .vertex_arrays import (
    VertexArrayAttribute, VertexArrayListAttribute, VertexArrayMatrixAttribute, VertexArray
)

from .context import Context, create_context, create_standalone_context
from .buffers import Buffer, BufferAccess, detect_format
from .programs import ComputeShader, Shader, Program
from .renderbuffers import Renderbuffer
from .textures import Texture

__all__ = [
    'Version', 'EnableFlag', 'Primitive',
    'CORE_330', 'CORE_400', 'CORE_410', 'CORE_420', 'CORE_430', 'CORE_440', 'CORE_450',
    'BLEND', 'DEPTH_TEST', 'CULL_FACE', 'MULTISAMPLE',
    'TRIANGLES', 'TRIANGLE_STRIP', 'TRIANGLE_FAN', 'LINES', 'LINE_STRIP', 'LINE_LOOP', 'POINTS',
    'LINE_STRIP_ADJACENCY', 'LINES_ADJACENCY', 'TRIANGLE_STRIP_ADJACENCY', 'TRIANGLES_ADJACENCY',
    'Uniform', 'UniformMap', 'UniformBlock',
    'Varying', 'Attribute', 'AttributeMap',
    'Subroutine', 'SubroutineUniform',
    'VertexArrayAttribute', 'VertexArrayListAttribute', 'VertexArrayMatrixAttribute',
    'Object', 'InvalidObject', 'Error',
    'VERSION',
    'create_context',
    'create_standalone_context',
    'BufferAccess',
    'Buffer',
    'ComputeShader',
    'Framebuffer',
    'Shader',
    'Program',
    'Renderbuffer',
    'Texture',
    'VertexArray',
    'Context',
    'detect_format',
]

VERSION = '3.1.5'
'''
    ModernGL version
'''
