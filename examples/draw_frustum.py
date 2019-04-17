"""

"""
from math import cos, radians, sin
import moderngl
import numpy as np
from objloader import Obj
import os
from pyrr import Matrix44, Quaternion
from pyrr import Vector3, matrix44, vector, vector3
from pyrr.quaternion import create_from_eulers, apply_to_vector, inverse
import time
from typing import Tuple
#
from examples.example_window import Example, run_example


# Direction Definitions
RIGHT = 1
LEFT = 2
FORWARD = 3
BACKWARD = 4
UP = 5
DOWN = 6

# Movement Definitions
STILL = 0
POSITIVE = 1
NEGATIVE = 2


def local(*path):
    return os.path.join(os.path.dirname(__file__), *path)


def inverse_rotate(q: Quaternion, v: Vector3) -> Vector3:
    """Returns the image of v by the Quaternion inverse()
    rotation.rotate() performs an inverse transformation.
    Same as inverse().rotate(v).

    :param q:
    :param v:
    :return:
    """
    return apply_to_vector(inverse(q), v)


def creative_modelview_from_position_orientation(
        position: Vector3,
        orientation: Quaternion
) -> matrix44:
    """

    :param position:
    :param orientation:
    :return:
    """
    q = orientation

    q00 = 2.0 * q[0] * q[0]
    q11 = 2.0 * q[1] * q[1]
    q22 = 2.0 * q[2] * q[2]

    q01 = 2.0 * q[0] * q[1]
    q02 = 2.0 * q[0] * q[2]
    q03 = 2.0 * q[0] * q[3]

    q12 = 2.0 * q[1] * q[2]
    q13 = 2.0 * q[1] * q[3]

    q23 = 2.0 * q[2] * q[3]

    model_view_matrix = matrix44.create_identity()
    model_view_matrix[0][0] = 1.0 - q11 - q22
    model_view_matrix[0][1] = q01 - q23
    model_view_matrix[0][2] = q02 + q13
    model_view_matrix[0][3] = 0.0

    model_view_matrix[1][0] = q01 + q23
    model_view_matrix[1][1] = 1.0 - q22 - q00
    model_view_matrix[1][2] = q12 - q03
    model_view_matrix[1][3] = 0.0

    model_view_matrix[2][0] = q02 - q13
    model_view_matrix[2][1] = q12 + q03
    model_view_matrix[2][2] = 1.0 - q11 - q00
    model_view_matrix[2][3] = 0.0

    t = inverse_rotate(q, position)
    model_view_matrix[3][0] = -t[0]
    model_view_matrix[3][1] = -t[1]
    model_view_matrix[3][2] = -t[2]
    model_view_matrix[3][3] = 1.0

    return model_view_matrix


class Projection:
    """
    Represent a projection matrix and its various properties
    including tools.
    """
    def __init__(self, aspect_ratio=9 / 16, fov=75, near=1, far=100):
        self.aspect_ratio = aspect_ratio
        self.fov = fov
        self.near = near
        self.far = far
        self.matrix = None
        self.update()

    def update(self, aspect_ratio=None, fov=None, near=None, far=None):
        """
        Update the internal projection matrix based on current values
        or values passed in if specified.

        :param aspect_ratio: New aspect ratio
        :param fov: New field of view
        :param near: New near value
        :param far: New far value
        """
        self.aspect_ratio = aspect_ratio or self.aspect_ratio
        self.fov = fov or self.fov
        self.near = near or self.near
        self.far = far or self.far

        self.matrix = Matrix44.perspective_projection(
            self.fov, self.aspect_ratio, self.near, self.far)

    def tobytes(self):
        return self.matrix.astype('f4').tobytes()

    @property
    def projection_constants(self):
        """
        Returns the (x, y) projection constants for the current projection.
        :return: x, y tuple projection constants
        """
        return (
            self.far / (self.far - self.near),
            (self.far * self.near) / (self.near - self.far)
        )


