from window import Example, run_example


class EmptyWindow(Example):
    gl_version = (3, 3)
    title = "Empty Window"
    window_size = (1280, 720)
    aspect_ratio = 16 / 9
    resizable = True

    def __init__(self, **kwargs):
        super().__init__(**kwargs)

    def render(self, time: float, frame_time: float):
        self.ctx.clear(0.2, 0.4, 0.7)


if __name__ == '__main__':
    run_example(EmptyWindow)
