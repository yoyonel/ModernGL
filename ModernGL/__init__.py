'''
    ModernGL: PyOpenGL alternative
'''

from .common import (
    InvalidObject, Version, EnableFlag, Primitive, Error,
    POINTS, LINES, LINE_STRIP, LINE_LOOP, TRIANGLES, TRIANGLE_STRIP, TRIANGLE_FAN,
    LINES_ADJACENCY, LINE_STRIP_ADJACENCY, TRIANGLES_ADJACENCY, TRIANGLE_STRIP_ADJACENCY,
    CORE_330, CORE_400, CORE_410, CORE_420, CORE_430, CORE_440, CORE_450,
    BLEND, DEPTH_TEST, CULL_FACE, MULTISAMPLE,
)

from .program_members import (
    Uniform, UniformMap, UniformBlock, UniformBlockMap,
    Varying, VaryingMap, Attribute, AttributeMap,
    Subroutine, SubroutineUniform,
)

from .vertex_arrays import (
    VertexArrayAttribute, VertexArray
)

from .context import Context, create_context, create_standalone_context
from .buffers import Buffer, BufferAccess, detect_format
from .programs import ComputeShader, Shader, Program
from .textures_renderbuffers import Texture, Renderbuffer
from .framebuffers import Framebuffer

__all__ = [
    'InvalidObject', 'Version', 'EnableFlag', 'Primitive', 'Error',
    'POINTS', 'LINES', 'LINE_STRIP', 'LINE_LOOP', 'TRIANGLES', 'TRIANGLE_STRIP', 'TRIANGLE_FAN',
    'LINES_ADJACENCY', 'LINE_STRIP_ADJACENCY', 'TRIANGLES_ADJACENCY', 'TRIANGLE_STRIP_ADJACENCY',
    'CORE_330', 'CORE_400', 'CORE_410', 'CORE_420', 'CORE_430', 'CORE_440', 'CORE_450',
    'BLEND', 'DEPTH_TEST', 'CULL_FACE', 'MULTISAMPLE',
    'Uniform', 'UniformMap', 'UniformBlock', 'UniformBlockMap',
    'Varying', 'VaryingMap', 'Attribute', 'AttributeMap',
    'Subroutine', 'SubroutineUniform',
    'VertexArrayAttribute',
    'VERSION',
    'create_context',
    'create_standalone_context',
    'BufferAccess',
    'Buffer',
    'ComputeShader',
    'Shader',
    'Program',
    'Renderbuffer',
    'Texture',
    'Framebuffer',
    'VertexArray',
    'Context',
    'detect_format',
]

VERSION = '3.1.5'
'''
    ModernGL version
'''
