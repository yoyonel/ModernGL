'''
    Mock linters.
'''

# pylint: skip-file

__all__ = ['mgl', 'Error']


class Error(Exception):
    '''
        ModernGL Error
    '''


class MockObject:
    '''
        MockObject
    '''

    wrapper = None
    mglo = None


class Implementation:
    '''
        Implementation
    '''

    NOTHING = MockObject()
    BLEND = MockObject()
    DEPTH_TEST = MockObject()
    CULL_FACE = MockObject()

    LINEAR = MockObject()
    NEAREST = MockObject()
    LINEAR_MIPMAP = MockObject()
    NEAREST_MIPMAP = MockObject()

    TRIANGLES = MockObject()
    TRIANGLE_STRIP = MockObject()
    TRIANGLE_FAN = MockObject()
    LINES = MockObject()
    LINE_STRIP = MockObject()
    LINE_LOOP = MockObject()
    POINTS = MockObject()
    LINE_STRIP_ADJACENCY = MockObject()
    LINES_ADJACENCY = MockObject()
    TRIANGLE_STRIP_ADJACENCY = MockObject()
    TRIANGLES_ADJACENCY = MockObject()

    def create_context(self) -> 'Context':
        '''
            create_context
        '''

    def create_standalone_context(self) -> 'Context':
        '''
            create_standalone_context
        '''

    def set_error_class(self, *args) -> None:
        '''
            set_error_class
        '''

    def set_default_context_size(self, *args) -> None:
        '''
            set_default_context_size
        '''

    def strsize(self, *args) -> int:
        '''
            strsize
        '''


mgl = Implementation()
