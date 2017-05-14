'''
    ModernGL: PyOpenGL alternative
'''

from .errors import Error

from .common import (
    InvalidObject, Object, Version, EnableFlag, Primitive,
    POINTS, LINES, LINE_STRIP, LINE_LOOP, TRIANGLES, TRIANGLE_STRIP, TRIANGLE_FAN,
    LINES_ADJACENCY, LINE_STRIP_ADJACENCY, TRIANGLES_ADJACENCY, TRIANGLE_STRIP_ADJACENCY,
    CORE_330, CORE_400, CORE_410, CORE_420, CORE_430, CORE_440, CORE_450,
    BLEND, DEPTH_TEST, CULL_FACE, MULTISAMPLE,
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
    'InvalidObject', 'Object', 'Version', 'EnableFlag', 'Primitive',
    'POINTS', 'LINES', 'LINE_STRIP', 'LINE_LOOP', 'TRIANGLES', 'TRIANGLE_STRIP', 'TRIANGLE_FAN',
    'LINES_ADJACENCY', 'LINE_STRIP_ADJACENCY', 'TRIANGLES_ADJACENCY', 'TRIANGLE_STRIP_ADJACENCY',
    'CORE_330', 'CORE_400', 'CORE_410', 'CORE_420', 'CORE_430', 'CORE_440', 'CORE_450',
    'BLEND', 'DEPTH_TEST', 'CULL_FACE', 'MULTISAMPLE',
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
