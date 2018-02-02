import moderngl
from moderngl.ext.examples import run_example


class Example:
    def __init__(self, wnd):
        self.wnd = wnd
        self.ctx = moderngl.create_context()

    def render(self):
        self.ctx.viewport = self.wnd.viewport
        self.ctx.clear(0.2, 0.4, 0.7)


run_example(Example)
