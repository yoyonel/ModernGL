'''
    ModernGL: PyOpenGL alternative
'''

import os

try:
    from ModernGL.mgl import Error

except ImportError:

    if os.environ.get('READTHEDOCS') == 'True':
        from ModernGL.mock import Error

    else:
        _IMPORT_ERROR = '\n'.join([
            'No implementation found for ModernGL',
            'Are you sure the source code is compiled properly?',
            'Hint: python3 setup.py build_ext -b .',
        ])

        raise ImportError(_IMPORT_ERROR) from None


from ModernGL.common import (
    InvalidObject, Version, EnableFlag, Primitive,
    POINTS, LINES, LINE_STRIP, LINE_LOOP, TRIANGLES, TRIANGLE_STRIP, TRIANGLE_FAN,
    LINES_ADJACENCY, LINE_STRIP_ADJACENCY, TRIANGLES_ADJACENCY, TRIANGLE_STRIP_ADJACENCY,
    CORE_330, CORE_400, CORE_410, CORE_420, CORE_430, CORE_440, CORE_450,
    BLEND, DEPTH_TEST, CULL_FACE, MULTISAMPLE,
)

from ModernGL.members import (
    Uniform, UniformMap, UniformBlock, UniformBlockMap,
    Varying, VaryingMap, Attribute, AttributeMap,
    Subroutine, SubroutineMap, SubroutineUniform, SubroutineUniformMap,
    ProgramStage,
)

from ModernGL.vertex_arrays import (
    VertexArrayAttribute, VertexArray
)

from ModernGL.context import Context, create_context, create_standalone_context
from ModernGL.buffers import Buffer, BufferAccess, detect_format
from ModernGL.programs import ComputeShader, Shader, Program
from ModernGL.textures import Texture
from ModernGL.renderbuffers import Renderbuffer
from ModernGL.framebuffers import Framebuffer

__version__ = '4.1.0'

__all__ = [
    'InvalidObject', 'Version', 'EnableFlag', 'Primitive', 'Error',
    'POINTS', 'LINES', 'LINE_STRIP', 'LINE_LOOP', 'TRIANGLES', 'TRIANGLE_STRIP', 'TRIANGLE_FAN',
    'LINES_ADJACENCY', 'LINE_STRIP_ADJACENCY', 'TRIANGLES_ADJACENCY', 'TRIANGLE_STRIP_ADJACENCY',
    'CORE_330', 'CORE_400', 'CORE_410', 'CORE_420', 'CORE_430', 'CORE_440', 'CORE_450',
    'BLEND', 'DEPTH_TEST', 'CULL_FACE', 'MULTISAMPLE',
    'Subroutine', 'SubroutineMap', 'SubroutineUniform', 'SubroutineUniformMap',
    'Uniform', 'UniformMap', 'UniformBlock', 'UniformBlockMap',
    'Varying', 'VaryingMap', 'Attribute', 'AttributeMap',
    'Program', 'ProgramStage', 'Shader', 'ComputeShader',
    'Texture', 'Framebuffer', 'Renderbuffer',
    'VertexArray', 'VertexArrayAttribute',
    'Buffer', 'BufferAccess',
    'Context',
    'create_context', 'create_standalone_context',
    'detect_format',
]
