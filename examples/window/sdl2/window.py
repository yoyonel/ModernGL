import sdl2
import sdl2.ext
import sdl2.video
import moderngl

from window.base import BaseWindow
from window.sdl2.keys import Keys


class Window(BaseWindow):
    keys = Keys

    def __init__(self, **kwargs):
        super().__init__(**kwargs)

        self._window_closing = False

        if sdl2.SDL_Init(sdl2.SDL_INIT_VIDEO) != 0:
            raise ValueError("Failed to initialize sdl2")

        sdl2.video.SDL_GL_SetAttribute(sdl2.SDL_GL_CONTEXT_MAJOR_VERSION, self.gl_version[0])
        sdl2.video.SDL_GL_SetAttribute(sdl2.SDL_GL_CONTEXT_MINOR_VERSION, self.gl_version[1])
        sdl2.video.SDL_GL_SetAttribute(sdl2.SDL_GL_CONTEXT_PROFILE_MASK, sdl2.SDL_GL_CONTEXT_PROFILE_CORE)
        sdl2.video.SDL_GL_SetAttribute(sdl2.SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG, 1)
        sdl2.video.SDL_GL_SetAttribute(sdl2.SDL_GL_DOUBLEBUFFER, 1)
        sdl2.video.SDL_GL_SetAttribute(sdl2.SDL_GL_DEPTH_SIZE, 24)
        sdl2.SDL_ShowCursor(sdl2.SDL_ENABLE if self.cursor else sdl2.SDL_DISABLE)

        if self.samples > 1:
            sdl2.video.SDL_GL_SetAttribute(sdl2.SDL_GL_MULTISAMPLEBUFFERS, 1)
            sdl2.video.SDL_GL_SetAttribute(sdl2.SDL_GL_MULTISAMPLESAMPLES, self.samples)

        flags = sdl2.SDL_WINDOW_OPENGL
        if self.fullscreen:
            flags |= sdl2.SDL_WINDOW_FULLSCREEN_DESKTOP
        else:
            if self.resizable:
                flags |= sdl2.SDL_WINDOW_RESIZABLE

        self.window = sdl2.SDL_CreateWindow(
            self.title.encode(),
            sdl2.SDL_WINDOWPOS_UNDEFINED,
            sdl2.SDL_WINDOWPOS_UNDEFINED,
            self.width,
            self.height,
            flags,
        )

        if not self.window:
            raise ValueError("Failed to create window:", sdl2.SDL_GetError())

        self.context = sdl2.SDL_GL_CreateContext(self.window)
        sdl2.video.SDL_GL_SetSwapInterval(1 if self.vsync else 0)

        self.ctx = moderngl.create_context(require=self.gl_version_code)
        self.set_default_viewport()
        self.print_context_info()

    @property
    def is_closing(self):
        return self._window_closing

    def close(self):
        self._window_closing = True

    def swap_buffers(self):
        self.frames += 1
        sdl2.SDL_GL_SwapWindow(self.window)
        self.process_events()

    def resize(self, width, height):
        """
        Sets the new size and buffer size internally
        """
        self.width = width
        self.height = height
        self.buffer_width, self.buffer_height = self.width, self.height
        self.set_default_viewport()

    def process_events(self):
        for event in sdl2.ext.get_events():
            if event.type == sdl2.SDL_MOUSEMOTION:
                self.example.mouse_postion_event(event.motion.x, event.motion.y)

            elif event.type == sdl2.SDL_MOUSEBUTTONUP:
                # Support left and right mouse button for now
                if  event.button.button in [1, 3]:
                    self.example.mouse_press_event(
                        event.motion.x, event.motion.y,
                        1 if event.button.button == 1 else 2,
                    )

            elif event.type == sdl2.SDL_MOUSEBUTTONDOWN:
                # Support left and right mouse button for now
                if  event.button.button in [1, 3]:
                    self.example.mouse_release_event(
                        event.motion.x, event.motion.y,
                        1 if event.button.button == 1 else 2,
                    )

            elif event.type in [sdl2.SDL_KEYDOWN, sdl2.SDL_KEYUP]:
                if event.key.keysym.sym == sdl2.SDLK_ESCAPE:
                    self.close()

                self.example.key_event(event.key.keysym.sym, event.type)

            elif event.type == sdl2.SDL_QUIT:
                self.close()

            elif event.type == sdl2.SDL_WINDOWEVENT:
                if event.window.event == sdl2.SDL_WINDOWEVENT_RESIZED:
                    self.resize(event.window.data1, event.window.data2)

    def destroy(self):
        sdl2.SDL_GL_DeleteContext(self.context)
        sdl2.SDL_DestroyWindow(self.window)
        sdl2.SDL_Quit()
