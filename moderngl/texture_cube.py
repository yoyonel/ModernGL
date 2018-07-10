from .buffer import Buffer

__all__ = ['TextureCube']


class TextureCube:
    '''
        A Texture is an OpenGL object that contains one or more images that all
        have the same image format. A texture can be used in two ways. It can
        be the source of a texture access from a Shader, or it can be used
        as a render target.

        A Texture3D object cannot be instantiated directly, it requires a context.
        Use :py:meth:`Context.texture_cube` to create one.
    '''

    __slots__ = ['mglo', '_size', '_components', '_dtype', '_glo', 'ctx', 'extra']

    def __init__(self):
        self.mglo = None
        self._size = (None, None)
        self._components = None
        self._dtype = None
        self._glo = None
        self.ctx = None
        self.extra = None
        raise TypeError()

    def __repr__(self):
        return '<TextureCube: %d>' % self.glo

    def __eq__(self, other):
        return type(self) is type(other) and self.mglo is other.mglo

    @property
    def glo(self) -> int:
        '''
            int: The internal OpenGL object.
            This values is provided for debug purposes only.
        '''

        return self._glo

    def read(self, face, *, alignment=1) -> bytes:
        '''
            Read a face from the cubemap texture.

            Args:
                face (int): The face to read.

            Keyword Args:
                alignment (int): The byte alignment of the pixels.
        '''

        return self.mglo.read(face, alignment)

    def read_into(self, buffer, face, *, alignment=1, write_offset=0) -> None:
        '''
            Read a face from the cubemap texture.

            Args:
                buffer (bytearray): The buffer that will receive the pixels.
                face (int): The face to read.

            Keyword Args:
                alignment (int): The byte alignment of the pixels.
                write_offset (int): The write offset.
        '''

        if type(buffer) is Buffer:
            buffer = buffer.mglo

        return self.mglo.read_into(buffer, face, alignment, write_offset)

    def write(self, face, data, viewport=None, *, alignment=1) -> None:
        '''
            Update the content of the texture.

            Args:
                face (int): The face to update.
                data (bytes): The pixel data.
                viewport (tuple): The viewport.

            Keyword Args:
                alignment (int): The byte alignment of the pixels.
        '''

        if type(data) is Buffer:
            data = data.mglo

        self.mglo.write(face, data, viewport, alignment)

    def use(self, location=0) -> None:
        '''
            Bind the cubemap texture.

            Args:
                location (int): The texture location.
                    Same as the integer value that is used for sampler3D
                    uniforms in the shaders. The value ``0`` will bind the
                    texture to the ``GL_TEXTURE0`` binding point.
        '''

        self.mglo.use(location)

    def release(self) -> None:
        '''
            Release the ModernGL object.
        '''

        self.mglo.release()
