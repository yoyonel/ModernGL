'''
    ModernGL buffers
'''

from .common import Object


class BufferAccess:
    '''
        BufferAccess
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
            internal use only
        '''

        res = BufferAccess.__new__(BufferAccess)
        res.mglo = obj
        return res

    def open(self):
        '''
            Map the buffer.
        '''

        self.mglo.open()

    def close(self):
        '''
            Unmap the buffer.
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

    def write(self, data, offset=0):
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


class Buffer(Object):
    '''
        Create a `Buffer` using `Context.buffer`.
    '''

    @staticmethod
    def new(obj):
        '''
            internal use only
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

    def access(self, size=-1, offset=0, readonly=False) -> BufferAccess:
        '''
            Create a buffer access object.

            Keyword Args:
                size: The size.
                offset: The offset.
                readonly: The readonly.
        '''

        return BufferAccess.new(self.mglo.access(size, offset, readonly))

    def read(self, size=-1, offset=0) -> bytes:
        '''
            Read the content.

            Args:
                size: The size. Value `-1` means all.

            Keyword Args:
                offset: The offset.

            Returns:
                bytes: binary data.
        '''

        return self.mglo.read(size, offset)

    def write(self, data, offset=0):
        '''
            Write the content.

            Args:
                data: The data.

            Keyword Args:
                offset: The offset.
        '''

        self.mglo.write(data, offset)

    def orphan(self):
        '''
            Orphan the buffer.
        '''

        self.mglo.orphan()

    def bind_to_uniform_block(self, location=0):
        '''
            Bind the buffer to a uniform block.

            Args:
                location: The uniform block location.
        '''

        self.mglo.bind_to_uniform_block(location)

    def bind_to_storage_buffer(self, location=0):
        '''
            Bind the buffer to a shader storage buffer.

            Args:
                location: The shader storage location.
        '''

        self.mglo.bind_to_storage_buffer(location)


def detect_format(program, attributes) -> str:
    '''
        detect_format
    '''

    def fmt(attr):
        '''
            size and shape
        '''

        return attr.array_length * attr.dimension, attr.shape

    return ''.join('%d%s' % fmt(program.attributes[a]) for a in attributes)
