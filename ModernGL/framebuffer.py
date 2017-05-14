'''
    framebuffer
'''

from .common import Object


class Framebuffer(Object):
    '''
        Framebuffer
    '''

    @staticmethod
    def new(obj):
        '''
            For internal use only.
        '''

        res = Framebuffer.__new__(Framebuffer)
        res.mglo = obj
        return res

    def read(self, viewport=None, components=3, floats=False) -> bytes:
        '''
            Read the framebuffer content.
        '''

        return self.mglo.read(viewport, components, floats)

    def use(self):
        '''
            Bind the framebuffer. Set the target for the
            `VertexArray.render` or `VertexArray.transform` methods.
        '''

        self.mglo.use()
