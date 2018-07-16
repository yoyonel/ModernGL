from typing import Tuple

from .buffer import Buffer

__all__ = ['Texture',
           'NEAREST', 'LINEAR', 'NEAREST_MIPMAP_NEAREST', 'LINEAR_MIPMAP_NEAREST', 'NEAREST_MIPMAP_LINEAR',
           'LINEAR_MIPMAP_LINEAR']


NEAREST = 0x2600
LINEAR = 0x2601
NEAREST_MIPMAP_NEAREST = 0x2700
LINEAR_MIPMAP_NEAREST = 0x2701
NEAREST_MIPMAP_LINEAR = 0x2702
LINEAR_MIPMAP_LINEAR = 0x2703


class Texture:
    '''
        A Texture is an OpenGL object that contains one or more images that all
        have the same image format. A texture can be used in two ways. It can
        be the source of a texture access from a Shader, or it can be used
        as a render target.

        A Texture object cannot be instantiated directly, it requires a context.
        Use :py:meth:`Context.texture` or :py:meth:`Context.depth_texture`
        to create one.
    '''

    __slots__ = ['mglo', '_size', '_components', '_samples', '_dtype', '_depth', '_glo', 'ctx', 'extra']

    def __init__(self):
        self.mglo = None
        self._size = (None, None)
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
    def compare_func(self) -> str:
        '''
            tuple: The compare function of the depth texture.
        '''

        return self.mglo.compare_func

    @compare_func.setter
    def compare_func(self, value):
        self.mglo.compare_func = value

    @property
    def width(self) -> int:
        '''
            int: The width of the texture.
        '''

        return self._size[0]

    @property
    def height(self) -> int:
        '''
            int: The height of the texture.
        '''

        return self._size[1]

    @property
    def size(self) -> tuple:
        '''
            tuple: The size of the texture.
        '''

        return self._size

    @property
    def components(self) -> int:
        '''
            int: The number of components of the texture.
        '''

        return self._components

    @property
    def samples(self) -> int:
        '''
            int: The number of samples of the texture.
        '''

        return self._samples

    @property
    def dtype(self) -> str:
        '''
            str: Data type.
        '''

        return self._dtype

    @property
    def depth(self) -> bool:
        '''
            bool: Is the texture a depth texture?
        '''

        return self._depth

    @property
    def glo(self) -> int:
        '''
            int: The internal OpenGL object.
            This values is provided for debug purposes only.
        '''

        return self._glo

    def read(self, *, level=0, alignment=1) -> bytes:
        '''
            Read the content of the texture into a buffer.

            Keyword Args:
                level (int): The mipmap level.
                alignment (int): The byte alignment of the pixels.

            Returns:
                bytes
        '''

        return self.mglo.read(level, alignment)

    def read_into(self, buffer, *, level=0, alignment=1, write_offset=0) -> None:
        '''
            Read the content of the texture into a buffer.

            Args:
                buffer (bytearray): The buffer that will receive the pixels.

            Keyword Args:
                level (int): The mipmap level.
                alignment (int): The byte alignment of the pixels.
                write_offset (int): The write offset.
        '''

        if type(buffer) is Buffer:
            buffer = buffer.mglo

        return self.mglo.read_into(buffer, level, alignment, write_offset)

    def write(self, data, viewport=None, *, level=0, alignment=1) -> None:
        '''
            Update the content of the texture.

            Args:
                data (bytes): The pixel data.
                viewport (tuple): The viewport.

            Keyword Args:
                level (int): The mipmap level.
                alignment (int): The byte alignment of the pixels.
        '''

        if type(data) is Buffer:
            data = data.mglo

        self.mglo.write(data, viewport, level, alignment)

    def build_mipmaps(self, base=0, max_level=1000) -> None:
        '''
            Generate mipmaps.
        '''

        self.mglo.build_mipmaps(base, max_level)

    def use(self, location=0) -> None:
        '''
            Bind the texture.

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
