#pragma once

#include "opengl/opengl.hpp"
#include "opengl/gl_methods.hpp"

namespace MGLBytecode {

enum Opcode {
    OP_glActiveTexture,
    OP_glBeginConditionalRender,
    OP_glBeginQuery,
    OP_glBeginTransformFeedback,
    OP_glBindBuffer,
    OP_glBindBufferBase,
    OP_glBindBufferRange,
    OP_glBindFramebuffer,
    OP_glBindSampler,
    OP_glBindTexture,
    OP_glBindVertexArray,
    OP_glBlendFunc,
    OP_glBufferSubData,
    OP_glClearBufferData,
    OP_glClearBufferfv,
    OP_glClearBufferiv,
    OP_glClearBufferuiv,
    OP_glColorMaski,
    OP_glCopyBufferSubData,
    OP_glDepthMask,
    OP_glDisable,
    OP_glDispatchCompute,
    OP_glDrawArraysInstanced,
    OP_glDrawElementsInstanced,
    OP_glEnable,
    OP_glEndConditionalRender,
    OP_glEndQuery,
    OP_glEndTransformFeedback,
    OP_glFlush,
    OP_glPixelStorei,
    OP_glSamplerParameteri,
    OP_glScissor,
    OP_glTexSubImage2D,
    OP_glTexSubImage3D,
    OP_glUseProgram,
    OP_glViewport,
    OP_glUniform,
};

enum UniformOpcode {
    OP_glUniform1dv,
    OP_glUniform1fv,
    OP_glUniform1iv,
    OP_glUniform1uiv,
    OP_glUniform2dv,
    OP_glUniform2fv,
    OP_glUniform2iv,
    OP_glUniform2uiv,
    OP_glUniform3dv,
    OP_glUniform3fv,
    OP_glUniform3iv,
    OP_glUniform3uiv,
    OP_glUniform4dv,
    OP_glUniform4fv,
    OP_glUniform4iv,
    OP_glUniform4uiv,
    OP_glUniformBlockBinding,
    OP_glUniformMatrix2dv,
    OP_glUniformMatrix2fv,
    OP_glUniformMatrix2x3dv,
    OP_glUniformMatrix2x3fv,
    OP_glUniformMatrix2x4dv,
    OP_glUniformMatrix2x4fv,
    OP_glUniformMatrix3dv,
    OP_glUniformMatrix3fv,
    OP_glUniformMatrix3x2dv,
    OP_glUniformMatrix3x2fv,
    OP_glUniformMatrix3x4dv,
    OP_glUniformMatrix3x4fv,
    OP_glUniformMatrix4dv,
    OP_glUniformMatrix4fv,
    OP_glUniformMatrix4x2dv,
    OP_glUniformMatrix4x2fv,
    OP_glUniformMatrix4x3dv,
    OP_glUniformMatrix4x3fv,
};

extern bool error;
extern char * buffer;
extern char * ptr;
extern GLMethods rec;
extern GLMethods gl;

void GLAPI rec_glActiveTexture(GLenum texture);
void GLAPI rec_glBeginConditionalRender(GLuint id, GLenum mode);
void GLAPI rec_glBeginQuery(GLenum target, GLuint id);
void GLAPI rec_glBeginTransformFeedback(GLenum primitiveMode);
void GLAPI rec_glBindBuffer(GLenum target, GLuint buffer);
void GLAPI rec_glBindBufferBase(GLenum target, GLuint index, GLuint buffer);
void GLAPI rec_glBindBufferRange(GLenum target, GLuint index, GLuint buffer, GLintptr offset, GLsizeiptr size);
void GLAPI rec_glBindFramebuffer(GLenum target, GLuint framebuffer);
void GLAPI rec_glBindSampler(GLuint unit, GLuint sampler);
void GLAPI rec_glBindTexture(GLenum target, GLuint texture);
void GLAPI rec_glBindVertexArray(GLuint array);
void GLAPI rec_glBlendFunc(GLenum sfactor, GLenum dfactor);
void GLAPI rec_glBufferSubData(GLenum target, GLintptr offset, GLsizeiptr size, const void * data);
void GLAPI rec_glClearBufferData(GLenum target, GLenum internalformat, GLenum format, GLenum type, const void * data);
void GLAPI rec_glClearBufferfv(GLenum buffer, GLint drawbuffer, const GLfloat * value);
void GLAPI rec_glClearBufferiv(GLenum buffer, GLint drawbuffer, const GLint * value);
void GLAPI rec_glClearBufferuiv(GLenum buffer, GLint drawbuffer, const GLuint * value);
void GLAPI rec_glColorMaski(GLuint index, GLboolean r, GLboolean g, GLboolean b, GLboolean a);
void GLAPI rec_glCopyBufferSubData(GLenum readTarget, GLenum writeTarget, GLintptr readOffset, GLintptr writeOffset, GLsizeiptr size);
void GLAPI rec_glDepthMask(GLboolean flag);
void GLAPI rec_glDisable(GLenum cap);
void GLAPI rec_glDispatchCompute(GLuint num_groups_x, GLuint num_groups_y, GLuint num_groups_z);
void GLAPI rec_glDrawArraysInstanced(GLenum mode, GLint first, GLsizei count, GLsizei instancecount);
void GLAPI rec_glDrawElementsInstanced(GLenum mode, GLsizei count, GLenum type, const void * indices, GLsizei instancecount);
void GLAPI rec_glEnable(GLenum cap);
void GLAPI rec_glEndConditionalRender();
void GLAPI rec_glEndQuery(GLenum target);
void GLAPI rec_glEndTransformFeedback();
void GLAPI rec_glFlush();
void GLAPI rec_glPixelStorei(GLenum pname, GLint param);
void GLAPI rec_glSamplerParameteri(GLuint sampler, GLenum pname, GLint param);
void GLAPI rec_glScissor(GLint x, GLint y, GLsizei width, GLsizei height);
void GLAPI rec_glTexSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const void * pixels);
void GLAPI rec_glTexSubImage3D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const void * pixels);
void GLAPI rec_glUseProgram(GLuint program);
void GLAPI rec_glViewport(GLint x, GLint y, GLsizei width, GLsizei height);
void GLAPI rec_glUniform1dv(GLint location, GLsizei count, const GLdouble * value);
void GLAPI rec_glUniform1fv(GLint location, GLsizei count, const GLfloat * value);
void GLAPI rec_glUniform1iv(GLint location, GLsizei count, const GLint * value);
void GLAPI rec_glUniform1uiv(GLint location, GLsizei count, const GLuint * value);
void GLAPI rec_glUniform2dv(GLint location, GLsizei count, const GLdouble * value);
void GLAPI rec_glUniform2fv(GLint location, GLsizei count, const GLfloat * value);
void GLAPI rec_glUniform2iv(GLint location, GLsizei count, const GLint * value);
void GLAPI rec_glUniform2uiv(GLint location, GLsizei count, const GLuint * value);
void GLAPI rec_glUniform3dv(GLint location, GLsizei count, const GLdouble * value);
void GLAPI rec_glUniform3fv(GLint location, GLsizei count, const GLfloat * value);
void GLAPI rec_glUniform3iv(GLint location, GLsizei count, const GLint * value);
void GLAPI rec_glUniform3uiv(GLint location, GLsizei count, const GLuint * value);
void GLAPI rec_glUniform4dv(GLint location, GLsizei count, const GLdouble * value);
void GLAPI rec_glUniform4fv(GLint location, GLsizei count, const GLfloat * value);
void GLAPI rec_glUniform4iv(GLint location, GLsizei count, const GLint * value);
void GLAPI rec_glUniform4uiv(GLint location, GLsizei count, const GLuint * value);
void GLAPI rec_glUniformBlockBinding(GLuint program, GLuint uniformBlockIndex, GLuint uniformBlockBinding);
void GLAPI rec_glUniformMatrix2dv(GLint location, GLsizei count, GLboolean transpose, const GLdouble * value);
void GLAPI rec_glUniformMatrix2fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat * value);
void GLAPI rec_glUniformMatrix2x3dv(GLint location, GLsizei count, GLboolean transpose, const GLdouble * value);
void GLAPI rec_glUniformMatrix2x3fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat * value);
void GLAPI rec_glUniformMatrix2x4dv(GLint location, GLsizei count, GLboolean transpose, const GLdouble * value);
void GLAPI rec_glUniformMatrix2x4fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat * value);
void GLAPI rec_glUniformMatrix3dv(GLint location, GLsizei count, GLboolean transpose, const GLdouble * value);
void GLAPI rec_glUniformMatrix3fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat * value);
void GLAPI rec_glUniformMatrix3x2dv(GLint location, GLsizei count, GLboolean transpose, const GLdouble * value);
void GLAPI rec_glUniformMatrix3x2fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat * value);
void GLAPI rec_glUniformMatrix3x4dv(GLint location, GLsizei count, GLboolean transpose, const GLdouble * value);
void GLAPI rec_glUniformMatrix3x4fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat * value);
void GLAPI rec_glUniformMatrix4dv(GLint location, GLsizei count, GLboolean transpose, const GLdouble * value);
void GLAPI rec_glUniformMatrix4fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat * value);
void GLAPI rec_glUniformMatrix4x2dv(GLint location, GLsizei count, GLboolean transpose, const GLdouble * value);
void GLAPI rec_glUniformMatrix4x2fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat * value);
void GLAPI rec_glUniformMatrix4x3dv(GLint location, GLsizei count, GLboolean transpose, const GLdouble * value);
void GLAPI rec_glUniformMatrix4x3fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat * value);
void GLAPI rec_glGetQueryObjectiv(GLuint id, GLenum pname, GLint * params);
void GLAPI rec_glAttachShader(GLuint program, GLuint shader);
void GLAPI rec_glBindRenderbuffer(GLenum target, GLuint renderbuffer);
void GLAPI rec_glBufferData(GLenum target, GLsizeiptr size, const void * data, GLenum usage);
void GLAPI rec_glBufferStorage(GLenum target, GLsizeiptr size, const void * data, GLbitfield flags);
GLenum GLAPI rec_glCheckFramebufferStatus(GLenum target);
void GLAPI rec_glCompileShader(GLuint shader);
GLuint GLAPI rec_glCreateShader(GLenum type);
void GLAPI rec_glDeleteBuffers(GLsizei n, const GLuint * buffers);
void GLAPI rec_glDeleteFramebuffers(GLsizei n, const GLuint * framebuffers);
void GLAPI rec_glDeleteProgram(GLuint program);
void GLAPI rec_glDeleteQueries(GLsizei n, const GLuint * ids);
void GLAPI rec_glDeleteRenderbuffers(GLsizei n, const GLuint * renderbuffers);
void GLAPI rec_glDeleteSamplers(GLsizei count, const GLuint * samplers);
void GLAPI rec_glDeleteShader(GLuint shader);
void GLAPI rec_glDeleteTextures(GLsizei n, const GLuint * textures);
void GLAPI rec_glDeleteVertexArrays(GLsizei n, const GLuint * arrays);
void GLAPI rec_glEnableVertexAttribArray(GLuint index);
void GLAPI rec_glFramebufferRenderbuffer(GLenum target, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer);
void GLAPI rec_glFramebufferTexture2D(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level);
void GLAPI rec_glGenBuffers(GLsizei n, GLuint * buffers);
void GLAPI rec_glGenFramebuffers(GLsizei n, GLuint * framebuffers);
void GLAPI rec_glGenQueries(GLsizei n, GLuint * ids);
void GLAPI rec_glGenRenderbuffers(GLsizei n, GLuint * renderbuffers);
void GLAPI rec_glGenSamplers(GLsizei count, GLuint * samplers);
void GLAPI rec_glGenTextures(GLsizei n, GLuint * textures);
void GLAPI rec_glGenVertexArrays(GLsizei n, GLuint * arrays);
void GLAPI rec_glGetActiveAttrib(GLuint program, GLuint index, GLsizei bufSize, GLsizei * length, GLint * size, GLenum * type, GLchar * name);
void GLAPI rec_glGetActiveUniform(GLuint program, GLuint index, GLsizei bufSize, GLsizei * length, GLint * size, GLenum * type, GLchar * name);
void GLAPI rec_glGetActiveUniformBlockName(GLuint program, GLuint uniformBlockIndex, GLsizei bufSize, GLsizei * length, GLchar * uniformBlockName);
void GLAPI rec_glGetActiveUniformBlockiv(GLuint program, GLuint uniformBlockIndex, GLenum pname, GLint * params);
GLint GLAPI rec_glGetAttribLocation(GLuint program, const GLchar * name);
void GLAPI rec_glGetFloatv(GLenum pname, GLfloat * data);
void GLAPI rec_glGetInteger64v(GLenum pname, GLint64 * data);
void GLAPI rec_glGetIntegeri_v(GLenum target, GLuint index, GLint * data);
void GLAPI rec_glGetIntegerv(GLenum pname, GLint * data);
void GLAPI rec_glGetProgramInfoLog(GLuint program, GLsizei bufSize, GLsizei * length, GLchar * infoLog);
void GLAPI rec_glGetProgramiv(GLuint program, GLenum pname, GLint * params);
void GLAPI rec_glGetShaderInfoLog(GLuint shader, GLsizei bufSize, GLsizei * length, GLchar * infoLog);
void GLAPI rec_glGetShaderiv(GLuint shader, GLenum pname, GLint * params);
const GLubyte * GLAPI rec_glGetString(GLenum name);
const GLubyte * GLAPI rec_glGetStringi(GLenum name, GLuint index);
GLuint GLAPI rec_glGetUniformBlockIndex(GLuint program, const GLchar * uniformBlockName);
GLint GLAPI rec_glGetUniformLocation(GLuint program, const GLchar * name);
void GLAPI rec_glGetUniformdv(GLuint program, GLint location, GLdouble * params);
void GLAPI rec_glGetUniformfv(GLuint program, GLint location, GLfloat * params);
void GLAPI rec_glGetUniformiv(GLuint program, GLint location, GLint * params);
void GLAPI rec_glGetUniformuiv(GLuint program, GLint location, GLuint * params);
void GLAPI rec_glLinkProgram(GLuint program);
void * GLAPI rec_glMapBuffer(GLenum target, GLenum access);
void * GLAPI rec_glMapBufferRange(GLenum target, GLintptr offset, GLsizeiptr length, GLbitfield access);
void GLAPI rec_glPrimitiveRestartIndex(GLuint index);
void GLAPI rec_glReadBuffer(GLenum src);
void GLAPI rec_glReadPixels(GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, void * pixels);
void GLAPI rec_glRenderbufferStorage(GLenum target, GLenum internalformat, GLsizei width, GLsizei height);
void GLAPI rec_glRenderbufferStorageMultisample(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height);
void GLAPI rec_glShaderSource(GLuint shader, GLsizei count, const GLchar * const * string, const GLint * length);
void GLAPI rec_glTexImage2D(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const void * pixels);
void GLAPI rec_glTexImage2DMultisample(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLboolean fixedsamplelocations);
void GLAPI rec_glTexImage3D(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLenum format, GLenum type, const void * pixels);
void GLAPI rec_glTexStorage2D(GLenum target, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height);
void GLAPI rec_glTexStorage3D(GLenum target, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth);
void GLAPI rec_glTransformFeedbackVaryings(GLuint program, GLsizei count, const GLchar * const * varyings, GLenum bufferMode);
GLboolean GLAPI rec_glUnmapBuffer(GLenum target);
void GLAPI rec_glVertexAttribDivisor(GLuint index, GLuint divisor);
void GLAPI rec_glVertexAttribIPointer(GLuint index, GLint size, GLenum type, GLsizei stride, const void * pointer);
void GLAPI rec_glVertexAttribLPointer(GLuint index, GLint size, GLenum type, GLsizei stride, const void * pointer);
void GLAPI rec_glVertexAttribPointer(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void * pointer);

void evaluate(int size);
void init();

}
