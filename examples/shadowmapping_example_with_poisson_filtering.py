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
import os

import moderngl
import numpy as np
from objloader import Obj
from PIL import Image
from pyrr import Matrix44
from pyrr import Vector3

from example_window import Example, run_example


def local(*path):
    return os.path.join(os.path.dirname(__file__), *path)


class ShadowMappingWithPoissonFilteringSample(Example):
    def __init__(self):
        self.ctx = moderngl.create_context()

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
                
                // https://github.com/opengl-tutorials/ogl/blob/master/tutorial16_shadowmaps/ShadowMapping.fragmentshader
                vec2 poissonDisk[16] = vec2[]( 
                    vec2( -0.94201624, -0.39906216 ), 
                    vec2( 0.94558609, -0.76890725 ), 
                    vec2( -0.094184101, -0.92938870 ), 
                    vec2( 0.34495938, 0.29387760 ), 
                    vec2( -0.91588581, 0.45771432 ), 
                    vec2( -0.81544232, -0.87912464 ), 
                    vec2( -0.38277543, 0.27676845 ), 
                    vec2( 0.97484398, 0.75648379 ), 
                    vec2( 0.44323325, -0.97511554 ), 
                    vec2( 0.53742981, -0.47373420 ), 
                    vec2( -0.26496911, -0.41893023 ), 
                    vec2( 0.79197514, 0.19090188 ), 
                    vec2( -0.24188840, 0.99706507 ), 
                    vec2( -0.81409955, 0.91437590 ), 
                    vec2( 0.19984126, 0.78641367 ), 
                    vec2( 0.14383161, -0.14100790 ) 
                );
                
                // Returns a random number based on a vec3 and an int.
                float random(vec3 seed, int i){
                    vec4 seed4 = vec4(seed,i);
                    float dot_product = dot(seed4, vec4(12.9898,78.233,45.164,94.673));
                    return fract(sin(dot_product) * 43758.5453);
                }

                float compute_shadow_with_poisson_filtering(in float cosTheta) {
                    //vec4 ShadowCoord = v_ShadowCoord / v_ShadowCoord.w;
                    vec4 ShadowCoord = v_ShadowCoord;
                    
                    // const float bias = 0.005;
                    float bias = 0.50*tan(acos(cosTheta));
                    bias = clamp(bias, 0, 0.50);
                    //const float bias = 0.250;
                    
                    float visibility = 1.0;
                    
                    const int nb_samples = 4;
                    
                    // Sample the shadow map vnb_samples` times
                    for (int i=0;i<nb_samples;i++){
                        // use either :
                        //  - Always the same samples.
                        //    Gives a fixed pattern in the shadow, but no noise
                        // int index = i;
                        //  - A random sample, based on the pixel's screen location. 
                        //    No banding, but the shadow moves with the camera, which looks weird.
                        // int index = int(16.0*random(gl_FragCoord.xyy, i))%16;
                        //  - A random sample, based on the pixel's position in world space.
                        //    The position is rounded to the millimeter to avoid too much aliasing
                        int index = int(16.0*random(floor(v_vert.xyz*1000.0), i))%16;

                        vec2 ShadowCoord_LightView = ShadowCoord.xy/ShadowCoord.w;
                        ShadowCoord_LightView +=  + poissonDisk[index]/700.0;
                        float z_from_light = texture(Texture, ShadowCoord_LightView).r;
                        float z_from_cam = (ShadowCoord.z - bias) / ShadowCoord.w;
                        float is_texel_shadowed = (z_from_cam >=  z_from_light ? 1.0: 0.0);
                        // retrieve the lighting/shadowing contribution of this texel 
                        visibility -= 1.0/nb_samples * is_texel_shadowed;
                    }
                    return visibility;
                }
                

                void main() {
                    float cosTheta = dot(normalize(Light - v_vert), normalize(v_norm));
                    float lum = clamp(cosTheta, 0.0, 1.0) * 0.9 + 0.1;
                    if (UseTexture) {
                        f_color = texture(Texture, v_text);
                    } else {
                        float visibility = compute_shadow_with_poisson_filtering(cosTheta);                 

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

        for name in ['ground', 'grass', 'billboard',
                     'billboard-holder', 'billboard-image']:
            obj = Obj.open(local('data', 'scene-1-%s.obj' % name))

            vbo = self.ctx.buffer(obj.pack('vx vy vz nx ny nz tx ty'))
            vao = self.ctx.simple_vertex_array(self.prog, vbo,
                                               "in_vert", "in_norm", "in_text")
            self.objects[name] = vao

            vbo_shadow = self.ctx.buffer(obj.pack('vx vy vz'))  # only vertices
            vao_shadow = self.ctx.simple_vertex_array(self.prog_shadow,
                                                      vbo_shadow, "in_vert")
            self.objects_shadow[name] = vao_shadow

        img = Image.open(local('data', 'infographic-1.jpg')).transpose(
            Image.FLIP_TOP_BOTTOM).convert('RGB')
        self.texture1 = self.ctx.texture(img.size, 3, img.tobytes())
        self.texture1.build_mipmaps()

        ########################################################################
        shadow_size = tuple([1 << 9] * 2)
        print(f"Depth texture size: {shadow_size}")
        depth_attachment_shadow = self.ctx.depth_renderbuffer(shadow_size)
        self.tex_depth = self.ctx.texture(shadow_size, components=1, dtype='f4')
        self.fbo_shadow = self.ctx.framebuffer(
            color_attachments=[self.tex_depth],
            depth_attachment=depth_attachment_shadow)
        ########################################################################

    def render(self):
        self.ctx.viewport = self.wnd.viewport
        self.ctx.clear(1.0, 1.0, 1.0)
        self.ctx.enable(moderngl.DEPTH_TEST)

        cam_proj = Matrix44.perspective_projection(45.0, self.wnd.ratio,
                                                   1.0, 100.0)
        scene_position = (47.697, -8.147, 24.498)
        cam_lookat = Matrix44.look_at(
            scene_position,
            (0.0, 0.0, 8.0),
            (0.0, 0.0, 1.0),
        )

        # cam_rotate = Matrix44.from_z_rotation(self.wnd.time * 0.5)
        cam_rotate = Matrix44.identity()

        self.mvp.write((cam_proj * cam_lookat * cam_rotate).astype('f4').tobytes())

        light_rotate = Matrix44.from_z_rotation(
            -np.sin(self.wnd.time * 2) * 0.50 + 0.2)
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

        light_proj = Matrix44.perspective_projection(20.0, self.wnd.ratio,
                                                     60.0, 100.0)
        light_lookat = Matrix44.look_at(
            light_pos,
            (0, 0, 0),
            (0.0, 0.0, 1.0),
        )
        depthMVP = light_proj * light_lookat
        depthBiasMVP = bias_matrix * depthMVP
        self.depth_mvp.write(depthBiasMVP.astype('f4').tobytes())
        self.mvp_shadow.write(depthMVP.astype('f4').tobytes())
        self.fbo_shadow.clear(1.0, 1.0, 1.0)
        self.fbo_shadow.use()
        for vao_shadow in self.objects_shadow.values():
            vao_shadow.render()

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


run_example(ShadowMappingWithPoissonFilteringSample)
