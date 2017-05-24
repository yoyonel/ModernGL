'''
    Mock linters.
'''

# pylint: skip-file

__all__ = ['mgl', 'Error']


class Error(Exception):
    '''
        Error
    '''


class Implementation:
    '''
        Implementation
    '''

    BLEND = 'BLEND'
    DEPTH_TEST = 'DEPTH_TEST'
    CULL_FACE = 'CULL_FACE'
    MULTISAMPLE = 'MULTISAMPLE'

    TRIANGLES = 'TRIANGLES'
    TRIANGLE_STRIP = 'TRIANGLE_STRIP'
    TRIANGLE_FAN = 'TRIANGLE_FAN'
    LINES = 'LINES'
    LINE_STRIP = 'LINE_STRIP'
    LINE_LOOP = 'LINE_LOOP'
    POINTS = 'POINTS'
    LINE_STRIP_ADJACENCY = 'LINE_STRIP_ADJACENCY'
    LINES_ADJACENCY = 'LINES_ADJACENCY'
    TRIANGLE_STRIP_ADJACENCY = 'TRIANGLE_STRIP_ADJACENCY'
    TRIANGLES_ADJACENCY = 'TRIANGLES_ADJACENCY'


    def create_context() -> 'Context':
        '''
            create_context
        '''

    def create_standalone_context(*args) -> 'Context':
        '''
            create_standalone_context
        '''


mgl = Implementation()
