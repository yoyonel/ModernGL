import sys
import moderngl


class BaseKeys:
    """
    Namespace for mapping key constants.
    Add missing keys for all windows when needed.
    """
    ACTION_PRESS = 'ACTION_PRESS'
    ACTION_RELEASE = 'ACTION_RELEASE'

    ESCAPE = None
    SPACE = None
    ENTER = None
    PAGE_UP = None
    PAGE_DOWN = None
    LEFT = None
    RIGHT = None
    UP = None
    DOWN = None

    A = None
    B = None
    C = None
    D = None
    E = None
    F = None
    G = None
    H = None
    I = None
    J = None
    K = None
    L = None
    M = None
    N = None
    O = None
    P = None
    Q = None
    R = None
    S = None
    T = None
    U = None
    V = None
    W = None
    X = None
    Y = None
    Z = None


class BaseWindow:
    """Helper base class for a generic window implementation"""
    keys = BaseKeys

    def __init__(self, title="Example", gl_version=(3, 3), size=(1280, 720), resizable=True,
                 fullscreen=False, vsync=True, aspect_ratio=16/9, samples=4, cursor=True, **kwargs):
        self.title = title
        self.gl_version = gl_version
        self.width, self.height = size
        self.resizable = resizable
        self.buffer_width, self.buffer_height = size
        self.fullscreen = fullscreen
        self.vsync = vsync
        self.aspect_ratio = aspect_ratio
        self.samples = samples
        self.cursor = cursor

        self._close = False
        self.ctx = None
        self.example = None  # type: Example
        self.frames = 0

        if not self.keys:
            raise ValueError("Window {} class missing keys".format(self.__class__))

    @property
    def is_closing(self):
        return self._close

    def close(self):
        self._close = True

    def render(self, time: float, frame_time: float):
        """
        Renders the assigned effect

        Args:
            time (float): Current time in seconds
            frame_time (float): Delta time from last frame in seconds
        """
        self.example.render(time, frame_time)

    def swap_buffers(self):
        raise NotImplementedError()

    def resize(self, width, height):
        if self.example:
            self.example.resize(width, height)

    def destroy(self):
        raise NotImplementedError()

    def set_default_viewport(self):
        """
        Calculates the viewport based on the configured aspect ratio
        Will add black borders and center the viewport if the window
        do not match the viewport configured viewport.
        """
        expected_width = int(self.buffer_height * self.aspect_ratio)
        expected_height = int(expected_width / self.aspect_ratio)

        if expected_width > self.buffer_width:
            expected_width = self.buffer_width
            expected_height =  int(expected_width / self.aspect_ratio)

        blank_space_x = self.buffer_width - expected_width
        blank_space_y = self.buffer_height - expected_height

        self.ctx.viewport = (
            blank_space_x // 2,
            blank_space_y // 2,
            expected_width,
            expected_height,
        )

    @property
    def gl_version_code(self):
        return self.gl_version[0] * 100 +  self.gl_version[1] * 10

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
    window_size = (1280, 720)
    resizable = True
    gl_version = (3, 3)
    title = "Example"
    aspect_ratio = 16 / 9

    def __init__(self, ctx=None, wnd=None, **kwargs):
        self.ctx = ctx
        self.wnd = wnd

    def render(self, time: float, frame_time: float):
        """
        Renders the assigned effect

        Args:
            time (float): Current time in seconds
            frame_time (float): Delta time from last frame in seconds
        """
        raise NotImplementedError("Example:render not implemented")

    def resize(self, width, height):
        """
        Called every time the window is resized
        in case the example needs to do internal adustments
        """
        print("Window resized to", width, height)

    def key_event(self, key, action):
        """
        Called for every key press and release
        """
        pass

    def mouse_event(self, x, y):
        """
        Reports the current mouse cursor position in the window
        """
        pass
