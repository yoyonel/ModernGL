'''
    Placeholder
'''

from .common import Object


class Texture(Object):
    '''
        Texture
    '''

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
            width
        '''

        return self.mglo.width

    @property
    def height(self) -> int:
        '''
            height
        '''

        return self.mglo.height

    @property
    def size(self) -> tuple:
        '''
            size
        '''

        return (self.mglo.width, self.mglo.height)

    def update(self, data, size=None, *, offset=(0, 0)):
        '''
            update
        '''

        self.mglo.update(data, size, offset)

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
