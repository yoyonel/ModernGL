"""
Links:
- https://en.wikipedia.org/wiki/Shadow_volume#cite_note-9
- https://web.archive.org/web/20110516024500/http://developer.nvidia.com/node/168
- https://github.com/moderngl/moderngl/issues/323
- https://www.khronos.org/opengl/wiki/Geometry_Shader
- https://www.khronos.org/opengl/wiki/Primitive
- https://learnopengl.com/Advanced-OpenGL/Geometry-Shader
"""

from pyrr import Matrix44
from pyrr import Vector3

import moderngl
#
from ported._example import Example


class ShadowVolumeSample(Example):
    title = "ShadowVolume"
    window_size = (1280, 720)
    gl_version = (3, 3)

    def __init__(self, **kwargs):
        super().__init__(**kwargs)

        self.obj = self.load_scene('sitting_dummy.obj')
        self.texture = self.load_texture_2d('wood.jpg')

        self.prog = self.ctx.program(
            vertex_shader='''
                        #version 330

                        uniform mat4 Mvp;

                        in vec3 in_position;
                        in vec3 in_normal;
                        in vec2 in_texcoord_0;

                        out vec3 v_vert;
                        out vec3 v_norm;
                        out vec2 v_text;

                        void main() {
                            v_vert = in_position;
                            v_norm = in_normal;
                            v_text = in_texcoord_0;
                            gl_Position = Mvp * vec4(in_position, 1.0);
                        }
                    ''',
            fragment_shader='''
                        #version 330

                        uniform sampler2D Texture;
                        uniform vec4 Color;
                        uniform vec3 Light;

                        in vec3 v_vert;
                        in vec3 v_norm;
                        in vec2 v_text;

                        out vec4 f_color;

                        void main() {
                            float lum = dot(normalize(v_norm), normalize(v_vert - Light));
                            lum = acos(lum) / 3.14159265;
                            lum = clamp(lum, 0.0, 1.0);
                            lum = lum * lum;
                            lum = smoothstep(0.0, 1.0, lum);
                            lum *= smoothstep(0.0, 80.0, v_vert.z) * 0.3 + 0.7;
                            lum = lum * 0.8 + 0.2;

                            vec3 color = texture(Texture, v_text).rgb;
                            color = color * (1.0 - Color.a) + Color.rgb * Color.a;
                            f_color = vec4(color * lum, 1.0);
                        }
                    ''',
        )

        self.light = self.prog['Light']
        self.color = self.prog['Color']
        self.mvp = self.prog['Mvp']

        # Create a vao from the first root node (attribs are auto mapped)
        self.vao = self.obj.root_nodes[0].mesh.vao.instance(self.prog)

        self.prog_shadow_edges = self.ctx.program(
            vertex_shader="""
                #version 330

                uniform mat4 u_mv;

                // light position in model/object space
                uniform vec3 u_light;
                
                in vec3 in_position;
                in vec3 in_normal;
                out float cos_theta;
                
                void main() {
                    gl_Position = u_mv * vec4(in_position, 1.0);
                    cos_theta = dot(normalize(u_light - in_position), in_normal);
                }
            """,
            geometry_shader="""
                #version 330

                // light position in model/object space
                uniform vec3 u_light;
                uniform mat4 u_proj;
                uniform float u_cull_face;
                
                // We are taking triangle from vertex shader
                // and an edge
                layout (triangles) in;
                // https://en.wikipedia.org/wiki/Triangle_strip
                layout (triangle_strip, max_vertices = 4) out;
                //layout (line_strip, max_vertices = 2) out;

                // Since geometry shader can take multiple values from a vertex
                // shader we need to define the inputs from it as arrays.
                in float cos_theta[];
                
                out vec4 color;

                void main() {
                    vec3 ns = cross(
                            gl_in[2].gl_Position.xyz - gl_in[0].gl_Position.xyz, 
                            gl_in[1].gl_Position.xyz - gl_in[0].gl_Position.xyz );
                    if(u_cull_face * ns.z >= 0)
                        return;
                    /**
                    if(ns.z < 0) {
                    for(int i=0; i<3; i++) {
                        gl_Position = u_proj * gl_in[i].gl_Position;
                        EmitVertex();
                    }
                    EndPrimitive();
                    }
                    /**/
                    
                    /**/
                    int j = 0;
                    vec4 edge_vertices[2];
                    
                    for(int i=0; i<3; i++)
                    {
                        int id_0 = i % 3;
                        int id_1 = (i + 1) % 3;
                        if(sign(cos_theta[id_0]) != sign(cos_theta[id_1])) {
                            if(cos_theta[id_0] > cos_theta[id_1]) {
                                int tmp = id_0; id_0 = id_1; id_1 = tmp;
                            }
                            float ratio = cos_theta[id_0] / (cos_theta[id_0] - cos_theta[id_1]);
                            // https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/mix.xhtml 
                            edge_vertices[j] = mix(gl_in[id_0].gl_Position, gl_in[id_1].gl_Position, ratio);
                            j += 1;                            
                        }
                    }
                    if(j == 2) {
                        gl_Position = u_proj * edge_vertices[0];
                        EmitVertex();
                        gl_Position = u_proj * (edge_vertices[0] + normalize(vec4(edge_vertices[0].xyz - u_light, 0.0)) * 500.0);
                        EmitVertex();                        
                        gl_Position = u_proj * edge_vertices[1];
                        EmitVertex();
                        gl_Position = u_proj * (edge_vertices[1] + normalize(vec4(edge_vertices[1].xyz - u_light, 0.0)) * 500.0);
                        EmitVertex();
                    }
                    EndPrimitive();
                    /**/
                }
                """,
            fragment_shader="""
                #version 330

                uniform vec4 u_color;

                out vec4 fragColor;

                void main() {
                    fragColor = u_color;
                }
                """,
        )

        self.se_color = self.prog_shadow_edges.get("u_color", None)
        self.se_mv = self.prog_shadow_edges["u_mv"]
        self.se_proj = self.prog_shadow_edges["u_proj"]
        self.se_light = self.prog_shadow_edges.get("u_light", None)
        self.se_cull_face = self.prog_shadow_edges.get("u_cull_face", None)

        self.vao_shadow_edges = self.obj.root_nodes[0].mesh.vao.instance(self.prog_shadow_edges)

        self.ctx.enable(moderngl.CULL_FACE)

    def render(self, time: float, _frame_time: float):
        self.ctx.clear(1.0, 1.0, 1.0)
        self.ctx.enable(moderngl.DEPTH_TEST)

        cam_proj = Matrix44.perspective_projection(45.0, self.aspect_ratio, 0.1, 1000.0)
        cam_pos = (-85, -180, 140)
        cam_look_at = Matrix44.look_at(
            cam_pos,
            (0.0, 0.0, 65.0),
            (0.0, 0.0, 1.0),
        )
        cam_rotate = Matrix44.identity()
        cam_mv = cam_look_at * cam_rotate
        cam_mvp = cam_proj * cam_mv
        self.se_mv.write(cam_mv.astype('f4').tobytes())
        self.se_proj.write(cam_proj.astype('f4').tobytes())
        self.mvp.write(cam_mvp.astype('f4'))

        # build light camera
        light_rotate = Matrix44.from_z_rotation(time)
        light_pos = light_rotate * Vector3(cam_pos)
        if self.se_light:
            self.se_light.value = tuple(light_pos)

        self.ctx.screen.use()

        self.ctx.enable(moderngl.CULL_FACE)
        self.ctx.wireframe = False
        if self.se_light:
            self.light.value = self.se_light.value
        self.color.value = (1.0, 1.0, 1.0, 0.25)
        self.texture.use()
        self.vao.render()

        self.ctx.depth_func = "<="
        moderngl.Framebuffer.depth_mask = False
        self.ctx.enable(moderngl.BLEND)
        # self.ctx.wireframe = True
        self.ctx.disable(moderngl.CULL_FACE)

        # self.ctx.front_face = "cw"
        if self.se_color:
            self.se_color.value = (0.95, 0.1, 0.15, 0.25)
        if self.se_cull_face:
            self.se_cull_face.value = -1
        self.vao_shadow_edges.render()
        #
        # self.ctx.front_face = "ccw"
        if self.se_color:
            self.se_color.value = (0.1, 0.95, 0.15, 0.25)
        if self.se_cull_face:
            self.se_cull_face.value = +1
        self.vao_shadow_edges.render()

        self.ctx.depth_func = "<="
        moderngl.Framebuffer.depth_mask = True


if __name__ == '__main__':
    ShadowVolumeSample.run()
