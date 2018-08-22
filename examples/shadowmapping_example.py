"""
TODO:
- cullface (front, back) for different render pass (standard, shadow pass, ...)
- draw frustums/cameras (light, camera, differents point of view, ...)
- optimize (simply) the light (shadow) frustum
- try to work with real depth texture and shadow samplers (https://www.khronos.org/opengl/wiki/Sampler_(GLSL)#Shadow_samplers)

Links:
- http://www.opengl-tutorial.org/fr/intermediate-tutorials/tutorial-16-shadow-mapping/#shadowmap-basique
- https://learnopengl.com/Advanced-Lighting/Shadows/Shadow-Mapping
- https://learnopengl.com/Advanced-OpenGL/Depth-testing
"""
import moderngl
import numpy as np
from objloader import Obj
import os
from PIL import Image
from pyrr import Matrix44, matrix44
from pyrr import Vector3
from pyrr import Vector4
#
from examples.draw_frustum import DrawFrustumExample
from examples.example_window import Example, run_example


def local(*path):
    return os.path.join(os.path.dirname(__file__), *path)


def bbox2_3D(img):
    r = np.any(img, axis=(1, 2))
    c = np.any(img, axis=(0, 2))
    z = np.any(img, axis=(0, 1))

    rmin, rmax = np.where(r)[0][[0, -1]]
    cmin, cmax = np.where(c)[0][[0, -1]]
    zmin, zmax = np.where(z)[0][[0, -1]]

    return rmin, rmax, cmin, cmax, zmin, zmax