class Camera:
    """Simple camera class containing projection"""
    def __init__(self, fov=60, aspect=1.0, near=1, far=100):
        """
        Initialize camera using a specific projection

        :param fov: Field of view
        :param aspect: Aspect ratio
        :param near: Near plane
        :param far: Far plane
        """
        self.position = Vector3([0.0, 0.0, 0.0])
        # Default camera placement
        self.up = Vector3([0.0, 1.0, 0.0])
        self.right = Vector3([1.0, 0.0, 0.0])
        self.dir = Vector3([0.0, 0.0, -1.0])
        # Yaw and Pitch
        self.yaw = -90.0
        self.pitch = 0.0

        # World up vector
        self._up = Vector3([0.0, 1.0, 0.0])

        # Projection
        self.projection = Projection(aspect, fov, near, far)

    def set_position(self, x, y, z):
        """
        Set the 3D position of the camera

        :param x: float
        :param y: float
        :param z: float
        """
        self.position = Vector3([x, y, z])

    @property
    def view_matrix(self):
        """
        :return: The current view matrix for the camera
        """
        self._update_yaw_and_pitch()
        return self._gl_look_at(self.position, self.position + self.dir,
                                self._up)

    def _update_yaw_and_pitch(self):
        """
        Updates the camera vectors based on the current yaw and pitch
        """
        front = Vector3([0.0, 0.0, 0.0])
        front.x = cos(radians(self.yaw)) * cos(radians(self.pitch))
        front.y = sin(radians(self.pitch))
        front.z = sin(radians(self.yaw)) * cos(radians(self.pitch))

        self.dir = vector.normalise(front)
        self.right = vector.normalise(vector3.cross(self.dir, self._up))
        self.up = vector.normalise(vector3.cross(self.right, self.dir))

    def look_at(self, vec=None, pos=None):
        """
        Look at a specific point

        :param vec: Vector3 position
        :param pos: python list [x, y, x]
        :return: Camera matrix
        """
        if pos is None:
            vec = Vector3(pos)

        if vec is None:
            raise ValueError("vector or pos must be set")

        return self._gl_look_at(self.position, vec, self._up)

    def _gl_look_at(self, pos, target, up):
        """
        The standard lookAt method

        :param pos: current position
        :param target: target position to look at
        :param up: direction up
        """
        z = vector.normalise(pos - target)
        x = vector.normalise(vector3.cross(vector.normalise(up), z))
        y = vector3.cross(z, x)

        translate = matrix44.create_identity()
        translate[3][0] = -pos.x
        translate[3][1] = -pos.y
        translate[3][2] = -pos.z

        rotate = matrix44.create_identity()
        rotate[0][0] = x[0]  # -- X
        rotate[1][0] = x[1]
        rotate[2][0] = x[2]
        rotate[0][1] = y[0]  # -- Y
        rotate[1][1] = y[1]
        rotate[2][1] = y[2]
        rotate[0][2] = z[0]  # -- Z
        rotate[1][2] = z[1]
        rotate[2][2] = z[2]

        return matrix44.multiply(translate, rotate)


class CameraQuaternion(Camera):
    """
    void Camera::setViewDirection(const Vec &direction)
    https://github.com/GillesDebunne/libQGLViewer/blob/master/QGLViewer/camera.cpp#L1151


    https://github.com/GillesDebunne/libQGLViewer/blob/master/QGLViewer/quaternion.cpp#L136
    """

    def __init__(self, fov=60, aspect=1.0, near=1, far=100):
        """
        Initialize camera using a specific projection

        :param fov: Field of view
        :param aspect: Aspect ratio
        :param near: Near plane
        :param far: Far plane
        """
        super().__init__(fov=fov, aspect=aspect, near=near, far=far)

        # Eulers: +Roll
        self.roll = 0.0
        # self.yall = 0.0

        # Orientation: quaternion
        self.orientation = create_from_eulers((self.roll, self.pitch, self.yaw))

    @property
    def eulers(self) -> Tuple[float, float, float]:
        return self.yaw, self.pitch, self.roll

    def _update_yaw_and_pitch(self):
        """
        Updates the camera vectors based on the current yaw and pitch
        """
        self.orientation = create_from_eulers(self.eulers)


