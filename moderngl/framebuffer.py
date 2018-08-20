from typing import Dict, Tuple, Union

from .buffer import Buffer
from .renderbuffer import Renderbuffer
from .texture import Texture

__all__ = ['Framebuffer']


class Framebuffer:
    '''
        A :py:class:`Framebuffer` is a collection of buffers that can be used as the destination for rendering.
        The buffers for Framebuffer objects reference images from either Textures or Renderbuffers.

        Create a :py:class:`Framebuffer` using :py:meth:`Context.framebuffer`.
    '''

    __slots__ = ['mglo', '_color_attachments', '_depth_attachment', '_size', '_samples', '_glo', 'ctx', 'extra']

    def __init__(self):
        self.mglo = None
        self._color_attachments = None
        self._depth_attachment = None
        self._size = (None, None)
        self._samples = None
        self._glo = None
        self.ctx = None
        self.extra = None
        raise TypeError()

    def __repr__(self):
        return '<Framebuffer: %d>' % self.glo

    def __eq__(self, other):
        return type(self) is type(other) and self.mglo is other.mglo

    @property
    def viewport(self) -> Tuple[int, int, int, int]:
        '''
            tuple: The viewport of the framebuffer.
        '''

        return self.mglo.viewport

    @viewport.setter
    def viewport(self, value):
        self.mglo.viewport = tuple(value)

    @property
    def color_mask(self) -> Tuple[bool, bool, bool, bool]:
        '''
            tuple: The color mask of the framebuffer.
        '''

        return self.mglo.color_mask

    @color_mask.setter
    def color_mask(self, value):
        self.mglo.color_mask = value

    @property
    def depth_mask(self) -> bool:
        '''
            tuple: The depth mask of the framebuffer.
        '''

        return self.mglo.depth_mask

    @depth_mask.setter
    def depth_mask(self, value):
        self.mglo.depth_mask = value

    @property
    def width(self) -> int:
        '''
            int: The width of the framebuffer.
        '''

        return self._size[0]

    @property
    def height(self) -> int:
        '''
            int: The height of the framebuffer.
        '''

        return self._size[1]

    @property
    def size(self) -> tuple:
        '''
            tuple: The size of the framebuffer.
        '''

        return self._size

    @property
    def samples(self) -> int:
        '''
            int: The samples of the framebuffer.
        '''

        return self._samples

    @property
    def bits(self) -> Dict[str, str]:
        '''
            dict: The bits of the framebuffer.
        '''

        return self.mglo.bits

    @property
    def color_attachments(self) -> Tuple[Union[Texture, Renderbuffer], ...]:
        '''
            tuple: The color attachments of the framebuffer.
        '''

        return self._color_attachments

    @property
    def depth_attachment(self) -> Union[Texture, Renderbuffer]:
        '''
            Texture or Renderbuffer: The depth attachment of the framebuffer.
        '''

        return self._depth_attachment

    @property
    def glo(self) -> int:
        '''
            int: The internal OpenGL object.
            This values is provided for debug purposes only.
        '''

        return self._glo

    def clear(self, red=0.0, green=0.0, blue=0.0, alpha=0.0, depth=1.0, *, viewport=None) -> None:
        '''
            Clear the framebuffer.

            If the `viewport` is not ``None`` then scrissor test
            will be used to clear the given viewport.

            If the `viewport` is a 2-tuple it will clear the
            ``(0, 0, width, height)`` where ``(width, height)`` is the 2-tuple.

            If the `viewport` is a 4-tuple it will clear the given viewport.

            Args:
                red (float): color component.
                green (float): color component.
                blue (float): color component.
                alpha (float): alpha component.
                depth (float): depth value.

            Keyword Args:
                viewport (tuple): The viewport.
        '''

        if viewport is not None:
            viewport = tuple(viewport)

        self.mglo.clear(red, green, blue, alpha, depth, viewport)

    def use(self) -> None:
        '''
            Bind the framebuffer. Set the target for the :py:meth:`VertexArray.render`.
        '''

        self.ctx.fbo = self
        self.mglo.use()

    def read(self, viewport=None, components=3, *, attachment=0, alignment=1, dtype='f1') -> bytes:
        '''
            Read the content of the framebuffer.

            Args:
                viewport (tuple): The viewport.
                components (int): The number of components to read.

            Keyword Args:
                attachment (int): The color attachment.
                alignment (int): The byte alignment of the pixels.
                dtype (str): Data type.

            Returns:
                bytes
        '''
        return self.mglo.read(viewport, components, attachment, alignment, dtype)

    def read_into(self, buffer, viewport=None, components=3, *,
                  attachment=0, alignment=1, dtype='f1', write_offset=0) -> None:
        '''
            Read the content of the framebuffer into a buffer.

            Args:
                buffer (bytearray): The buffer that will receive the pixels.
                viewport (tuple): The viewport.
                components (int): The number of components to read.

            Keyword Args:
                attachment (int): The color attachment.
                alignment (int): The byte alignment of the pixels.
                dtype (str): Data type.
                write_offset (int): The write offset.
        '''

        if type(buffer) is Buffer:
            buffer = buffer.mglo

        return self.mglo.read_into(buffer, viewport, components, attachment, alignment, dtype, write_offset)

    def release(self) -> None:
        '''
            Release the ModernGL object.
        '''

        self.mglo.release()
