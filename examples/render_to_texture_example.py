import os

import numpy as np
from pyrr import Matrix44

import moderngl
from ported._example import Example
from basic_colors_and_texture import ColorsAndTexture


class RenderToTexture(ColorsAndTexture):
    title = "Render to Texture"
    gl_version = (3, 3)

    def __init__(self, **kwargs):
        super().__init__(**kwargs)

        self.texture = self.ctx.texture(self.wnd.size, 3)
        depth_attachment = self.ctx.depth_renderbuffer(self.wnd.size)
        self.fbo = self.ctx.framebuffer(self.texture, depth_attachment)

    def render(self, time, frame_time):
        self.ctx.clear(1.0, 1.0, 1.0)
        self.ctx.enable(moderngl.DEPTH_TEST)

        proj = Matrix44.perspective_projection(45.0, self.aspect_ratio, 0.1, 1000.0)
        lookat = Matrix44.look_at(
            (47.697, -8.147, 24.498),
            (0.0, 0.0, 8.0),
            (0.0, 0.0, 1.0),
        )

        rotate = Matrix44.from_z_rotation(np.sin(time) * 0.5 + 0.2)

        for mode in ['render_to_texture', 'render_to_window']:
            if mode == 'render_to_texture':
                self.fbo.clear(1.0, 1.0, 1.0)
                self.fbo.use()
            else:
                self.ctx.screen.use()

            super().render(time, frame_time)


if __name__ == '__main__':
    RenderToTexture.run()
