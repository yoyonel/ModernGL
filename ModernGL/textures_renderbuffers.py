'''
    ModernGL textures and renderbuffers
'''

from .common import InvalidObject


class Texture:
    '''
        Texture
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

    @staticmethod
    def new(obj):
        '''
            For internal use only.
        '''

        res = Texture.__new__(Texture)
        res.mglo = obj
        return res

    @property
    def width(self) -> int:
        '''
            Texture width
        '''

        return self.mglo.width

    @property
    def height(self) -> int:
        '''
            Texture height
        '''

        return self.mglo.height

    @property
    def size(self) -> tuple:
        '''
            Texture size
        '''

        return (self.mglo.width, self.mglo.height)

    @property
    def samples(self) -> int:
        '''
            Texture samples
        '''

        return self.mglo.samples

    @property
    def components(self) -> int:
        '''
            Texture components
        '''

        return self.mglo.components

    @property
    def depth(self) -> bool:
        '''
            Texture depth
        '''

        return self.mglo.depth

    def write(self, data, viewport=None):
        '''
            write
        '''

        self.mglo.write(data, viewport)

    def use(self, location=0):
        '''
            Bind the texture.

            Args:
                location (int): The texture location.
                    Same as the integer value that is used for sampler2D
                    uniforms in the shaders. The value ``0`` will bind the
                    texture to the ``GL_TEXTURE0`` binding point.
        '''

        self.mglo.use(location)


class Renderbuffer:
    '''
        Renderbuffer
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

    @staticmethod
    def new(obj):
        '''
            For internal use only.
        '''

        res = Renderbuffer.__new__(Renderbuffer)
        res.mglo = obj
        return res

    @property
    def width(self) -> int:
        '''
            Renderbuffer width
        '''

        return self.mglo.width

    @property
    def height(self) -> int:
        '''
            Renderbuffer height
        '''

        return self.mglo.height

    @property
    def size(self) -> tuple:
        '''
            Renderbuffer size
        '''

        return (self.mglo.width, self.mglo.height)

    @property
    def samples(self) -> int:
        '''
            Renderbuffer samples
        '''

        return self.mglo.samples

    @property
    def components(self) -> bool:
        '''
            Renderbuffer components
        '''

        return self.mglo.components

    @property
    def depth(self) -> bool:
        '''
            Renderbuffer depth
        '''

        return self.mglo.depth
