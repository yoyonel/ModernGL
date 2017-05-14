'''
    framebuffer
'''


class Framebuffer:
    '''
        Framebuffer
    '''

    def __init__(self):
        self.mglo = None
        raise NotImplementedError('Framebuffer')

    @staticmethod
    def new(obj):
        '''
            internal use only
        '''

        res = Framebuffer.__new__(Framebuffer)
        res.mglo = obj
        return res

    def read(self, viewport=None, components=3, floats=False) -> bytes:
        '''
            read
        '''

        return self.mglo.read(viewport, components, floats)

    def use(self):
        '''
            Bind the framebuffer. Set the target for the
            `VertexArray.render` or `VertexArray.transform` methods.
        '''

        self.mglo.use()
