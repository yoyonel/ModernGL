import moderngl
from PyQt5 import QtCore, QtOpenGL, QtWidgets

from window.base import BaseWindow
from window.pyqt5.keys import Keys


class Window(BaseWindow):
    keys = Keys

    def __init__(self, **kwargs):
        super().__init__(**kwargs)
        self._closed = False

        # Specify OpenGL context parameters
        gl = QtOpenGL.QGLFormat()
        gl.setVersion(self.gl_version[0], self.gl_version[1])
        gl.setProfile(QtOpenGL.QGLFormat.CoreProfile)
        gl.setDepthBufferSize(24)
        gl.setDoubleBuffer(True)
        gl.setSwapInterval(1 if self.vsync else 0)

        if self.samples > 1:
            gl.setSampleBuffers(True)
            gl.setSamples(self.samples)

        # We need an application object, but we are not using the event loop
        self.app = QtWidgets.QApplication([])

        # Create the OpenGL widget
        self.widget = QtOpenGL.QGLWidget(gl)
        self.widget.setWindowTitle(self.title)

        # Fetch desktop size
        if self.fullscreen:
            rect = QtWidgets.QDesktopWidget().screenGeometry()
            self.width = rect.width()
            self.height = rect.height()
            self.buffer_width = rect.width() * self.widget.devicePixelRatio()
            self.buffer_height = rect.height() * self.widget.devicePixelRatio()

        if self.resizable:
            size_policy = QtWidgets.QSizePolicy(
                QtWidgets.QSizePolicy.Expanding,
                QtWidgets.QSizePolicy.Expanding,
            )
            self.widget.setSizePolicy(size_policy)
            self.widget.resize(self.width, self.height)
        else:
            self.widget.setFixedSize(self.width, self.height)

        self.widget.move(QtWidgets.QDesktopWidget().rect().center() - self.widget.rect().center())
        # Needs to be set before show()
        self.widget.resizeGL = self.resize
        self.widget.show()

        if not self.cursor:
            self.widget.setCursor(QtCore.Qt.BlankCursor)

        if self.fullscreen:
            self.widget.showFullScreen()

        # We want mouse position events
        self.widget.setMouseTracking(True)

        # Override event functions
        self.widget.keyPressEvent = self.key_pressed_event
        self.widget.keyReleaseEvent = self.key_release_event
        self.widget.mouseMoveEvent = self.mouse_move_event
        self.widget.mousePressEvent = self.mouse_press_event
        self.widget.mouseReleaseEvent = self.mouse_release_event
        self.widget.closeEvent = self.close_event

        # Attach to the context
        self.ctx = moderngl.create_context(require=self.gl_version_code)

        # Ensure retina and 4k displays get the right viewport
        self.buffer_width = self.width * self.widget.devicePixelRatio()
        self.buffer_height = self.height * self.widget.devicePixelRatio()

        self.print_context_info()
        self.set_default_viewport()

    def swap_buffers(self):
        self.widget.swapBuffers()
        self.set_default_viewport()
        self.app.processEvents()
        self.frames += 1

    def resize(self, width, height):
        self.width = width
        self.height = height

        self.buffer_width = self.width * self.widget.devicePixelRatio()
        self.buffer_height = self.height * self.widget.devicePixelRatio()

        if self.ctx:
            self.set_default_viewport()

        super().resize(width, height)

    def key_pressed_event(self, event):
        if event.key() == self.keys.ESCAPE:
            self.close()

        self.example.key_event(event.key(), self.keys.ACTION_PRESS)

    def key_release_event(self, event):
        self.example.key_event(event.key(), self.keys.ACTION_RELEASE)

    def mouse_move_event(self, event):
        self.example.mouse_position_event(event.x(), event.y())

    def mouse_press_event(self, event):
        # Support left and right mouse button for now
        if event.button() not in [1, 2]:
            return

        self.example.mouse_press_event(event.x(), event.y(), event.button())

    def mouse_release_event(self, event):
        # Support left and right mouse button for now
        if event.button() not in [1, 2]:
            return

        self.example.mouse_release_event(event.x(), event.y(), event.button())

    def close_event(self, event):
        self.close()

    @property
    def is_closing(self):
        return self._closed

    def close(self):
        self._closed = True

    def destroy(self):
         QtCore.QCoreApplication.instance().quit()
