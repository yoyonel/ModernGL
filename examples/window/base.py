import sys
import moderngl


class BaseKeys:
    """
    Namespace for mapping key constants.
    Add missing keys for all windows when needed.
    """
    ACTION_PRESS = None
    ACTION_RELEASE = None

    ESCAPE = None
    SPACE = None
    ENTER = None

    A = None
    S = None
    D = None
    W = None

    LEFT = None
    RIGHT = None
    UP = None
    DOWN = None


class BaseWindow:
    """Helper base class for a generic window implementation"""
    keys = None  # type: BaseKeys

    def __init__(self, title="Example", gl_version=(3, 3), width=1280, height=720,
                 fullscreen=False, vsync=True, aspect_ratio=16/9, samples=4, cursor=True, **kwargs):
        self.title = title
        self.gl_version = gl_version
        self.width, self.height = width, height
        self.buffer_width, self.buffer_height = width, height
        self.fullscreen = fullscreen
        self.vsync = vsync
        self.aspect_ratio = aspect_ratio
        self.samples = samples
        self.cursor = cursor

        self._close = False
        self.ctx = None
        self.example = None

        if not self.keys:
            raise ValueError("Window {} class missing keys".format(self.__class__))

    @property
    def is_closing(self):
        return self._close

    def close(self):
        self._close = True

    def render(self):
        self.example.render()

    def swap_buffers(self):
        raise NotImplementedError()

    def destroy(self):
        raise NotImplementedError()

    def set_default_viewport(self):
        """
        Calculates the viewport based on the configured aspect ratio
        Will add black borders if the window do not match the viewport
        """
        expected_height = int(self.buffer_width / self.aspect_ratio)
        blank_space = self.buffer_height - expected_height
        self.ctx.viewport = (0, blank_space // 2, self.buffer_width, expected_height)

    def print_context_info(self):
        """
        Prints moderngl context info.
        """
        print("Context Version:")
        print('ModernGL:', moderngl.__version__)
        print('vendor:', self.ctx.info['GL_VENDOR'])
        print('renderer:', self.ctx.info['GL_RENDERER'])
        print('version:', self.ctx.info['GL_VERSION'])
        print('python:', sys.version)
        print('platform:', sys.platform)
        print('code:', self.ctx.version_code)


class Example:
    gl_version = (3, 3)
    title = "Example"
    aspect_ratio = 16/9

    def __init__(self, ctx=None, wnd=None, **kwargs):
        self.ctx = ctx
        self.wnd = wnd

    def render(self, current_time):
        pass

    def key_event(self, key, action):
        pass

    def mouse_event(self, x, y):
        pass
