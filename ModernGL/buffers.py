'''
    ModernGL buffers
'''

from .common import InvalidObject


class BufferAccess:
    '''
        :py:class:`BufferAccess` objects are designed to access
        a :py:class:`Buffer`'s content inside a ``with`` statement.
        The buffer is mapped and unmapped only once.

        example::

            with vbo.access(...) as access:
                access.read(...)
                access.write(...)
    '''

    def __init__(self):
        self.mglo = None
        raise NotImplementedError('BufferAccess')

    def __enter__(self):
        self.mglo.open()
        return self

    def __exit__(self, *args):
        self.mglo.close()

    @staticmethod
    def new(obj):
        '''
            For internal use only.
        '''

        res = BufferAccess.__new__(BufferAccess)
        res.mglo = obj
        return res

    def open(self) -> None:
        '''
            Map the buffer.
            This method is called once ``__enter__`` is called.
        '''

        self.mglo.open()

    def close(self) -> None:
        '''
            Unmap the buffer.
            This method is called once ``__exit__`` is called.
        '''

        self.mglo.close()

    def read(self, size=-1, offset=0) -> bytes:
        '''
            Read the content.

            Args:
                size: The size. Value `-1` means all.

            Keyword Args:
                offset: The offset.

            Returns:
                bytes: binary data
        '''

        return self.mglo.read(size, offset)

    def write(self, data, offset=0) -> None:
        '''
            Write the content.

            Args:
                size: The data.

            Keyword Args:
                offset: The offset.
        '''

        self.mglo.write(data, offset)

    @property
    def offset(self) -> int:
        '''
            The offset.
        '''

        return self.mglo.offset

    @property
    def size(self) -> int:
        '''
            The size.
        '''

        return self.mglo.size

    @property
    def readonly(self) -> bool:
        '''
            Is readonly.
        '''

        return self.mglo.readonly


class Buffer:
    '''
        Create a :py:class:`Buffer` using :py:meth:`Context.buffer`.
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

        res = Buffer.__new__(Buffer)
        res.mglo = obj
        return res

    @property
    def size(self) -> int:
        '''
            The size of the buffer.
        '''

        return self.mglo.size

    @property
    def dynamic(self) -> bool:
        '''
            Is the buffer created with the dynamic flag?
        '''

        return self.mglo.dynamic

    def access(self, *, size=-1, offset=0, readonly=False) -> BufferAccess:
        '''
            Create a :py:class:`BufferAccess` object.

            Keyword Args:
                size (int): The size. Value `-1` means all.
                offset (int): The offset.
                readonly (bool): The readonly.
        '''

        return BufferAccess.new(self.mglo.access(size, offset, readonly))

    def read(self, size=-1, *, offset=0) -> bytes:
        '''
            Read the content.

            Args:
                size (int): The size. Value ``-1`` means all.

            Keyword Args:
                offset (int): The offset.

            Returns:
                bytes: binary data.
        '''

        return self.mglo.read(size, offset)

    def write(self, data, offset=0) -> None:
        '''
            Write the content.

            Args:
                data: The data.

            Keyword Args:
                offset: The offset.
        '''

        self.mglo.write(data, offset)

    def orphan(self) -> None:
        '''
            Orphan the buffer.
        '''

        self.mglo.orphan()

    def bind_to_uniform_block(self, location=0) -> None:
        '''
            Bind the buffer to a uniform block.

            Args:
                location: The uniform block location.
        '''

        self.mglo.bind_to_uniform_block(location)

    def bind_to_storage_buffer(self, location=0) -> None:
        '''
            Bind the buffer to a shader storage buffer.

            Args:
                location: The shader storage location.
        '''

        self.mglo.bind_to_storage_buffer(location)


def detect_format(program, attributes) -> str:
    '''
        Detect format for vertex attributes.
        The format returned does not contain padding.
    '''

    def fmt(attr):
        '''
            For internal use only.
        '''

        return attr.array_length * attr.dimension, attr.shape

    return ''.join('%d%s' % fmt(program.attributes[a]) for a in attributes)