class SystemCamera(Camera):
    """System camera controlled by mouse and keyboard"""
    def __init__(self, fov=60, aspect=1.0, near=1, far=100):
        # Position movement states
        self._xdir = STILL
        self._zdir = STILL
        self._ydir = STILL
        self._last_time = 0

        # Velocity in axis units per second
        self.velocity = 10.0
        self.mouse_sensitivity = 0.5
        self.last_x = None
        self.last_y = None

        super().__init__(fov=fov, aspect=aspect, near=near, far=far)

    def move_left(self, activate):
        self.move_state(LEFT, activate)

    def move_right(self, activate):
        self.move_state(RIGHT, activate)

    def move_forward(self, activate):
        self.move_state(FORWARD, activate)

    def move_backward(self, activate):
        self.move_state(BACKWARD, activate)

    def move_up(self, activate):
        self.move_state(UP, activate)

    def move_down(self, activate):
        self.move_state(DOWN, activate)

    def move_state(self, direction, activate):
        """
        Set the camera position move state

        :param direction: What direction to update
        :param activate: Start or stop moving in the direction
        """
        if direction == RIGHT:
            self._xdir = POSITIVE if activate else STILL
        elif direction == LEFT:
            self._xdir = NEGATIVE if activate else STILL
        elif direction == FORWARD:
            self._zdir = NEGATIVE if activate else STILL
        elif direction == BACKWARD:
            self._zdir = POSITIVE if activate else STILL
        elif direction == UP:
            self._ydir = POSITIVE if activate else STILL
        elif direction == DOWN:
            self._ydir = NEGATIVE if activate else STILL

    def rot_state(self, x, y):
        """
        Set the rotation state of the camera

        :param x: viewport x pos
        :param y: viewport y pos
        """
        if self.last_x is None:
            self.last_x = x
        if self.last_y is None:
            self.last_y = y

        x_offset = self.last_x - x
        y_offset = self.last_y - y

        self.last_x = x
        self.last_y = y

        x_offset *= self.mouse_sensitivity
        y_offset *= self.mouse_sensitivity

        self.yaw -= y_offset
        self.pitch -= x_offset

        self._update_yaw_and_pitch()

    @property
    def view_matrix(self):
        """
        :return: The current view matrix for the camera
        """
        # Use separate time in camera so we can move it when the demo is paused
        now = time.time()
        # If the camera has been inactive for a while, a large time delta
        # can suddenly move the camera far away from the scene
        t = max(now - self._last_time, 0)
        self._last_time = now

        # X Movement
        if self._xdir == POSITIVE:
            self.position += self.right * self.velocity * t
        elif self._xdir == NEGATIVE:
            self.position -= self.right * self.velocity * t

        # Z Movement
        if self._zdir == NEGATIVE:
            self.position += self.dir * self.velocity * t
        elif self._zdir == POSITIVE:
            self.position -= self.dir * self.velocity * t

        # Y Movement
        if self._ydir == POSITIVE:
            self.position += self.up * self.velocity * t
        elif self._ydir == NEGATIVE:
            self.position -= self.up * self.velocity * t

        return self._gl_look_at(self.position,
                                self.position + self.dir, self._up)