class ShadowMappingSample(Example):
    def __init__(self):
        self.ctx = moderngl.create_context(require=330)

        self.prog = self.ctx.program(
            vertex_shader='''
                #version 330

                uniform mat4 Mvp;
                uniform mat4 DepthBiasMVP;

                in vec3 in_vert;
                in vec3 in_norm;
                in vec2 in_text;

                out vec3 v_vert;
                out vec3 v_norm;
                out vec2 v_text;
                out vec4 v_ShadowCoord;

                void main() {
                    gl_Position = Mvp * vec4(in_vert, 1.0);
                    
                    v_ShadowCoord = DepthBiasMVP * vec4(in_vert, 1.0);
                    
                    v_vert = in_vert;
                    v_norm = in_norm;
                    v_text = in_text;
                }
            ''',
            fragment_shader='''
                #version 330

                uniform vec3 Light;
                uniform vec3 Color;
                uniform bool UseTexture;

                uniform sampler2D Texture;

                in vec3 v_vert;
                in vec3 v_norm;
                in vec2 v_text;
                in vec4 v_ShadowCoord;

                out vec4 f_color;                

                float compute_shadow(in float cosTheta) {
                    //vec4 ShadowCoord = v_ShadowCoord / v_ShadowCoord.w;
                    vec4 ShadowCoord = v_ShadowCoord;
                    
                    vec2 ShadowCoord_LightView = ShadowCoord.xy/ShadowCoord.w;
                    float z_from_light = texture(Texture, ShadowCoord_LightView).r;
                    
                    // const float bias = 0.005;
                    float bias = 0.005*tan(acos(cosTheta));
                    bias = clamp(bias, 0,0.01);                    
                    float z_from_cam = (ShadowCoord.z - bias) / ShadowCoord.w;
                    
                    float is_texel_shadowed = (z_from_cam >=  z_from_light ? 1.0: 0.0);
                    float visibility = 1.0 - is_texel_shadowed;
                    return visibility;
                }
                

                void main() {
                    float cosTheta = dot(normalize(Light - v_vert), normalize(v_norm));
                    float lum = clamp(cosTheta, 0.0, 1.0) * 0.9 + 0.1;
                    if (UseTexture) {
                        f_color = texture(Texture, v_text);
                    } else {
                        float visibility = compute_shadow(cosTheta);                 

                        lum *= visibility;

                        const float coefAmbient = 0.15;
                        f_color = vec4(Color * (coefAmbient + lum), 1.0);
                    }
                }
            ''',
        )

        self.prog_shadow = self.ctx.program(
            vertex_shader='''
                        #version 330

                        uniform mat4 Mvp;

                        in vec3 in_vert;
                        
                        out vec4 v_vert;

                        void main() {
                            gl_Position = Mvp * vec4(in_vert, 1.0);
                            v_vert = gl_Position;
                        }
                    ''',
            fragment_shader='''
                        #version 330

                        layout(location = 0) out float fragmentdepth;
                        
                        in vec4 v_vert;

                        void main() {
                            fragmentdepth = gl_FragCoord.z;
                        }
                    ''',
        )

        self.mvp = self.prog['Mvp']
        self.depth_mvp = self.prog['DepthBiasMVP']
        self.light = self.prog['Light']
        self.color = self.prog['Color']
        self.use_texture = self.prog['UseTexture']
        self.prog['Texture'].value = 0

        self.mvp_shadow = self.prog_shadow['Mvp']

        self.objects = {}
        self.objects_shadow = {}
        self.objects_mat_bbox = {}

        for name in ['ground', 'grass', 'billboard', 'billboard-holder', 'billboard-image']:
            obj = Obj.open(local('data', 'scene-1-%s.obj' % name))

            vbo = self.ctx.buffer(obj.pack('vx vy vz nx ny nz tx ty'))
            vao = self.ctx.simple_vertex_array(self.prog, vbo, "in_vert", "in_norm", "in_text")
            self.objects[name] = vao

            vbo_shadow = self.ctx.buffer(obj.pack('vx vy vz'))  # only vertices
            vao_shadow = self.ctx.simple_vertex_array(self.prog_shadow, vbo_shadow, "in_vert")
            self.objects_shadow[name] = vao_shadow

            ##########################################
            # Compute BBox (Orthographic) Matrix
            ##########################################
            np_obj_vert = np.array(obj.vert)
            bbox_min, bbox_max = Vector3(np.min(np_obj_vert, axis=0)), Vector3(np.max(np_obj_vert, axis=0))
            mat_bbox = Matrix44.orthogonal_projection(bbox_min.x, bbox_max.x,
                                                      bbox_min.y, bbox_max.y,
                                                      -bbox_min.z, -bbox_max.z)
            assert ((mat_bbox * bbox_min) - Vector3((-1, -1, -1))).length <= 0.0001
            assert ((mat_bbox * bbox_max) - Vector3((1, 1, 1))).length <= 0.0001
            self.objects_mat_bbox[name] = mat_bbox
            ##########################################

        img = Image.open(local('data', 'infographic-1.jpg')).transpose(Image.FLIP_TOP_BOTTOM).convert('RGB')
        self.texture1 = self.ctx.texture(img.size, 3, img.tobytes())
        self.texture1.build_mipmaps()

        self.texture2 = self.ctx.texture((1, 1), 3)  # TODO: (1) composents influenced the bug below
        # depth_attachment = self.ctx.depth_renderbuffer(self.wnd.size)
        self.fbo = self.ctx.framebuffer(color_attachments=[self.texture2])

        ############################################################################################################
        shadow_size = tuple([1 << 9] * 2)
        print(f"Depth texture size: {shadow_size}")

        # self.tex_depth = self.ctx.depth_texture(size=shadow_size)
        # self.tex_depth.compare_func = '0'
        # self.fbo_shadow = self.ctx.framebuffer(depth_attachment=self.tex_depth)
        #
        # self.fbo_shadow = self.ctx.framebuffer(color_attachments=[self.tex_depth], depth_attachment=depth_attachment)
        #

        depth_attachment_shadow = self.ctx.depth_renderbuffer(shadow_size)
        self.tex_depth = self.ctx.texture(shadow_size, components=1, dtype='f4')
        self.fbo_shadow = self.ctx.framebuffer(color_attachments=[self.tex_depth],
                                               depth_attachment=depth_attachment_shadow)
        ############################################################################################################

        self.render_light_frustum = DrawFrustumExample()

    def render(self):
        self.ctx.viewport = self.wnd.viewport
        self.ctx.clear(1.0, 1.0, 1.0)
        self.ctx.enable(moderngl.DEPTH_TEST)

        cam_proj = Matrix44.perspective_projection(45.0, self.wnd.ratio, 1.0, 100.0)
        scene_position = (47.697, -8.147, 24.498)
        cam_lookat = Matrix44.look_at(
            scene_position,
            (0.0, 0.0, 8.0),
            (0.0, 0.0, 1.0),
        )
        cam_rotate = Matrix44.from_z_rotation(self.wnd.time * 0.25)
        # cam_rotate = Matrix44.identity()
        cam_mvp = cam_proj * cam_lookat * cam_rotate
        self.mvp.write(cam_mvp.astype('f4').tobytes())

        # light_rotate = Matrix44.from_z_rotation(-np.sin(self.wnd.time * 0.25) * 0.50 + 0.2)
        light_rotate = Matrix44.identity()
        light_pos = light_rotate * Vector3((-60.69, -40.14, 52.49))
        self.light.value = tuple(light_pos)
        bias_matrix = Matrix44(
            [
                [0.5, 0.0, 0.0, 0.0],
                [0.0, 0.5, 0.0, 0.0],
                [0.0, 0.0, 0.5, 0.0],
                [0.5, 0.5, 0.5, 1.0]
            ]
        )
        light_proj = Matrix44.perspective_projection(20.0, self.wnd.ratio, 60.0, 100.0)
        light_lookat = Matrix44.look_at(
            light_pos,
            (0, 0, 0),
            (0.0, 0.0, 1.0),
        )
        light_mpv = light_proj * light_lookat
        depthBiasMVP = bias_matrix * light_mpv

        self.depth_mvp.write(depthBiasMVP.astype('f4').tobytes())
        self.mvp_shadow.write(light_mpv.astype('f4').tobytes())

        self.fbo_shadow.clear(1.0, 1.0, 1.0)
        self.fbo_shadow.use()
        for vao_shadow in self.objects_shadow.values():
            vao_shadow.render()

        self.fbo.use()  # TODO: strange .. need to 'use' this fbo to have a 'correct' rendering on screen ... :/ see (1)
        self.ctx.screen.use()
        self.tex_depth.use()

        self.use_texture.value = False

        self.color.value = (0.67, 0.49, 0.29)
        self.objects['ground'].render()

        self.color.value = (0.46, 0.67, 0.29)
        self.objects['grass'].render()

        self.color.value = (1.0, 1.0, 1.0)
        self.objects['billboard'].render()

        self.color.value = (0.2, 0.2, 0.2)
        self.objects['billboard-holder'].render()

        self.use_texture.value = True
        self.texture1.use(0)
        self.objects['billboard-image'].render()

        # BBox objects frustums
        for mat_bbox in self.objects_mat_bbox.values():
            self.render_light_frustum.render_frustum(cam_mvp, mat_bbox.inverse,
                                                     color_faces=(0.05, 0.50, 0.30, 0.25),
                                                     color_edges=(0.5, 0.15, 0.65, 1.0))

        # Light Frustum
        self.render_light_frustum.render_frustum(cam_mvp, light_mpv.inverse)


run_example(ShadowMappingSample)
