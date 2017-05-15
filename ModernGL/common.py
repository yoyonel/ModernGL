'''
    ModernGL Common
'''

# from ModernGL import ModernGL as _mgl
import importlib; _mgl = importlib.import_module('ModernGL', 'ModernGL')

# pylint: disable=too-few-public-methods, using-constant-test


if False:
    _mgl.BLEND = 'BLEND'
    _mgl.DEPTH_TEST = 'DEPTH_TEST'
    _mgl.CULL_FACE = 'CULL_FACE'
    _mgl.MULTISAMPLE = 'MULTISAMPLE'

    _mgl.TRIANGLES = 'TRIANGLES'
    _mgl.TRIANGLE_STRIP = 'TRIANGLE_STRIP'
    _mgl.TRIANGLE_FAN = 'TRIANGLE_FAN'
    _mgl.LINES = 'LINES'
    _mgl.LINE_STRIP = 'LINE_STRIP'
    _mgl.LINE_LOOP = 'LINE_LOOP'
    _mgl.POINTS = 'POINTS'
    _mgl.LINE_STRIP_ADJACENCY = 'LINE_STRIP_ADJACENCY'
    _mgl.LINES_ADJACENCY = 'LINES_ADJACENCY'
    _mgl.TRIANGLE_STRIP_ADJACENCY = 'TRIANGLE_STRIP_ADJACENCY'
    _mgl.TRIANGLES_ADJACENCY = 'TRIANGLES_ADJACENCY'


class InvalidObject:
    '''
        A ModernGL object turns into an InvalidObject
        once the release method is successfully called.
    '''


class Object:
    '''
        Placeholder Object
    '''

    def __init__(self):
        self.mglo = None
        raise NotImplementedError()

    def release(self):
        '''
            Release the ModernGL object.
        '''

        self.mglo.release()
        self.__class__ = InvalidObject


class EnableFlag:
    '''
        EnableFlag
    '''

    def __init__(self):
        self.mglo = None
        raise NotImplementedError('EnableFlag')

    @staticmethod
    def new(obj):
        '''
            internal use only
        '''

        res = EnableFlag.__new__(EnableFlag)
        res.mglo = obj
        return res


BLEND = _mgl.BLEND
'''
    GL_BLEND
'''

DEPTH_TEST = _mgl.DEPTH_TEST
'''
    GL_DEPTH_TEST
'''

CULL_FACE = _mgl.CULL_FACE
'''
    GL_CULL_FACE
'''

MULTISAMPLE = _mgl.MULTISAMPLE
'''
    GL_MULTISAMPLE
'''


class Primitive:
    '''
        Primitive
    '''

    def __init__(self):
        self.mglo = None
        raise NotImplementedError('Primitive')

    @staticmethod
    def new(obj):
        '''
            internal use only
        '''

        res = Primitive.__new__(Primitive)
        res.mglo = obj
        return res


TRIANGLES = _mgl.TRIANGLES
'''
    GL_TRIANGLES
'''

TRIANGLE_STRIP = _mgl.TRIANGLE_STRIP
'''
    GL_TRIANGLE_STRIP
'''

TRIANGLE_FAN = _mgl.TRIANGLE_FAN
'''
    GL_TRIANGLE_FAN
'''

LINES = _mgl.LINES
'''
    GL_LINES
'''

LINE_STRIP = _mgl.LINE_STRIP
'''
    GL_LINE_STRIP
'''

LINE_LOOP = _mgl.LINE_LOOP
'''
    GL_LINE_LOOP
'''

POINTS = _mgl.POINTS
'''
    GL_POINTS
'''

LINE_STRIP_ADJACENCY = _mgl.LINE_STRIP_ADJACENCY
'''
    GL_LINE_STRIP_ADJACENCY
'''

LINES_ADJACENCY = _mgl.LINES_ADJACENCY
'''
    GL_LINES_ADJACENCY
'''

TRIANGLE_STRIP_ADJACENCY = _mgl.TRIANGLE_STRIP_ADJACENCY
'''
    GL_TRIANGLE_STRIP_ADJACENCY
'''

TRIANGLES_ADJACENCY = _mgl.TRIANGLES_ADJACENCY
'''
    GL_TRIANGLES_ADJACENCY
'''


class Version:
    '''
        Version
    '''

    def __init__(self, major, minor):
        self.major = major
        self.minor = minor


CORE_330 = Version(3, 3)
'''
    OpenGL 3.3
'''

CORE_400 = Version(4, 0)
'''
    OpenGL 4.0
'''

CORE_410 = Version(4, 1)
'''
    OpenGL 4.1
'''

CORE_420 = Version(4, 2)
'''
    OpenGL 4.2
'''

CORE_430 = Version(4, 3)
'''
    OpenGL 4.3
'''

CORE_440 = Version(4, 4)
'''
    OpenGL 4.4
'''

CORE_450 = Version(4, 5)
'''
    OpenGL 4.5
'''