class SystemCameraQuaternion(CameraQuaternion):
    """System camera controlled by mouse and keyboard"""
    def __init__(self, fov=60, aspect=1.0, near=1, far=100):
        # Position movement states
        self._xdir = STILL
        self._zdir = STILL
        self._ydir = STILL
        self._last_time = 0

        # Velocity in axis units per second
        self.velocity = 10.0
        self.mouse_sensitivity = 0.5
        self.mouse_sensitivity *= 0.01
        self.last_x = None
        self.last_y = None

        super().__init__(fov=fov, aspect=aspect, near=near, far=far)

        self.mv = creative_modelview_from_position_orientation(self.position,
                                                               self.orientation)

    def move_left(self, activate):
        self.move_state(LEFT, activate)

    def move_right(self, activate):
        self.move_state(RIGHT, activate)

    def move_forward(self, activate):
        self.move_state(FORWARD, activate)

    def move_backward(self, activate):
        self.move_state(BACKWARD, activate)

    def move_up(self, activate):
        self.move_state(UP, activate)

    def move_down(self, activate):
        self.move_state(DOWN, activate)

    def move_state(self, direction, activate):
        """
        Set the camera position move state

        :param direction: What direction to update
        :param activate: Start or stop moving in the direction
        """
        if direction == RIGHT:
            self._xdir = POSITIVE if activate else STILL
        elif direction == LEFT:
            self._xdir = NEGATIVE if activate else STILL
        elif direction == FORWARD:
            self._zdir = NEGATIVE if activate else STILL
        elif direction == BACKWARD:
            self._zdir = POSITIVE if activate else STILL
        elif direction == UP:
            self._ydir = POSITIVE if activate else STILL
        elif direction == DOWN:
            self._ydir = NEGATIVE if activate else STILL

    def rot_state(self, x, y):
        """
        Set the rotation state of the camera

        :param x: viewport x pos
        :param y: viewport y pos
        """
        if self.last_x is None:
            self.last_x = x
        if self.last_y is None:
            self.last_y = y

        x_offset = self.last_x - x
        y_offset = self.last_y - y

        self.last_x = x
        self.last_y = y

        x_offset *= self.mouse_sensitivity
        y_offset *= self.mouse_sensitivity

        rotate = Quaternion()
        if x_offset:
            rotatex = Quaternion.from_x_rotation(x_offset)
            rotate *= rotatex

        if y_offset:
            rotatey = Quaternion.from_y_rotation(y_offset)
            rotate *= rotatey

        self.mv *= matrix44.create_from_inverse_of_quaternion(rotate)

    @property
    def view_matrix(self):
        """
        :return: The current view matrix for the camera
        """
        # Use separate time in camera so we can move it when the demo is paused
        now = time.time()
        # If the camera has been inactive for a while, a large time delta
        # can suddenly move the camera far away from the scene
        t = max(now - self._last_time, 0)
        self._last_time = now

        # X Movement
        if self._xdir == POSITIVE:
            self.position += self.right * self.velocity * t
        elif self._xdir == NEGATIVE:
            self.position -= self.right * self.velocity * t

        # Z Movement
        if self._zdir == NEGATIVE:
            self.position += self.dir * self.velocity * t
        elif self._zdir == POSITIVE:
            self.position -= self.dir * self.velocity * t

        # Y Movement
        if self._ydir == POSITIVE:
            self.position += self.up * self.velocity * t
        elif self._ydir == NEGATIVE:
            self.position -= self.up * self.velocity * t

        try:
            # return creative_modelview_from_position_orientation(
            #     self.position, self.orientation)
            # return matrix44.create_from_translation(self.position)
            return self.mv
        except Exception as e:
            print(f"Exception: {e}")


