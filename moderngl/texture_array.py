from typing import Tuple

from .buffer import Buffer

__all__ = ['TextureArray']


class TextureArray:
    '''
        An Array Texture is a Texture where each mipmap level contains an array of
        images of the same size. Array textures may have Mipmaps, but each mipmap
        in the texture has the same number of levels.

        A TextureArray object cannot be instantiated directly, it requires a context.
        Use :py:meth:`Context.texture_array` to create one.
    '''

    __slots__ = ['mglo', '_size', '_components', '_samples', '_dtype', '_depth', '_glo', 'ctx', 'extra']

    def __init__(self):
        self.mglo = None
        self._size = (None, None, None)
        self._components = None
        self._samples = None
        self._dtype = None
        self._depth = None
        self._glo = None
        self.ctx = None
        self.extra = None
        raise TypeError()

    def __repr__(self):
        return '<Texture: %d>' % self.glo

    def __eq__(self, other):
        return type(self) is type(other) and self.mglo is other.mglo

    @property
    def repeat_x(self) -> bool:
        '''
            bool: The repeat_x of the texture.
        '''

        return self.mglo.repeat_x

    @repeat_x.setter
    def repeat_x(self, value):
        self.mglo.repeat_x = value

    @property
    def repeat_y(self) -> bool:
        '''
            bool: The repeat_y of the texture.
        '''

        return self.mglo.repeat_y

    @repeat_y.setter
    def repeat_y(self, value):
        self.mglo.repeat_y = value

    @property
    def filter(self) -> Tuple[int, int]:
        '''
            tuple: The filter of the texture.
        '''

        return self.mglo.filter

    @filter.setter
    def filter(self, value):
        self.mglo.filter = value

    @property
    def swizzle(self) -> str:
        '''
            str: The swizzle of the texture.
        '''

        return self.mglo.swizzle

    @swizzle.setter
    def swizzle(self, value):
        self.mglo.swizzle = value

    @property
    def anisotropy(self) -> float:
        '''
            float: Number of samples for anisotropic filtering.
            Any value greater than 1.0 counts as a use of anisotropic filtering
        '''
        return self.mglo.anisotropy

    @anisotropy.setter
    def anisotropy(self, value):
        self.mglo.anisotropy = value

    @property
    def width(self) -> int:
        '''
            int: The width of the texture array.
        '''

        return self._size[0]

    @property
    def height(self) -> int:
        '''
            int: The height of the texture array.
        '''

        return self._size[1]

    @property
    def layers(self) -> int:
        '''
            int: The number of layers of the texture array.
        '''

        return self._size[2]

    @property
    def size(self) -> tuple:
        '''
            tuple: The size of the texture array.
        '''

        return self._size

    @property
    def components(self) -> int:
        '''
            int: The number of components of the texture array.
        '''

        return self._components

    @property
    def dtype(self) -> str:
        '''
            str: Data type.
        '''

        return self._dtype

    @property
    def glo(self) -> int:
        '''
            int: The internal OpenGL object.
            This values is provided for debug purposes only.
        '''

        return self._glo

    def read(self, *, alignment=1) -> bytes:
        '''
            Read the content of the texture array into a buffer.

            Keyword Args:
                alignment (int): The byte alignment of the pixels.

            Returns:
                bytes
        '''

        return self.mglo.read(alignment)

    def read_into(self, buffer, *, alignment=1, write_offset=0) -> None:
        '''
            Read the content of the texture array into a buffer.

            Args:
                buffer (bytearray): The buffer that will receive the pixels.

            Keyword Args:
                alignment (int): The byte alignment of the pixels.
                write_offset (int): The write offset.
        '''

        if type(buffer) is Buffer:
            buffer = buffer.mglo

        return self.mglo.read_into(buffer, alignment, write_offset)

    def write(self, data, viewport=None, *, alignment=1) -> None:
        '''
            Update the content of the texture array.

            Args:
                data (bytes): The pixel data.
                viewport (tuple): The viewport.

            Keyword Args:
                alignment (int): The byte alignment of the pixels.
        '''

        if type(data) is Buffer:
            data = data.mglo

        self.mglo.write(data, viewport, alignment)

    def build_mipmaps(self, base=0, max_level=1000) -> None:
        '''
            Generate mipmaps.
        '''

        self.mglo.build_mipmaps(base, max_level)

    def use(self, location=0) -> None:
        '''
            Bind the texture array.

            Args:
                location (int): The texture location.
                    Same as the integer value that is used for sampler2D
                    uniforms in the shaders. The value ``0`` will bind the
                    texture to the ``GL_TEXTURE0`` binding point.
        '''

        self.mglo.use(location)

    def release(self) -> None:
        '''
            Release the ModernGL object.
        '''

        self.mglo.release()