class DrawFrustumExample(Example):
    def __init__(self, ctx=None):
        if ctx is None:
            self.ctx = moderngl.create_context()
        else:
            self.ctx = ctx

        self.prog = self.ctx.program(
            vertex_shader='''
                #version 330

                uniform mat4 Mvp;

                in vec3 in_vert;
                
                void main() {
                    gl_Position = Mvp * vec4(in_vert, 1.0);
                }
            ''',
            fragment_shader='''
                #version 330

                uniform vec4 Color;
                
                out vec4 f_color;

                void main() {
                    f_color = Color;
                }
            ''',
        )

        self.mvp = self.prog['Mvp']
        self.color = self.prog['Color']

        obj = Obj.open(local('data', 'crate.obj'))

        self.vbo = self.ctx.buffer(obj.pack('vx vy vz'))
        self.vao = self.ctx.simple_vertex_array(self.prog, self.vbo, 'in_vert')

        # Map vertices to centered unit cube
        # [-0.5, -0.5, 0.0]x[+0.5, +0.5, 1.0] -> [-1, -1, -1]x[+1, +1, +1]
        self.mv_frustum = Matrix44.from_translation((0, 0, -1))
        self.mv_frustum *= Matrix44.from_scale((2, 2, 2))

        aspect = 1
        if self.wnd is not None:
            aspect = self.wnd.ratio
        self.sys_camera = SystemCameraQuaternion(fov=60, aspect=aspect,
                                                 near=1, far=10)

    def _render_frustum(self, mvp_cam, inv_mvp_frustrum,
                        color=(0.0, 1.0, 0.0, 1.0)):
        """

        :param mvp_cam:
        :param inv_mvp_frustrum:
        :param color:
        :return:
        """
        self.color.value = color
        self.mvp.write((mvp_cam * inv_mvp_frustrum).astype('f4').tobytes())
        self.vao.render()

    def render_frustum(
            self,
            mvp_cam,
            inv_mvp_frustrum,
            draw_edges=True,
            draw_faces=True,
            color_edges=(1.0, 0.0, 0.0, 1.0),
            color_faces=(0.10, 0.0, 0.75, 0.1),
    ):
        """

        :param mvp_cam:
        :param inv_mvp_frustrum:
        :param draw_edges:
        :param draw_faces:
        :param color_edges:
        :param color_faces:
        :return:
        """
        mv_frustum = inv_mvp_frustrum * self.mv_frustum

        if draw_edges:
            self.ctx.wireframe = True
            self._render_frustum(mvp_cam, mv_frustum, color_edges)
            self.ctx.wireframe = False

        if draw_faces:
            self.ctx.wireframe = False
            self.ctx.enable(moderngl.BLEND)
            depth_mask = self.ctx.fbo.depth_mask
            self.ctx.fbo.depth_mask = False
            self._render_frustum(mvp_cam, mv_frustum, color_faces)
            self.ctx.disable(moderngl.BLEND)
            self.ctx.fbo.depth_mask = depth_mask

    def render(self):
        self.sys_camera.rot_state(*self.wnd.mouse)

        angle = self.wnd.time
        self.ctx.viewport = self.wnd.viewport
        self.ctx.clear(0.0, 0.0, 0.0)
        self.ctx.enable(moderngl.DEPTH_TEST)
        self.ctx.wireframe = True

        ########################################################################
        # View Camera Matrices
        ########################################################################
        angle *= 0.0
        camera_pos = (np.cos(angle) * 5.0, np.sin(angle) * 5.0, 20.0)
        proj_cam = Matrix44.perspective_projection(45.0, self.wnd.ratio,
                                                   0.1, 1000.0)
        lookat_cam = Matrix44.look_at(
            camera_pos,
            (0.0, 0.0, 0.5),
            (0.0, 0.0, 1.0),
        )
        mvp_cam = proj_cam * lookat_cam
        ########################################################################

        ########################################################################
        # Frustum Matrices (Camera Light (for example))
        ########################################################################
        pos_frustum = (0, -1, 0)
        cam = self.sys_camera
        cam.set_position(*pos_frustum)
        mvp_frustum = cam.projection.matrix * cam.view_matrix
        inv_mvp_frustrum = mvp_frustum.inverse

        self.render_frustum(mvp_cam, inv_mvp_frustrum)


if __name__ == '__main__':
    run_example(DrawFrustumExample)
