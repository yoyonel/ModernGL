#pragma once

#include "OpenGL.hpp"

#ifdef MGL_DEBUG
#include <cstdio>
#define GLMethods GLMethodsDebugImpl
#define MGL_GLMETHOD_DBG_UNIFORM_READER(...)
#define MGL_GLMETHOD_DBG_UNIFORM_WRITER(...)
#define MGL_GLMETHOD_DBG_ATTRIB_NORM_PTR(...)
#define MGL_GLMETHOD_DBG_ATTRIB_PTR(...)
// #define MGL_GLMETHOD_DBG_UNIFORM_READER GLMethodsDebug_uniform_reader
// #define MGL_GLMETHOD_DBG_UNIFORM_WRITER GLMethodsDebug_uniform_writer
// #define MGL_GLMETHOD_DBG_ATTRIB_NORM_PTR GLMethodsDebug_attrib_norm_ptr
// #define MGL_GLMETHOD_DBG_ATTRIB_PTR GLMethodsDebug_attrib_ptr
#else
#define GLMethods GLMethodsImpl
#define MGL_GLMETHOD_DBG_UNIFORM_READER(...)
#define MGL_GLMETHOD_DBG_UNIFORM_WRITER(...)
#define MGL_GLMETHOD_DBG_ATTRIB_NORM_PTR(...)
#define MGL_GLMETHOD_DBG_ATTRIB_PTR(...)
#endif

#if defined(__x86_64__) || defined(_WIN64)
#define LL "ll"
#else
#define LL ""
#endif

typedef GLvoid (GLAPI * gl_attribute_normal_ptr_proc)(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid * pointer);
typedef GLvoid (GLAPI * gl_attribute_ptr_proc)(GLuint index, GLint size, GLenum type, GLsizei stride, const GLvoid * pointer);

struct GLMethodsImpl {
	PROC_glActiveShaderProgram ActiveShaderProgram;
	PROC_glActiveTexture ActiveTexture;
	PROC_glAttachShader AttachShader;
	PROC_glBeginConditionalRender BeginConditionalRender;
	PROC_glBeginQuery BeginQuery;
	PROC_glBeginQueryIndexed BeginQueryIndexed;
	PROC_glBeginTransformFeedback BeginTransformFeedback;
	PROC_glBindAttribLocation BindAttribLocation;
	PROC_glBindBuffer BindBuffer;
	PROC_glBindBufferBase BindBufferBase;
	PROC_glBindBufferRange BindBufferRange;
	PROC_glBindBuffersBase BindBuffersBase;
	PROC_glBindBuffersRange BindBuffersRange;
	PROC_glBindFragDataLocation BindFragDataLocation;
	PROC_glBindFragDataLocationIndexed BindFragDataLocationIndexed;
	PROC_glBindFramebuffer BindFramebuffer;
	PROC_glBindImageTexture BindImageTexture;
	PROC_glBindImageTextures BindImageTextures;
	PROC_glBindProgramPipeline BindProgramPipeline;
	PROC_glBindRenderbuffer BindRenderbuffer;
	PROC_glBindSampler BindSampler;
	PROC_glBindSamplers BindSamplers;
	PROC_glBindTexture BindTexture;
	PROC_glBindTextureUnit BindTextureUnit;
	PROC_glBindTextures BindTextures;
	PROC_glBindTransformFeedback BindTransformFeedback;
	PROC_glBindVertexArray BindVertexArray;
	PROC_glBindVertexBuffer BindVertexBuffer;
	PROC_glBindVertexBuffers BindVertexBuffers;
	PROC_glBlendColor BlendColor;
	PROC_glBlendEquation BlendEquation;
	PROC_glBlendEquationSeparate BlendEquationSeparate;
	PROC_glBlendEquationSeparatei BlendEquationSeparatei;
	PROC_glBlendEquationi BlendEquationi;
	PROC_glBlendFunc BlendFunc;
	PROC_glBlendFuncSeparate BlendFuncSeparate;
	PROC_glBlendFuncSeparatei BlendFuncSeparatei;
	PROC_glBlendFunci BlendFunci;
	PROC_glBlitFramebuffer BlitFramebuffer;
	PROC_glBlitNamedFramebuffer BlitNamedFramebuffer;
	PROC_glBufferData BufferData;
	PROC_glBufferStorage BufferStorage;
	PROC_glBufferSubData BufferSubData;
	PROC_glCheckFramebufferStatus CheckFramebufferStatus;
	PROC_glCheckNamedFramebufferStatus CheckNamedFramebufferStatus;
	PROC_glClampColor ClampColor;
	PROC_glClear Clear;
	PROC_glClearBufferData ClearBufferData;
	PROC_glClearBufferSubData ClearBufferSubData;
	PROC_glClearBufferfi ClearBufferfi;
	PROC_glClearBufferfv ClearBufferfv;
	PROC_glClearBufferiv ClearBufferiv;
	PROC_glClearBufferuiv ClearBufferuiv;
	PROC_glClearColor ClearColor;
	PROC_glClearDepth ClearDepth;
	PROC_glClearDepthf ClearDepthf;
	PROC_glClearNamedBufferData ClearNamedBufferData;
	PROC_glClearNamedBufferSubData ClearNamedBufferSubData;
	PROC_glClearNamedFramebufferfi ClearNamedFramebufferfi;
	PROC_glClearNamedFramebufferfv ClearNamedFramebufferfv;
	PROC_glClearNamedFramebufferiv ClearNamedFramebufferiv;
	PROC_glClearNamedFramebufferuiv ClearNamedFramebufferuiv;
	PROC_glClearStencil ClearStencil;
	PROC_glClearTexImage ClearTexImage;
	PROC_glClearTexSubImage ClearTexSubImage;
	PROC_glClientWaitSync ClientWaitSync;
	PROC_glWaitSync WaitSync;
	PROC_glClipControl ClipControl;
	PROC_glColorMask ColorMask;
	PROC_glColorMaski ColorMaski;
	PROC_glCompileShader CompileShader;
	PROC_glCompressedTexImage1D CompressedTexImage1D;
	PROC_glCompressedTexImage2D CompressedTexImage2D;
	PROC_glCompressedTexImage3D CompressedTexImage3D;
	PROC_glCompressedTexSubImage1D CompressedTexSubImage1D;
	PROC_glCompressedTexSubImage2D CompressedTexSubImage2D;
	PROC_glCompressedTexSubImage3D CompressedTexSubImage3D;
	PROC_glCompressedTextureSubImage1D CompressedTextureSubImage1D;
	PROC_glCompressedTextureSubImage2D CompressedTextureSubImage2D;
	PROC_glCompressedTextureSubImage3D CompressedTextureSubImage3D;
	PROC_glCopyBufferSubData CopyBufferSubData;
	PROC_glCopyImageSubData CopyImageSubData;
	PROC_glCopyNamedBufferSubData CopyNamedBufferSubData;
	PROC_glCopyTexImage1D CopyTexImage1D;
	PROC_glCopyTexImage2D CopyTexImage2D;
	PROC_glCopyTexSubImage1D CopyTexSubImage1D;
	PROC_glCopyTexSubImage2D CopyTexSubImage2D;
	PROC_glCopyTexSubImage3D CopyTexSubImage3D;
	PROC_glCopyTextureSubImage1D CopyTextureSubImage1D;
	PROC_glCopyTextureSubImage2D CopyTextureSubImage2D;
	PROC_glCopyTextureSubImage3D CopyTextureSubImage3D;
	PROC_glCreateBuffers CreateBuffers;
	PROC_glCreateFramebuffers CreateFramebuffers;
	PROC_glCreateProgram CreateProgram;
	PROC_glCreateProgramPipelines CreateProgramPipelines;
	PROC_glCreateQueries CreateQueries;
	PROC_glCreateRenderbuffers CreateRenderbuffers;
	PROC_glCreateSamplers CreateSamplers;
	PROC_glCreateShader CreateShader;
	PROC_glCreateShaderProgramv CreateShaderProgramv;
	PROC_glCreateTextures CreateTextures;
	PROC_glCreateTransformFeedbacks CreateTransformFeedbacks;
	PROC_glCreateVertexArrays CreateVertexArrays;
	PROC_glCullFace CullFace;
	PROC_glDebugMessageCallback DebugMessageCallback;
	PROC_glDebugMessageControl DebugMessageControl;
	PROC_glDebugMessageInsert DebugMessageInsert;
	PROC_glDeleteBuffers DeleteBuffers;
	PROC_glDeleteFramebuffers DeleteFramebuffers;
	PROC_glDeleteProgram DeleteProgram;
	PROC_glDeleteProgramPipelines DeleteProgramPipelines;
	PROC_glDeleteQueries DeleteQueries;
	PROC_glDeleteRenderbuffers DeleteRenderbuffers;
	PROC_glDeleteSamplers DeleteSamplers;
	PROC_glDeleteShader DeleteShader;
	PROC_glDeleteSync DeleteSync;
	PROC_glDeleteTextures DeleteTextures;
	PROC_glDeleteTransformFeedbacks DeleteTransformFeedbacks;
	PROC_glDeleteVertexArrays DeleteVertexArrays;
	PROC_glDepthFunc DepthFunc;
	PROC_glDepthMask DepthMask;
	PROC_glDepthRange DepthRange;
	PROC_glDepthRangeArrayv DepthRangeArrayv;
	PROC_glDepthRangeIndexed DepthRangeIndexed;
	PROC_glDepthRangef DepthRangef;
	PROC_glDetachShader DetachShader;
	PROC_glDisable Disable;
	PROC_glDisableVertexArrayAttrib DisableVertexArrayAttrib;
	PROC_glDisableVertexAttribArray DisableVertexAttribArray;
	PROC_glDisablei Disablei;
	PROC_glDispatchCompute DispatchCompute;
	PROC_glDispatchComputeIndirect DispatchComputeIndirect;
	PROC_glDrawArrays DrawArrays;
	PROC_glDrawArraysIndirect DrawArraysIndirect;
	PROC_glDrawArraysInstanced DrawArraysInstanced;
	PROC_glDrawArraysInstancedBaseInstance DrawArraysInstancedBaseInstance;
	PROC_glDrawBuffer DrawBuffer;
	PROC_glDrawBuffers DrawBuffers;
	PROC_glDrawElements DrawElements;
	PROC_glDrawElementsBaseVertex DrawElementsBaseVertex;
	PROC_glDrawElementsIndirect DrawElementsIndirect;
	PROC_glDrawElementsInstanced DrawElementsInstanced;
	PROC_glDrawElementsInstancedBaseInstance DrawElementsInstancedBaseInstance;
	PROC_glDrawElementsInstancedBaseVertex DrawElementsInstancedBaseVertex;
	PROC_glDrawElementsInstancedBaseVertexBaseInstance DrawElementsInstancedBaseVertexBaseInstance;
	PROC_glDrawRangeElements DrawRangeElements;
	PROC_glDrawRangeElementsBaseVertex DrawRangeElementsBaseVertex;
	PROC_glDrawTransformFeedback DrawTransformFeedback;
	PROC_glDrawTransformFeedbackInstanced DrawTransformFeedbackInstanced;
	PROC_glDrawTransformFeedbackStream DrawTransformFeedbackStream;
	PROC_glDrawTransformFeedbackStreamInstanced DrawTransformFeedbackStreamInstanced;
	PROC_glEnable Enable;
	PROC_glEnableVertexArrayAttrib EnableVertexArrayAttrib;
	PROC_glEnableVertexAttribArray EnableVertexAttribArray;
	PROC_glEnablei Enablei;
	PROC_glEndConditionalRender EndConditionalRender;
	PROC_glEndQuery EndQuery;
	PROC_glEndQueryIndexed EndQueryIndexed;
	PROC_glEndTransformFeedback EndTransformFeedback;
	PROC_glFenceSync FenceSync;
	PROC_glFinish Finish;
	PROC_glFlush Flush;
	PROC_glFlushMappedBufferRange FlushMappedBufferRange;
	PROC_glFlushMappedNamedBufferRange FlushMappedNamedBufferRange;
	PROC_glFramebufferParameteri FramebufferParameteri;
	PROC_glFramebufferRenderbuffer FramebufferRenderbuffer;
	PROC_glFramebufferTexture FramebufferTexture;
	PROC_glFramebufferTexture1D FramebufferTexture1D;
	PROC_glFramebufferTexture2D FramebufferTexture2D;
	PROC_glFramebufferTexture3D FramebufferTexture3D;
	PROC_glFramebufferTextureLayer FramebufferTextureLayer;
	PROC_glFrontFace FrontFace;
	PROC_glGenBuffers GenBuffers;
	PROC_glGenFramebuffers GenFramebuffers;
	PROC_glGenProgramPipelines GenProgramPipelines;
	PROC_glGenQueries GenQueries;
	PROC_glGenRenderbuffers GenRenderbuffers;
	PROC_glGenSamplers GenSamplers;
	PROC_glGenTextures GenTextures;
	PROC_glGenTransformFeedbacks GenTransformFeedbacks;
	PROC_glGenVertexArrays GenVertexArrays;
	PROC_glGenerateMipmap GenerateMipmap;
	PROC_glGenerateTextureMipmap GenerateTextureMipmap;
	PROC_glGetActiveAtomicCounterBufferiv GetActiveAtomicCounterBufferiv;
	PROC_glGetActiveAttrib GetActiveAttrib;
	PROC_glGetActiveSubroutineName GetActiveSubroutineName;
	PROC_glGetActiveSubroutineUniformName GetActiveSubroutineUniformName;
	PROC_glGetActiveSubroutineUniformiv GetActiveSubroutineUniformiv;
	PROC_glGetActiveUniform GetActiveUniform;
	PROC_glGetActiveUniformBlockName GetActiveUniformBlockName;
	PROC_glGetActiveUniformBlockiv GetActiveUniformBlockiv;
	PROC_glGetActiveUniformName GetActiveUniformName;
	PROC_glGetActiveUniformsiv GetActiveUniformsiv;
	PROC_glGetAttachedShaders GetAttachedShaders;
	PROC_glGetAttribLocation GetAttribLocation;
	PROC_glGetBooleani_v GetBooleani_v;
	PROC_glGetBooleanv GetBooleanv;
	PROC_glGetBufferParameteri64v GetBufferParameteri64v;
	PROC_glGetBufferParameteriv GetBufferParameteriv;
	PROC_glGetBufferPointerv GetBufferPointerv;
	PROC_glGetBufferSubData GetBufferSubData;
	PROC_glGetCompressedTexImage GetCompressedTexImage;
	PROC_glGetCompressedTextureImage GetCompressedTextureImage;
	PROC_glGetCompressedTextureSubImage GetCompressedTextureSubImage;
	PROC_glGetDebugMessageLog GetDebugMessageLog;
	PROC_glGetDoublei_v GetDoublei_v;
	PROC_glGetDoublev GetDoublev;
	PROC_glGetError GetError;
	PROC_glGetFloati_v GetFloati_v;
	PROC_glGetFloatv GetFloatv;
	PROC_glGetFragDataIndex GetFragDataIndex;
	PROC_glGetFragDataLocation GetFragDataLocation;
	PROC_glGetFramebufferAttachmentParameteriv GetFramebufferAttachmentParameteriv;
	PROC_glGetFramebufferParameteriv GetFramebufferParameteriv;
	PROC_glGetGraphicsResetStatus GetGraphicsResetStatus;
	PROC_glGetInteger64i_v GetInteger64i_v;
	PROC_glGetInteger64v GetInteger64v;
	PROC_glGetIntegeri_v GetIntegeri_v;
	PROC_glGetIntegerv GetIntegerv;
	PROC_glGetInternalformati64v GetInternalformati64v;
	PROC_glGetInternalformativ GetInternalformativ;
	PROC_glGetMultisamplefv GetMultisamplefv;
	PROC_glGetNamedBufferParameteri64v GetNamedBufferParameteri64v;
	PROC_glGetNamedBufferParameteriv GetNamedBufferParameteriv;
	PROC_glGetNamedBufferPointerv GetNamedBufferPointerv;
	PROC_glGetNamedBufferSubData GetNamedBufferSubData;
	PROC_glGetNamedFramebufferAttachmentParameteriv GetNamedFramebufferAttachmentParameteriv;
	PROC_glGetNamedFramebufferParameteriv GetNamedFramebufferParameteriv;
	PROC_glGetNamedRenderbufferParameteriv GetNamedRenderbufferParameteriv;
	PROC_glGetObjectLabel GetObjectLabel;
	PROC_glGetObjectPtrLabel GetObjectPtrLabel;
	PROC_glGetPointerv GetPointerv;
	PROC_glGetProgramBinary GetProgramBinary;
	PROC_glGetProgramInfoLog GetProgramInfoLog;
	PROC_glGetProgramInterfaceiv GetProgramInterfaceiv;
	PROC_glGetProgramPipelineInfoLog GetProgramPipelineInfoLog;
	PROC_glGetProgramPipelineiv GetProgramPipelineiv;
	PROC_glGetProgramResourceIndex GetProgramResourceIndex;
	PROC_glGetProgramResourceLocation GetProgramResourceLocation;
	PROC_glGetProgramResourceLocationIndex GetProgramResourceLocationIndex;
	PROC_glGetProgramResourceName GetProgramResourceName;
	PROC_glGetProgramResourceiv GetProgramResourceiv;
	PROC_glGetProgramStageiv GetProgramStageiv;
	PROC_glGetProgramiv GetProgramiv;
	PROC_glGetQueryBufferObjecti64v GetQueryBufferObjecti64v;
	PROC_glGetQueryBufferObjectiv GetQueryBufferObjectiv;
	PROC_glGetQueryBufferObjectui64v GetQueryBufferObjectui64v;
	PROC_glGetQueryBufferObjectuiv GetQueryBufferObjectuiv;
	PROC_glGetQueryIndexediv GetQueryIndexediv;
	PROC_glGetQueryObjecti64v GetQueryObjecti64v;
	PROC_glGetQueryObjectiv GetQueryObjectiv;
	PROC_glGetQueryObjectui64v GetQueryObjectui64v;
	PROC_glGetQueryObjectuiv GetQueryObjectuiv;
	PROC_glGetQueryiv GetQueryiv;
	PROC_glGetRenderbufferParameteriv GetRenderbufferParameteriv;
	PROC_glGetSamplerParameterIiv GetSamplerParameterIiv;
	PROC_glGetSamplerParameterIuiv GetSamplerParameterIuiv;
	PROC_glGetSamplerParameterfv GetSamplerParameterfv;
	PROC_glGetSamplerParameteriv GetSamplerParameteriv;
	PROC_glGetShaderInfoLog GetShaderInfoLog;
	PROC_glGetShaderPrecisionFormat GetShaderPrecisionFormat;
	PROC_glGetShaderSource GetShaderSource;
	PROC_glGetShaderiv GetShaderiv;
	PROC_glGetString GetString;
	PROC_glGetStringi GetStringi;
	PROC_glGetSubroutineIndex GetSubroutineIndex;
	PROC_glGetSubroutineUniformLocation GetSubroutineUniformLocation;
	PROC_glGetSynciv GetSynciv;
	PROC_glGetTexImage GetTexImage;
	PROC_glGetTexLevelParameterfv GetTexLevelParameterfv;
	PROC_glGetTexLevelParameteriv GetTexLevelParameteriv;
	PROC_glGetTexParameterIiv GetTexParameterIiv;
	PROC_glGetTexParameterIuiv GetTexParameterIuiv;
	PROC_glGetTexParameterfv GetTexParameterfv;
	PROC_glGetTexParameteriv GetTexParameteriv;
	PROC_glGetTextureImage GetTextureImage;
	PROC_glGetTextureLevelParameterfv GetTextureLevelParameterfv;
	PROC_glGetTextureLevelParameteriv GetTextureLevelParameteriv;
	PROC_glGetTextureParameterIiv GetTextureParameterIiv;
	PROC_glGetTextureParameterIuiv GetTextureParameterIuiv;
	PROC_glGetTextureParameterfv GetTextureParameterfv;
	PROC_glGetTextureParameteriv GetTextureParameteriv;
	PROC_glGetTextureSubImage GetTextureSubImage;
	PROC_glGetTransformFeedbackVarying GetTransformFeedbackVarying;
	PROC_glGetTransformFeedbacki64_v GetTransformFeedbacki64_v;
	PROC_glGetTransformFeedbacki_v GetTransformFeedbacki_v;
	PROC_glGetTransformFeedbackiv GetTransformFeedbackiv;
	PROC_glGetUniformBlockIndex GetUniformBlockIndex;
	PROC_glGetUniformIndices GetUniformIndices;
	PROC_glGetUniformLocation GetUniformLocation;
	PROC_glGetUniformSubroutineuiv GetUniformSubroutineuiv;
	PROC_glGetUniformdv GetUniformdv;
	PROC_glGetUniformfv GetUniformfv;
	PROC_glGetUniformiv GetUniformiv;
	PROC_glGetUniformuiv GetUniformuiv;
	PROC_glGetVertexArrayIndexed64iv GetVertexArrayIndexed64iv;
	PROC_glGetVertexArrayIndexediv GetVertexArrayIndexediv;
	PROC_glGetVertexArrayiv GetVertexArrayiv;
	PROC_glGetVertexAttribIiv GetVertexAttribIiv;
	PROC_glGetVertexAttribIuiv GetVertexAttribIuiv;
	PROC_glGetVertexAttribLdv GetVertexAttribLdv;
	PROC_glGetVertexAttribPointerv GetVertexAttribPointerv;
	PROC_glGetVertexAttribdv GetVertexAttribdv;
	PROC_glGetVertexAttribfv GetVertexAttribfv;
	PROC_glGetVertexAttribiv GetVertexAttribiv;
	PROC_glGetnCompressedTexImage GetnCompressedTexImage;
	PROC_glGetnTexImage GetnTexImage;
	PROC_glGetnUniformdv GetnUniformdv;
	PROC_glGetnUniformfv GetnUniformfv;
	PROC_glGetnUniformiv GetnUniformiv;
	PROC_glGetnUniformuiv GetnUniformuiv;
	PROC_glHint Hint;
	PROC_glInvalidateBufferData InvalidateBufferData;
	PROC_glInvalidateBufferSubData InvalidateBufferSubData;
	PROC_glInvalidateFramebuffer InvalidateFramebuffer;
	PROC_glInvalidateNamedFramebufferData InvalidateNamedFramebufferData;
	PROC_glInvalidateNamedFramebufferSubData InvalidateNamedFramebufferSubData;
	PROC_glInvalidateSubFramebuffer InvalidateSubFramebuffer;
	PROC_glInvalidateTexImage InvalidateTexImage;
	PROC_glInvalidateTexSubImage InvalidateTexSubImage;
	PROC_glIsBuffer IsBuffer;
	PROC_glIsEnabled IsEnabled;
	PROC_glIsEnabledi IsEnabledi;
	PROC_glIsFramebuffer IsFramebuffer;
	PROC_glIsProgram IsProgram;
	PROC_glIsProgramPipeline IsProgramPipeline;
	PROC_glIsQuery IsQuery;
	PROC_glIsRenderbuffer IsRenderbuffer;
	PROC_glIsSampler IsSampler;
	PROC_glIsShader IsShader;
	PROC_glIsSync IsSync;
	PROC_glIsTexture IsTexture;
	PROC_glIsTransformFeedback IsTransformFeedback;
	PROC_glIsVertexArray IsVertexArray;
	PROC_glLineWidth LineWidth;
	PROC_glLinkProgram LinkProgram;
	PROC_glLogicOp LogicOp;
	PROC_glMapBuffer MapBuffer;
	PROC_glMapBufferRange MapBufferRange;
	PROC_glMapNamedBuffer MapNamedBuffer;
	PROC_glMapNamedBufferRange MapNamedBufferRange;
	PROC_glMemoryBarrier MemoryBarrier;
	PROC_glMemoryBarrierByRegion MemoryBarrierByRegion;
	PROC_glMinSampleShading MinSampleShading;
	PROC_glMultiDrawArrays MultiDrawArrays;
	PROC_glMultiDrawArraysIndirect MultiDrawArraysIndirect;
	PROC_glMultiDrawElements MultiDrawElements;
	PROC_glMultiDrawElementsBaseVertex MultiDrawElementsBaseVertex;
	PROC_glMultiDrawElementsIndirect MultiDrawElementsIndirect;
	PROC_glNamedBufferData NamedBufferData;
	PROC_glNamedBufferStorage NamedBufferStorage;
	PROC_glNamedBufferSubData NamedBufferSubData;
	PROC_glNamedFramebufferDrawBuffer NamedFramebufferDrawBuffer;
	PROC_glNamedFramebufferDrawBuffers NamedFramebufferDrawBuffers;
	PROC_glNamedFramebufferParameteri NamedFramebufferParameteri;
	PROC_glNamedFramebufferReadBuffer NamedFramebufferReadBuffer;
	PROC_glNamedFramebufferRenderbuffer NamedFramebufferRenderbuffer;
	PROC_glNamedFramebufferTexture NamedFramebufferTexture;
	PROC_glNamedFramebufferTextureLayer NamedFramebufferTextureLayer;
	PROC_glNamedRenderbufferStorage NamedRenderbufferStorage;
	PROC_glNamedRenderbufferStorageMultisample NamedRenderbufferStorageMultisample;
	PROC_glObjectLabel ObjectLabel;
	PROC_glObjectPtrLabel ObjectPtrLabel;
	PROC_glPatchParameterfv PatchParameterfv;
	PROC_glPatchParameteri PatchParameteri;
	PROC_glPauseTransformFeedback PauseTransformFeedback;
	PROC_glPixelStoref PixelStoref;
	PROC_glPixelStorei PixelStorei;
	PROC_glPointParameterf PointParameterf;
	PROC_glPointParameterfv PointParameterfv;
	PROC_glPointParameteri PointParameteri;
	PROC_glPointParameteriv PointParameteriv;
	PROC_glPointSize PointSize;
	PROC_glPolygonMode PolygonMode;
	PROC_glPolygonOffset PolygonOffset;
	PROC_glPopDebugGroup PopDebugGroup;
	PROC_glPrimitiveRestartIndex PrimitiveRestartIndex;
	PROC_glProgramBinary ProgramBinary;
	PROC_glProgramParameteri ProgramParameteri;
	PROC_glProgramUniform1d ProgramUniform1d;
	PROC_glProgramUniform1dv ProgramUniform1dv;
	PROC_glProgramUniform1f ProgramUniform1f;
	PROC_glProgramUniform1fv ProgramUniform1fv;
	PROC_glProgramUniform1i ProgramUniform1i;
	PROC_glProgramUniform1iv ProgramUniform1iv;
	PROC_glProgramUniform1ui ProgramUniform1ui;
	PROC_glProgramUniform1uiv ProgramUniform1uiv;
	PROC_glProgramUniform2d ProgramUniform2d;
	PROC_glProgramUniform2dv ProgramUniform2dv;
	PROC_glProgramUniform2f ProgramUniform2f;
	PROC_glProgramUniform2fv ProgramUniform2fv;
	PROC_glProgramUniform2i ProgramUniform2i;
	PROC_glProgramUniform2iv ProgramUniform2iv;
	PROC_glProgramUniform2ui ProgramUniform2ui;
	PROC_glProgramUniform2uiv ProgramUniform2uiv;
	PROC_glProgramUniform3d ProgramUniform3d;
	PROC_glProgramUniform3dv ProgramUniform3dv;
	PROC_glProgramUniform3f ProgramUniform3f;
	PROC_glProgramUniform3fv ProgramUniform3fv;
	PROC_glProgramUniform3i ProgramUniform3i;
	PROC_glProgramUniform3iv ProgramUniform3iv;
	PROC_glProgramUniform3ui ProgramUniform3ui;
	PROC_glProgramUniform3uiv ProgramUniform3uiv;
	PROC_glProgramUniform4d ProgramUniform4d;
	PROC_glProgramUniform4dv ProgramUniform4dv;
	PROC_glProgramUniform4f ProgramUniform4f;
	PROC_glProgramUniform4fv ProgramUniform4fv;
	PROC_glProgramUniform4i ProgramUniform4i;
	PROC_glProgramUniform4iv ProgramUniform4iv;
	PROC_glProgramUniform4ui ProgramUniform4ui;
	PROC_glProgramUniform4uiv ProgramUniform4uiv;
	PROC_glProgramUniformMatrix2dv ProgramUniformMatrix2dv;
	PROC_glProgramUniformMatrix2fv ProgramUniformMatrix2fv;
	PROC_glProgramUniformMatrix2x3dv ProgramUniformMatrix2x3dv;
	PROC_glProgramUniformMatrix2x3fv ProgramUniformMatrix2x3fv;
	PROC_glProgramUniformMatrix2x4dv ProgramUniformMatrix2x4dv;
	PROC_glProgramUniformMatrix2x4fv ProgramUniformMatrix2x4fv;
	PROC_glProgramUniformMatrix3dv ProgramUniformMatrix3dv;
	PROC_glProgramUniformMatrix3fv ProgramUniformMatrix3fv;
	PROC_glProgramUniformMatrix3x2dv ProgramUniformMatrix3x2dv;
	PROC_glProgramUniformMatrix3x2fv ProgramUniformMatrix3x2fv;
	PROC_glProgramUniformMatrix3x4dv ProgramUniformMatrix3x4dv;
	PROC_glProgramUniformMatrix3x4fv ProgramUniformMatrix3x4fv;
	PROC_glProgramUniformMatrix4dv ProgramUniformMatrix4dv;
	PROC_glProgramUniformMatrix4fv ProgramUniformMatrix4fv;
	PROC_glProgramUniformMatrix4x2dv ProgramUniformMatrix4x2dv;
	PROC_glProgramUniformMatrix4x2fv ProgramUniformMatrix4x2fv;
	PROC_glProgramUniformMatrix4x3dv ProgramUniformMatrix4x3dv;
	PROC_glProgramUniformMatrix4x3fv ProgramUniformMatrix4x3fv;
	PROC_glProvokingVertex ProvokingVertex;
	PROC_glPushDebugGroup PushDebugGroup;
	PROC_glQueryCounter QueryCounter;
	PROC_glReadBuffer ReadBuffer;
	PROC_glReadPixels ReadPixels;
	PROC_glReadnPixels ReadnPixels;
	PROC_glReleaseShaderCompiler ReleaseShaderCompiler;
	PROC_glRenderbufferStorage RenderbufferStorage;
	PROC_glRenderbufferStorageMultisample RenderbufferStorageMultisample;
	PROC_glResumeTransformFeedback ResumeTransformFeedback;
	PROC_glSampleCoverage SampleCoverage;
	PROC_glSampleMaski SampleMaski;
	PROC_glSamplerParameterIiv SamplerParameterIiv;
	PROC_glSamplerParameterIuiv SamplerParameterIuiv;
	PROC_glSamplerParameterf SamplerParameterf;
	PROC_glSamplerParameterfv SamplerParameterfv;
	PROC_glSamplerParameteri SamplerParameteri;
	PROC_glSamplerParameteriv SamplerParameteriv;
	PROC_glScissor Scissor;
	PROC_glScissorArrayv ScissorArrayv;
	PROC_glScissorIndexed ScissorIndexed;
	PROC_glScissorIndexedv ScissorIndexedv;
	PROC_glShaderBinary ShaderBinary;
	PROC_glShaderSource ShaderSource;
	PROC_glShaderStorageBlockBinding ShaderStorageBlockBinding;
	PROC_glStencilFunc StencilFunc;
	PROC_glStencilFuncSeparate StencilFuncSeparate;
	PROC_glStencilMask StencilMask;
	PROC_glStencilMaskSeparate StencilMaskSeparate;
	PROC_glStencilOp StencilOp;
	PROC_glStencilOpSeparate StencilOpSeparate;
	PROC_glTexBuffer TexBuffer;
	PROC_glTexBufferRange TexBufferRange;
	PROC_glTexImage1D TexImage1D;
	PROC_glTexImage2D TexImage2D;
	PROC_glTexImage2DMultisample TexImage2DMultisample;
	PROC_glTexImage3D TexImage3D;
	PROC_glTexImage3DMultisample TexImage3DMultisample;
	PROC_glTexParameterIiv TexParameterIiv;
	PROC_glTexParameterIuiv TexParameterIuiv;
	PROC_glTexParameterf TexParameterf;
	PROC_glTexParameterfv TexParameterfv;
	PROC_glTexParameteri TexParameteri;
	PROC_glTexParameteriv TexParameteriv;
	PROC_glTexStorage1D TexStorage1D;
	PROC_glTexStorage2D TexStorage2D;
	PROC_glTexStorage2DMultisample TexStorage2DMultisample;
	PROC_glTexStorage3D TexStorage3D;
	PROC_glTexStorage3DMultisample TexStorage3DMultisample;
	PROC_glTexSubImage1D TexSubImage1D;
	PROC_glTexSubImage2D TexSubImage2D;
	PROC_glTexSubImage3D TexSubImage3D;
	PROC_glTextureBarrier TextureBarrier;
	PROC_glTextureBuffer TextureBuffer;
	PROC_glTextureBufferRange TextureBufferRange;
	PROC_glTextureParameterIiv TextureParameterIiv;
	PROC_glTextureParameterIuiv TextureParameterIuiv;
	PROC_glTextureParameterf TextureParameterf;
	PROC_glTextureParameterfv TextureParameterfv;
	PROC_glTextureParameteri TextureParameteri;
	PROC_glTextureParameteriv TextureParameteriv;
	PROC_glTextureStorage1D TextureStorage1D;
	PROC_glTextureStorage2D TextureStorage2D;
	PROC_glTextureStorage2DMultisample TextureStorage2DMultisample;
	PROC_glTextureStorage3D TextureStorage3D;
	PROC_glTextureStorage3DMultisample TextureStorage3DMultisample;
	PROC_glTextureSubImage1D TextureSubImage1D;
	PROC_glTextureSubImage2D TextureSubImage2D;
	PROC_glTextureSubImage3D TextureSubImage3D;
	PROC_glTextureView TextureView;
	PROC_glTransformFeedbackBufferBase TransformFeedbackBufferBase;
	PROC_glTransformFeedbackBufferRange TransformFeedbackBufferRange;
	PROC_glTransformFeedbackVaryings TransformFeedbackVaryings;
	PROC_glUniform1d Uniform1d;
	PROC_glUniform1dv Uniform1dv;
	PROC_glUniform1f Uniform1f;
	PROC_glUniform1fv Uniform1fv;
	PROC_glUniform1i Uniform1i;
	PROC_glUniform1iv Uniform1iv;
	PROC_glUniform1ui Uniform1ui;
	PROC_glUniform1uiv Uniform1uiv;
	PROC_glUniform2d Uniform2d;
	PROC_glUniform2dv Uniform2dv;
	PROC_glUniform2f Uniform2f;
	PROC_glUniform2fv Uniform2fv;
	PROC_glUniform2i Uniform2i;
	PROC_glUniform2iv Uniform2iv;
	PROC_glUniform2ui Uniform2ui;
	PROC_glUniform2uiv Uniform2uiv;
	PROC_glUniform3d Uniform3d;
	PROC_glUniform3dv Uniform3dv;
	PROC_glUniform3f Uniform3f;
	PROC_glUniform3fv Uniform3fv;
	PROC_glUniform3i Uniform3i;
	PROC_glUniform3iv Uniform3iv;
	PROC_glUniform3ui Uniform3ui;
	PROC_glUniform3uiv Uniform3uiv;
	PROC_glUniform4d Uniform4d;
	PROC_glUniform4dv Uniform4dv;
	PROC_glUniform4f Uniform4f;
	PROC_glUniform4fv Uniform4fv;
	PROC_glUniform4i Uniform4i;
	PROC_glUniform4iv Uniform4iv;
	PROC_glUniform4ui Uniform4ui;
	PROC_glUniform4uiv Uniform4uiv;
	PROC_glUniformBlockBinding UniformBlockBinding;
	PROC_glUniformMatrix2dv UniformMatrix2dv;
	PROC_glUniformMatrix2fv UniformMatrix2fv;
	PROC_glUniformMatrix2x3dv UniformMatrix2x3dv;
	PROC_glUniformMatrix2x3fv UniformMatrix2x3fv;
	PROC_glUniformMatrix2x4dv UniformMatrix2x4dv;
	PROC_glUniformMatrix2x4fv UniformMatrix2x4fv;
	PROC_glUniformMatrix3dv UniformMatrix3dv;
	PROC_glUniformMatrix3fv UniformMatrix3fv;
	PROC_glUniformMatrix3x2dv UniformMatrix3x2dv;
	PROC_glUniformMatrix3x2fv UniformMatrix3x2fv;
	PROC_glUniformMatrix3x4dv UniformMatrix3x4dv;
	PROC_glUniformMatrix3x4fv UniformMatrix3x4fv;
	PROC_glUniformMatrix4dv UniformMatrix4dv;
	PROC_glUniformMatrix4fv UniformMatrix4fv;
	PROC_glUniformMatrix4x2dv UniformMatrix4x2dv;
	PROC_glUniformMatrix4x2fv UniformMatrix4x2fv;
	PROC_glUniformMatrix4x3dv UniformMatrix4x3dv;
	PROC_glUniformMatrix4x3fv UniformMatrix4x3fv;
	PROC_glUniformSubroutinesuiv UniformSubroutinesuiv;
	PROC_glUnmapBuffer UnmapBuffer;
	PROC_glUnmapNamedBuffer UnmapNamedBuffer;
	PROC_glUseProgram UseProgram;
	PROC_glUseProgramStages UseProgramStages;
	PROC_glValidateProgram ValidateProgram;
	PROC_glValidateProgramPipeline ValidateProgramPipeline;
	PROC_glVertexArrayAttribBinding VertexArrayAttribBinding;
	PROC_glVertexArrayAttribFormat VertexArrayAttribFormat;
	PROC_glVertexArrayAttribIFormat VertexArrayAttribIFormat;
	PROC_glVertexArrayAttribLFormat VertexArrayAttribLFormat;
	PROC_glVertexArrayBindingDivisor VertexArrayBindingDivisor;
	PROC_glVertexArrayElementBuffer VertexArrayElementBuffer;
	PROC_glVertexArrayVertexBuffer VertexArrayVertexBuffer;
	PROC_glVertexArrayVertexBuffers VertexArrayVertexBuffers;
	PROC_glVertexAttrib1d VertexAttrib1d;
	PROC_glVertexAttrib1dv VertexAttrib1dv;
	PROC_glVertexAttrib1f VertexAttrib1f;
	PROC_glVertexAttrib1fv VertexAttrib1fv;
	PROC_glVertexAttrib1s VertexAttrib1s;
	PROC_glVertexAttrib1sv VertexAttrib1sv;
	PROC_glVertexAttrib2d VertexAttrib2d;
	PROC_glVertexAttrib2dv VertexAttrib2dv;
	PROC_glVertexAttrib2f VertexAttrib2f;
	PROC_glVertexAttrib2fv VertexAttrib2fv;
	PROC_glVertexAttrib2s VertexAttrib2s;
	PROC_glVertexAttrib2sv VertexAttrib2sv;
	PROC_glVertexAttrib3d VertexAttrib3d;
	PROC_glVertexAttrib3dv VertexAttrib3dv;
	PROC_glVertexAttrib3f VertexAttrib3f;
	PROC_glVertexAttrib3fv VertexAttrib3fv;
	PROC_glVertexAttrib3s VertexAttrib3s;
	PROC_glVertexAttrib3sv VertexAttrib3sv;
	PROC_glVertexAttrib4Nbv VertexAttrib4Nbv;
	PROC_glVertexAttrib4Niv VertexAttrib4Niv;
	PROC_glVertexAttrib4Nsv VertexAttrib4Nsv;
	PROC_glVertexAttrib4Nub VertexAttrib4Nub;
	PROC_glVertexAttrib4Nubv VertexAttrib4Nubv;
	PROC_glVertexAttrib4Nuiv VertexAttrib4Nuiv;
	PROC_glVertexAttrib4Nusv VertexAttrib4Nusv;
	PROC_glVertexAttrib4bv VertexAttrib4bv;
	PROC_glVertexAttrib4d VertexAttrib4d;
	PROC_glVertexAttrib4dv VertexAttrib4dv;
	PROC_glVertexAttrib4f VertexAttrib4f;
	PROC_glVertexAttrib4fv VertexAttrib4fv;
	PROC_glVertexAttrib4iv VertexAttrib4iv;
	PROC_glVertexAttrib4s VertexAttrib4s;
	PROC_glVertexAttrib4sv VertexAttrib4sv;
	PROC_glVertexAttrib4ubv VertexAttrib4ubv;
	PROC_glVertexAttrib4uiv VertexAttrib4uiv;
	PROC_glVertexAttrib4usv VertexAttrib4usv;
	PROC_glVertexAttribBinding VertexAttribBinding;
	PROC_glVertexAttribDivisor VertexAttribDivisor;
	PROC_glVertexAttribFormat VertexAttribFormat;
	PROC_glVertexAttribI1i VertexAttribI1i;
	PROC_glVertexAttribI1iv VertexAttribI1iv;
	PROC_glVertexAttribI1ui VertexAttribI1ui;
	PROC_glVertexAttribI1uiv VertexAttribI1uiv;
	PROC_glVertexAttribI2i VertexAttribI2i;
	PROC_glVertexAttribI2iv VertexAttribI2iv;
	PROC_glVertexAttribI2ui VertexAttribI2ui;
	PROC_glVertexAttribI2uiv VertexAttribI2uiv;
	PROC_glVertexAttribI3i VertexAttribI3i;
	PROC_glVertexAttribI3iv VertexAttribI3iv;
	PROC_glVertexAttribI3ui VertexAttribI3ui;
	PROC_glVertexAttribI3uiv VertexAttribI3uiv;
	PROC_glVertexAttribI4bv VertexAttribI4bv;
	PROC_glVertexAttribI4i VertexAttribI4i;
	PROC_glVertexAttribI4iv VertexAttribI4iv;
	PROC_glVertexAttribI4sv VertexAttribI4sv;
	PROC_glVertexAttribI4ubv VertexAttribI4ubv;
	PROC_glVertexAttribI4ui VertexAttribI4ui;
	PROC_glVertexAttribI4uiv VertexAttribI4uiv;
	PROC_glVertexAttribI4usv VertexAttribI4usv;
	PROC_glVertexAttribIFormat VertexAttribIFormat;
	PROC_glVertexAttribIPointer VertexAttribIPointer;
	PROC_glVertexAttribL1d VertexAttribL1d;
	PROC_glVertexAttribL1dv VertexAttribL1dv;
	PROC_glVertexAttribL2d VertexAttribL2d;
	PROC_glVertexAttribL2dv VertexAttribL2dv;
	PROC_glVertexAttribL3d VertexAttribL3d;
	PROC_glVertexAttribL3dv VertexAttribL3dv;
	PROC_glVertexAttribL4d VertexAttribL4d;
	PROC_glVertexAttribL4dv VertexAttribL4dv;
	PROC_glVertexAttribLFormat VertexAttribLFormat;
	PROC_glVertexAttribLPointer VertexAttribLPointer;
	PROC_glVertexAttribP1ui VertexAttribP1ui;
	PROC_glVertexAttribP1uiv VertexAttribP1uiv;
	PROC_glVertexAttribP2ui VertexAttribP2ui;
	PROC_glVertexAttribP2uiv VertexAttribP2uiv;
	PROC_glVertexAttribP3ui VertexAttribP3ui;
	PROC_glVertexAttribP3uiv VertexAttribP3uiv;
	PROC_glVertexAttribP4ui VertexAttribP4ui;
	PROC_glVertexAttribP4uiv VertexAttribP4uiv;
	PROC_glVertexAttribPointer VertexAttribPointer;
	PROC_glVertexBindingDivisor VertexBindingDivisor;
	PROC_glViewport Viewport;
	PROC_glViewportArrayv ViewportArrayv;
	PROC_glViewportIndexedf ViewportIndexedf;
	PROC_glViewportIndexedfv ViewportIndexedfv;

	bool load();

private:
	GLMethodsImpl(const GLMethodsImpl & copy);
	void operator = (const GLMethodsImpl & rhs);
};

#ifdef MGL_DEBUG

static FILE * GLMethodsDebugFile = stdout;

// static void GLMethodsDebug_uniform_reader(void * glmethod, GLuint program, GLint location, GLvoid * params) {
// 	fprintf(GLMethodsDebugFile, "[%d] uniform_reader_%p(%u, %d, 0x%p)\n", 0, glmethod, program, location, params);
// }

// static void GLMethodsDebug_uniform_writer(void * glmethod, GLuint program, GLint location, ...) {
// 	fprintf(GLMethodsDebugFile, "[%d] uniform_writer_%p(%u, %d, ...)\n", 0, glmethod, program, location);
// }

// static void GLMethodsDebug_attrib_norm_ptr(void * glmethod, GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid * pointer) {
// 	fprintf(GLMethodsDebugFile, "[%d] attrib_norm_ptr_%p(%u, %d, 0x%x, %d, %d, 0x%p)\n", 0, glmethod, index, size, type, normalized, stride, pointer);
// }

// static void GLMethodsDebug_attrib_ptr(void * glmethod, GLuint index, GLint size, GLenum type, GLsizei stride, const GLvoid * pointer) {
// 	fprintf(GLMethodsDebugFile, "[%d] attrib_ptr_%p(%u, %d, 0x%x, %d, 0x%p)\n", 0, glmethod, index, size, type, stride, pointer);
// }

struct GLMethodsDebugImpl {
	GLMethodsImpl gl;

	GLvoid CullFace(GLenum mode) const {
		gl.CullFace(mode);
		fprintf(GLMethodsDebugFile, "[%4d] CullFace(0x%x)\n", gl.GetError(), mode);
	}

	GLvoid FrontFace(GLenum mode) const {
		gl.FrontFace(mode);
		fprintf(GLMethodsDebugFile, "[%4d] FrontFace(0x%x)\n", gl.GetError(), mode);
	}

	GLvoid Hint(GLenum target, GLenum mode) const {
		gl.Hint(target, mode);
		fprintf(GLMethodsDebugFile, "[%4d] Hint(0x%x, 0x%x)\n", gl.GetError(), target, mode);
	}

	GLvoid LineWidth(GLfloat width) const {
		gl.LineWidth(width);
		fprintf(GLMethodsDebugFile, "[%4d] LineWidth(%f)\n", gl.GetError(), width);
	}

	GLvoid PointSize(GLfloat size) const {
		gl.PointSize(size);
		fprintf(GLMethodsDebugFile, "[%4d] PointSize(%f)\n", gl.GetError(), size);
	}

	GLvoid PolygonMode(GLenum face, GLenum mode) const {
		gl.PolygonMode(face, mode);
		fprintf(GLMethodsDebugFile, "[%4d] PolygonMode(0x%x, 0x%x)\n", gl.GetError(), face, mode);
	}

	GLvoid Scissor(GLint x, GLint y, GLsizei width, GLsizei height) const {
		gl.Scissor(x, y, width, height);
		fprintf(GLMethodsDebugFile, "[%4d] Scissor(%d, %d, %d, %d)\n", gl.GetError(), x, y, width, height);
	}

	GLvoid TexParameterf(GLenum target, GLenum pname, GLfloat param) const {
		gl.TexParameterf(target, pname, param);
		fprintf(GLMethodsDebugFile, "[%4d] TexParameterf(0x%x, 0x%x, %f)\n", gl.GetError(), target, pname, param);
	}

	GLvoid TexParameterfv(GLenum target, GLenum pname, const GLfloat * params) const {
		gl.TexParameterfv(target, pname, params);
		fprintf(GLMethodsDebugFile, "[%4d] TexParameterfv(0x%x, 0x%x, 0x%p)\n", gl.GetError(), target, pname, params);
	}

	GLvoid TexParameteri(GLenum target, GLenum pname, GLint param) const {
		gl.TexParameteri(target, pname, param);
		fprintf(GLMethodsDebugFile, "[%4d] TexParameteri(0x%x, 0x%x, %d)\n", gl.GetError(), target, pname, param);
	}

	GLvoid TexParameteriv(GLenum target, GLenum pname, const GLint * params) const {
		gl.TexParameteriv(target, pname, params);
		fprintf(GLMethodsDebugFile, "[%4d] TexParameteriv(0x%x, 0x%x, 0x%p)\n", gl.GetError(), target, pname, params);
	}

	GLvoid TexImage1D(GLenum target, GLint level, GLint internalformat, GLsizei width, GLint border, GLenum format, GLenum type, const GLvoid * pixels) const {
		gl.TexImage1D(target, level, internalformat, width, border, format, type, pixels);
		fprintf(GLMethodsDebugFile, "[%4d] TexImage1D(0x%x, %d, %d, %d, %d, 0x%x, 0x%x, 0x%p)\n", gl.GetError(), target, level, internalformat, width, border, format, type, pixels);
	}

	GLvoid TexImage2D(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const GLvoid * pixels) const {
		gl.TexImage2D(target, level, internalformat, width, height, border, format, type, pixels);
		fprintf(GLMethodsDebugFile, "[%4d] TexImage2D(0x%x, %d, %d, %d, %d, %d, 0x%x, 0x%x, 0x%p)\n", gl.GetError(), target, level, internalformat, width, height, border, format, type, pixels);
	}

	GLvoid DrawBuffer(GLenum buf) const {
		gl.DrawBuffer(buf);
		fprintf(GLMethodsDebugFile, "[%4d] DrawBuffer(0x%x)\n", gl.GetError(), buf);
	}

	GLvoid Clear(GLbitfield mask) const {
		gl.Clear(mask);
		fprintf(GLMethodsDebugFile, "[%4d] Clear(0x%x)\n", gl.GetError(), mask);
	}

	GLvoid ClearColor(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha) const {
		gl.ClearColor(red, green, blue, alpha);
		fprintf(GLMethodsDebugFile, "[%4d] ClearColor(%f, %f, %f, %f)\n", gl.GetError(), red, green, blue, alpha);
	}

	GLvoid ClearStencil(GLint s) const {
		gl.ClearStencil(s);
		fprintf(GLMethodsDebugFile, "[%4d] ClearStencil(%d)\n", gl.GetError(), s);
	}

	GLvoid ClearDepth(GLdouble depth) const {
		gl.ClearDepth(depth);
		fprintf(GLMethodsDebugFile, "[%4d] ClearDepth(%lf)\n", gl.GetError(), depth);
	}

	GLvoid StencilMask(GLuint mask) const {
		gl.StencilMask(mask);
		fprintf(GLMethodsDebugFile, "[%4d] StencilMask(%u)\n", gl.GetError(), mask);
	}

	GLvoid ColorMask(GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha) const {
		gl.ColorMask(red, green, blue, alpha);
		fprintf(GLMethodsDebugFile, "[%4d] ColorMask(%d, %d, %d, %d)\n", gl.GetError(), red, green, blue, alpha);
	}

	GLvoid DepthMask(GLboolean flag) const {
		gl.DepthMask(flag);
		fprintf(GLMethodsDebugFile, "[%4d] DepthMask(%d)\n", gl.GetError(), flag);
	}

	GLvoid Disable(GLenum cap) const {
		gl.Disable(cap);
		fprintf(GLMethodsDebugFile, "[%4d] Disable(0x%x)\n", gl.GetError(), cap);
	}

	GLvoid Enable(GLenum cap) const {
		gl.Enable(cap);
		fprintf(GLMethodsDebugFile, "[%4d] Enable(0x%x)\n", gl.GetError(), cap);
	}

	GLvoid Finish() const {
		gl.Finish();
		fprintf(GLMethodsDebugFile, "[%4d] Finish()\n", gl.GetError());
	}

	GLvoid Flush() const {
		gl.Flush();
		fprintf(GLMethodsDebugFile, "[%4d] Flush()\n", gl.GetError());
	}

	GLvoid BlendFunc(GLenum sfactor, GLenum dfactor) const {
		gl.BlendFunc(sfactor, dfactor);
		fprintf(GLMethodsDebugFile, "[%4d] BlendFunc(0x%x, 0x%x)\n", gl.GetError(), sfactor, dfactor);
	}

	GLvoid LogicOp(GLenum opcode) const {
		gl.LogicOp(opcode);
		fprintf(GLMethodsDebugFile, "[%4d] LogicOp(0x%x)\n", gl.GetError(), opcode);
	}

	GLvoid StencilFunc(GLenum func, GLint ref, GLuint mask) const {
		gl.StencilFunc(func, ref, mask);
		fprintf(GLMethodsDebugFile, "[%4d] StencilFunc(0x%x, %d, %u)\n", gl.GetError(), func, ref, mask);
	}

	GLvoid StencilOp(GLenum fail, GLenum zfail, GLenum zpass) const {
		gl.StencilOp(fail, zfail, zpass);
		fprintf(GLMethodsDebugFile, "[%4d] StencilOp(0x%x, 0x%x, 0x%x)\n", gl.GetError(), fail, zfail, zpass);
	}

	GLvoid DepthFunc(GLenum func) const {
		gl.DepthFunc(func);
		fprintf(GLMethodsDebugFile, "[%4d] DepthFunc(0x%x)\n", gl.GetError(), func);
	}

	GLvoid PixelStoref(GLenum pname, GLfloat param) const {
		gl.PixelStoref(pname, param);
		fprintf(GLMethodsDebugFile, "[%4d] PixelStoref(0x%x, %f)\n", gl.GetError(), pname, param);
	}

	GLvoid PixelStorei(GLenum pname, GLint param) const {
		gl.PixelStorei(pname, param);
		fprintf(GLMethodsDebugFile, "[%4d] PixelStorei(0x%x, %d)\n", gl.GetError(), pname, param);
	}

	GLvoid ReadBuffer(GLenum src) const {
		gl.ReadBuffer(src);
		fprintf(GLMethodsDebugFile, "[%4d] ReadBuffer(0x%x)\n", gl.GetError(), src);
	}

	GLvoid ReadPixels(GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, GLvoid * pixels) const {
		gl.ReadPixels(x, y, width, height, format, type, pixels);
		fprintf(GLMethodsDebugFile, "[%4d] ReadPixels(%d, %d, %d, %d, 0x%x, 0x%x, 0x%p)\n", gl.GetError(), x, y, width, height, format, type, pixels);
	}

	GLvoid GetBooleanv(GLenum pname, GLboolean * data) const {
		gl.GetBooleanv(pname, data);
		fprintf(GLMethodsDebugFile, "[%4d] GetBooleanv(0x%x, 0x%p)\n", gl.GetError(), pname, data);
	}

	GLvoid GetDoublev(GLenum pname, GLdouble * data) const {
		gl.GetDoublev(pname, data);
		fprintf(GLMethodsDebugFile, "[%4d] GetDoublev(0x%x, 0x%p)\n", gl.GetError(), pname, data);
	}

	GLenum GetError() const {
		GLenum res = gl.GetError();
		fprintf(GLMethodsDebugFile, "[%4d] GetError() -> 0x%x\n", gl.GetError(), res);
		return res;
	}

	GLvoid GetFloatv(GLenum pname, GLfloat * data) const {
		gl.GetFloatv(pname, data);
		fprintf(GLMethodsDebugFile, "[%4d] GetFloatv(0x%x, 0x%p)\n", gl.GetError(), pname, data);
	}

	GLvoid GetIntegerv(GLenum pname, GLint * data) const {
		gl.GetIntegerv(pname, data);
		fprintf(GLMethodsDebugFile, "[%4d] GetIntegerv(0x%x, 0x%p)\n", gl.GetError(), pname, data);
	}

	const GLubyte * GetString(GLenum name) const {
		const GLubyte * res = gl.GetString(name);
		fprintf(GLMethodsDebugFile, "[%4d] GetString(0x%x) -> 0x%p\n", gl.GetError(), name, res);
		return res;
	}

	GLvoid GetTexImage(GLenum target, GLint level, GLenum format, GLenum type, GLvoid * pixels) const {
		gl.GetTexImage(target, level, format, type, pixels);
		fprintf(GLMethodsDebugFile, "[%4d] GetTexImage(0x%x, %d, 0x%x, 0x%x, 0x%p)\n", gl.GetError(), target, level, format, type, pixels);
	}

	GLvoid GetTexParameterfv(GLenum target, GLenum pname, GLfloat * params) const {
		gl.GetTexParameterfv(target, pname, params);
		fprintf(GLMethodsDebugFile, "[%4d] GetTexParameterfv(0x%x, 0x%x, 0x%p)\n", gl.GetError(), target, pname, params);
	}

	GLvoid GetTexParameteriv(GLenum target, GLenum pname, GLint * params) const {
		gl.GetTexParameteriv(target, pname, params);
		fprintf(GLMethodsDebugFile, "[%4d] GetTexParameteriv(0x%x, 0x%x, 0x%p)\n", gl.GetError(), target, pname, params);
	}

	GLvoid GetTexLevelParameterfv(GLenum target, GLint level, GLenum pname, GLfloat * params) const {
		gl.GetTexLevelParameterfv(target, level, pname, params);
		fprintf(GLMethodsDebugFile, "[%4d] GetTexLevelParameterfv(0x%x, %d, 0x%x, 0x%p)\n", gl.GetError(), target, level, pname, params);
	}

	GLvoid GetTexLevelParameteriv(GLenum target, GLint level, GLenum pname, GLint * params) const {
		gl.GetTexLevelParameteriv(target, level, pname, params);
		fprintf(GLMethodsDebugFile, "[%4d] GetTexLevelParameteriv(0x%x, %d, 0x%x, 0x%p)\n", gl.GetError(), target, level, pname, params);
	}

	GLboolean IsEnabled(GLenum cap) const {
		GLboolean res = gl.IsEnabled(cap);
		fprintf(GLMethodsDebugFile, "[%4d] IsEnabled(0x%x) -> %d\n", gl.GetError(), cap, res);
		return res;
	}

	GLvoid DepthRange(GLdouble near, GLdouble far) const {
		gl.DepthRange(near, far);
		fprintf(GLMethodsDebugFile, "[%4d] DepthRange(%lf, %lf)\n", gl.GetError(), near, far);
	}

	GLvoid Viewport(GLint x, GLint y, GLsizei width, GLsizei height) const {
		gl.Viewport(x, y, width, height);
		fprintf(GLMethodsDebugFile, "[%4d] Viewport(%d, %d, %d, %d)\n", gl.GetError(), x, y, width, height);
	}

	GLvoid DrawArrays(GLenum mode, GLint first, GLsizei count) const {
		gl.DrawArrays(mode, first, count);
		fprintf(GLMethodsDebugFile, "[%4d] DrawArrays(0x%x, %d, %d)\n", gl.GetError(), mode, first, count);
	}

	GLvoid DrawElements(GLenum mode, GLsizei count, GLenum type, const GLvoid * indices) const {
		gl.DrawElements(mode, count, type, indices);
		fprintf(GLMethodsDebugFile, "[%4d] DrawElements(0x%x, %d, 0x%x, 0x%p)\n", gl.GetError(), mode, count, type, indices);
	}

	GLvoid GetPointerv(GLenum pname, GLvoid ** params) const {
		gl.GetPointerv(pname, params);
		fprintf(GLMethodsDebugFile, "[%4d] GetPointerv(0x%x, 0x%p)\n", gl.GetError(), pname, params);
	}

	GLvoid PolygonOffset(GLfloat factor, GLfloat units) const {
		gl.PolygonOffset(factor, units);
		fprintf(GLMethodsDebugFile, "[%4d] PolygonOffset(%f, %f)\n", gl.GetError(), factor, units);
	}

	GLvoid CopyTexImage1D(GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLint border) const {
		gl.CopyTexImage1D(target, level, internalformat, x, y, width, border);
		fprintf(GLMethodsDebugFile, "[%4d] CopyTexImage1D(0x%x, %d, 0x%x, %d, %d, %d, %d)\n", gl.GetError(), target, level, internalformat, x, y, width, border);
	}

	GLvoid CopyTexImage2D(GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLsizei height, GLint border) const {
		gl.CopyTexImage2D(target, level, internalformat, x, y, width, height, border);
		fprintf(GLMethodsDebugFile, "[%4d] CopyTexImage2D(0x%x, %d, 0x%x, %d, %d, %d, %d, %d)\n", gl.GetError(), target, level, internalformat, x, y, width, height, border);
	}

	GLvoid CopyTexSubImage1D(GLenum target, GLint level, GLint xoffset, GLint x, GLint y, GLsizei width) const {
		gl.CopyTexSubImage1D(target, level, xoffset, x, y, width);
		fprintf(GLMethodsDebugFile, "[%4d] CopyTexSubImage1D(0x%x, %d, %d, %d, %d, %d)\n", gl.GetError(), target, level, xoffset, x, y, width);
	}

	GLvoid CopyTexSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height) const {
		gl.CopyTexSubImage2D(target, level, xoffset, yoffset, x, y, width, height);
		fprintf(GLMethodsDebugFile, "[%4d] CopyTexSubImage2D(0x%x, %d, %d, %d, %d, %d, %d, %d)\n", gl.GetError(), target, level, xoffset, yoffset, x, y, width, height);
	}

	GLvoid TexSubImage1D(GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLenum type, const GLvoid * pixels) const {
		gl.TexSubImage1D(target, level, xoffset, width, format, type, pixels);
		fprintf(GLMethodsDebugFile, "[%4d] TexSubImage1D(0x%x, %d, %d, %d, 0x%x, 0x%x, 0x%p)\n", gl.GetError(), target, level, xoffset, width, format, type, pixels);
	}

	GLvoid TexSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid * pixels) const {
		gl.TexSubImage2D(target, level, xoffset, yoffset, width, height, format, type, pixels);
		fprintf(GLMethodsDebugFile, "[%4d] TexSubImage2D(0x%x, %d, %d, %d, %d, %d, 0x%x, 0x%x, 0x%p)\n", gl.GetError(), target, level, xoffset, yoffset, width, height, format, type, pixels);
	}

	GLvoid BindTexture(GLenum target, GLuint texture) const {
		gl.BindTexture(target, texture);
		fprintf(GLMethodsDebugFile, "[%4d] BindTexture(0x%x, %u)\n", gl.GetError(), target, texture);
	}

	GLvoid DeleteTextures(GLsizei n, const GLuint * textures) const {
		gl.DeleteTextures(n, textures);
		fprintf(GLMethodsDebugFile, "[%4d] DeleteTextures(%d, 0x%p)\n", gl.GetError(), n, textures);
	}

	GLvoid GenTextures(GLsizei n, GLuint * textures) const {
		gl.GenTextures(n, textures);
		fprintf(GLMethodsDebugFile, "[%4d] GenTextures(%d, 0x%p)\n", gl.GetError(), n, textures);
	}

	GLboolean IsTexture(GLuint texture) const {
		GLboolean res = gl.IsTexture(texture);
		fprintf(GLMethodsDebugFile, "[%4d] IsTexture(%u) -> %d\n", gl.GetError(), texture, res);
		return res;
	}

	GLvoid DrawRangeElements(GLenum mode, GLuint start, GLuint end, GLsizei count, GLenum type, const GLvoid * indices) const {
		gl.DrawRangeElements(mode, start, end, count, type, indices);
		fprintf(GLMethodsDebugFile, "[%4d] DrawRangeElements(0x%x, %u, %u, %d, 0x%x, 0x%p)\n", gl.GetError(), mode, start, end, count, type, indices);
	}

	GLvoid TexImage3D(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLenum format, GLenum type, const GLvoid * pixels) const {
		gl.TexImage3D(target, level, internalformat, width, height, depth, border, format, type, pixels);
		fprintf(GLMethodsDebugFile, "[%4d] TexImage3D(0x%x, %d, %d, %d, %d, %d, %d, 0x%x, 0x%x, 0x%p)\n", gl.GetError(), target, level, internalformat, width, height, depth, border, format, type, pixels);
	}

	GLvoid TexSubImage3D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const GLvoid * pixels) const {
		gl.TexSubImage3D(target, level, xoffset, yoffset, zoffset, width, height, depth, format, type, pixels);
		fprintf(GLMethodsDebugFile, "[%4d] TexSubImage3D(0x%x, %d, %d, %d, %d, %d, %d, %d, 0x%x, 0x%x, 0x%p)\n", gl.GetError(), target, level, xoffset, yoffset, zoffset, width, height, depth, format, type, pixels);
	}

	GLvoid CopyTexSubImage3D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLint x, GLint y, GLsizei width, GLsizei height) const {
		gl.CopyTexSubImage3D(target, level, xoffset, yoffset, zoffset, x, y, width, height);
		fprintf(GLMethodsDebugFile, "[%4d] CopyTexSubImage3D(0x%x, %d, %d, %d, %d, %d, %d, %d, %d)\n", gl.GetError(), target, level, xoffset, yoffset, zoffset, x, y, width, height);
	}

	GLvoid ActiveTexture(GLenum texture) const {
		gl.ActiveTexture(texture);
		fprintf(GLMethodsDebugFile, "[%4d] ActiveTexture(0x%x)\n", gl.GetError(), texture);
	}

	GLvoid SampleCoverage(GLfloat value, GLboolean invert) const {
		gl.SampleCoverage(value, invert);
		fprintf(GLMethodsDebugFile, "[%4d] SampleCoverage(%f, %d)\n", gl.GetError(), value, invert);
	}

	GLvoid CompressedTexImage3D(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLsizei imageSize, const GLvoid * data) const {
		gl.CompressedTexImage3D(target, level, internalformat, width, height, depth, border, imageSize, data);
		fprintf(GLMethodsDebugFile, "[%4d] CompressedTexImage3D(0x%x, %d, 0x%x, %d, %d, %d, %d, %d, 0x%p)\n", gl.GetError(), target, level, internalformat, width, height, depth, border, imageSize, data);
	}

	GLvoid CompressedTexImage2D(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLint border, GLsizei imageSize, const GLvoid * data) const {
		gl.CompressedTexImage2D(target, level, internalformat, width, height, border, imageSize, data);
		fprintf(GLMethodsDebugFile, "[%4d] CompressedTexImage2D(0x%x, %d, 0x%x, %d, %d, %d, %d, 0x%p)\n", gl.GetError(), target, level, internalformat, width, height, border, imageSize, data);
	}

	GLvoid CompressedTexImage1D(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLint border, GLsizei imageSize, const GLvoid * data) const {
		gl.CompressedTexImage1D(target, level, internalformat, width, border, imageSize, data);
		fprintf(GLMethodsDebugFile, "[%4d] CompressedTexImage1D(0x%x, %d, 0x%x, %d, %d, %d, 0x%p)\n", gl.GetError(), target, level, internalformat, width, border, imageSize, data);
	}

	GLvoid CompressedTexSubImage3D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLsizei imageSize, const GLvoid * data) const {
		gl.CompressedTexSubImage3D(target, level, xoffset, yoffset, zoffset, width, height, depth, format, imageSize, data);
		fprintf(GLMethodsDebugFile, "[%4d] CompressedTexSubImage3D(0x%x, %d, %d, %d, %d, %d, %d, %d, 0x%x, %d, 0x%p)\n", gl.GetError(), target, level, xoffset, yoffset, zoffset, width, height, depth, format, imageSize, data);
	}

	GLvoid CompressedTexSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const GLvoid * data) const {
		gl.CompressedTexSubImage2D(target, level, xoffset, yoffset, width, height, format, imageSize, data);
		fprintf(GLMethodsDebugFile, "[%4d] CompressedTexSubImage2D(0x%x, %d, %d, %d, %d, %d, 0x%x, %d, 0x%p)\n", gl.GetError(), target, level, xoffset, yoffset, width, height, format, imageSize, data);
	}

	GLvoid CompressedTexSubImage1D(GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLsizei imageSize, const GLvoid * data) const {
		gl.CompressedTexSubImage1D(target, level, xoffset, width, format, imageSize, data);
		fprintf(GLMethodsDebugFile, "[%4d] CompressedTexSubImage1D(0x%x, %d, %d, %d, 0x%x, %d, 0x%p)\n", gl.GetError(), target, level, xoffset, width, format, imageSize, data);
	}

	GLvoid GetCompressedTexImage(GLenum target, GLint level, GLvoid * img) const {
		gl.GetCompressedTexImage(target, level, img);
		fprintf(GLMethodsDebugFile, "[%4d] GetCompressedTexImage(0x%x, %d, 0x%p)\n", gl.GetError(), target, level, img);
	}

	GLvoid BlendFuncSeparate(GLenum sfactorRGB, GLenum dfactorRGB, GLenum sfactorAlpha, GLenum dfactorAlpha) const {
		gl.BlendFuncSeparate(sfactorRGB, dfactorRGB, sfactorAlpha, dfactorAlpha);
		fprintf(GLMethodsDebugFile, "[%4d] BlendFuncSeparate(0x%x, 0x%x, 0x%x, 0x%x)\n", gl.GetError(), sfactorRGB, dfactorRGB, sfactorAlpha, dfactorAlpha);
	}

	GLvoid MultiDrawArrays(GLenum mode, const GLint * first, const GLsizei * count, GLsizei drawcount) const {
		gl.MultiDrawArrays(mode, first, count, drawcount);
		fprintf(GLMethodsDebugFile, "[%4d] MultiDrawArrays(0x%x, 0x%p, 0x%p, %d)\n", gl.GetError(), mode, first, count, drawcount);
	}

	GLvoid MultiDrawElements(GLenum mode, const GLsizei * count, GLenum type, const GLvoid * const* indices, GLsizei drawcount) const {
		gl.MultiDrawElements(mode, count, type, indices, drawcount);
		fprintf(GLMethodsDebugFile, "[%4d] MultiDrawElements(0x%x, 0x%p, 0x%x, 0x%p, %d)\n", gl.GetError(), mode, count, type, indices, drawcount);
	}

	GLvoid PointParameterf(GLenum pname, GLfloat param) const {
		gl.PointParameterf(pname, param);
		fprintf(GLMethodsDebugFile, "[%4d] PointParameterf(0x%x, %f)\n", gl.GetError(), pname, param);
	}

	GLvoid PointParameterfv(GLenum pname, const GLfloat * params) const {
		gl.PointParameterfv(pname, params);
		fprintf(GLMethodsDebugFile, "[%4d] PointParameterfv(0x%x, 0x%p)\n", gl.GetError(), pname, params);
	}

	GLvoid PointParameteri(GLenum pname, GLint param) const {
		gl.PointParameteri(pname, param);
		fprintf(GLMethodsDebugFile, "[%4d] PointParameteri(0x%x, %d)\n", gl.GetError(), pname, param);
	}

	GLvoid PointParameteriv(GLenum pname, const GLint * params) const {
		gl.PointParameteriv(pname, params);
		fprintf(GLMethodsDebugFile, "[%4d] PointParameteriv(0x%x, 0x%p)\n", gl.GetError(), pname, params);
	}

	GLvoid BlendColor(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha) const {
		gl.BlendColor(red, green, blue, alpha);
		fprintf(GLMethodsDebugFile, "[%4d] BlendColor(%f, %f, %f, %f)\n", gl.GetError(), red, green, blue, alpha);
	}

	GLvoid BlendEquation(GLenum mode) const {
		gl.BlendEquation(mode);
		fprintf(GLMethodsDebugFile, "[%4d] BlendEquation(0x%x)\n", gl.GetError(), mode);
	}

	GLvoid GenQueries(GLsizei n, GLuint * ids) const {
		gl.GenQueries(n, ids);
		fprintf(GLMethodsDebugFile, "[%4d] GenQueries(%d, 0x%p)\n", gl.GetError(), n, ids);
	}

	GLvoid DeleteQueries(GLsizei n, const GLuint * ids) const {
		gl.DeleteQueries(n, ids);
		fprintf(GLMethodsDebugFile, "[%4d] DeleteQueries(%d, 0x%p)\n", gl.GetError(), n, ids);
	}

	GLboolean IsQuery(GLuint id) const {
		GLboolean res = gl.IsQuery(id);
		fprintf(GLMethodsDebugFile, "[%4d] IsQuery(%u) -> %d\n", gl.GetError(), id, res);
		return res;
	}

	GLvoid BeginQuery(GLenum target, GLuint id) const {
		gl.BeginQuery(target, id);
		fprintf(GLMethodsDebugFile, "[%4d] BeginQuery(0x%x, %u)\n", gl.GetError(), target, id);
	}

	GLvoid EndQuery(GLenum target) const {
		gl.EndQuery(target);
		fprintf(GLMethodsDebugFile, "[%4d] EndQuery(0x%x)\n", gl.GetError(), target);
	}

	GLvoid GetQueryiv(GLenum target, GLenum pname, GLint * params) const {
		gl.GetQueryiv(target, pname, params);
		fprintf(GLMethodsDebugFile, "[%4d] GetQueryiv(0x%x, 0x%x, 0x%p)\n", gl.GetError(), target, pname, params);
	}

	GLvoid GetQueryObjectiv(GLuint id, GLenum pname, GLint * params) const {
		gl.GetQueryObjectiv(id, pname, params);
		fprintf(GLMethodsDebugFile, "[%4d] GetQueryObjectiv(%u, 0x%x, 0x%p)\n", gl.GetError(), id, pname, params);
	}

	GLvoid GetQueryObjectuiv(GLuint id, GLenum pname, GLuint * params) const {
		gl.GetQueryObjectuiv(id, pname, params);
		fprintf(GLMethodsDebugFile, "[%4d] GetQueryObjectuiv(%u, 0x%x, 0x%p)\n", gl.GetError(), id, pname, params);
	}

	GLvoid BindBuffer(GLenum target, GLuint buffer) const {
		gl.BindBuffer(target, buffer);
		fprintf(GLMethodsDebugFile, "[%4d] BindBuffer(0x%x, %u)\n", gl.GetError(), target, buffer);
	}

	GLvoid DeleteBuffers(GLsizei n, const GLuint * buffers) const {
		gl.DeleteBuffers(n, buffers);
		fprintf(GLMethodsDebugFile, "[%4d] DeleteBuffers(%d, 0x%p)\n", gl.GetError(), n, buffers);
	}

	GLvoid GenBuffers(GLsizei n, GLuint * buffers) const {
		gl.GenBuffers(n, buffers);
		fprintf(GLMethodsDebugFile, "[%4d] GenBuffers(%d, 0x%p)\n", gl.GetError(), n, buffers);
	}

	GLboolean IsBuffer(GLuint buffer) const {
		GLboolean res = gl.IsBuffer(buffer);
		fprintf(GLMethodsDebugFile, "[%4d] IsBuffer(%u) -> %d\n", gl.GetError(), buffer, res);
		return res;
	}

	GLvoid BufferData(GLenum target, GLsizeiptr size, const GLvoid * data, GLenum usage) const {
		gl.BufferData(target, size, data, usage);
		fprintf(GLMethodsDebugFile, "[%4d] BufferData(0x%x, %" LL "d, 0x%p, 0x%x)\n", gl.GetError(), target, size, data, usage);
	}

	GLvoid BufferSubData(GLenum target, GLintptr offset, GLsizeiptr size, const GLvoid * data) const {
		gl.BufferSubData(target, offset, size, data);
		fprintf(GLMethodsDebugFile, "[%4d] BufferSubData(0x%x, %" LL "d, %" LL "d, 0x%p)\n", gl.GetError(), target, offset, size, data);
	}

	GLvoid GetBufferSubData(GLenum target, GLintptr offset, GLsizeiptr size, GLvoid * data) const {
		gl.GetBufferSubData(target, offset, size, data);
		fprintf(GLMethodsDebugFile, "[%4d] GetBufferSubData(0x%x, %" LL "d, %" LL "d, 0x%p)\n", gl.GetError(), target, offset, size, data);
	}

	GLvoid * MapBuffer(GLenum target, GLenum access) const {
		GLvoid * res = gl.MapBuffer(target, access);
		fprintf(GLMethodsDebugFile, "[%4d] MapBuffer(0x%x, 0x%x) -> 0x%p\n", gl.GetError(), target, access, res);
		return res;
	}

	GLboolean UnmapBuffer(GLenum target) const {
		GLboolean res = gl.UnmapBuffer(target);
		fprintf(GLMethodsDebugFile, "[%4d] UnmapBuffer(0x%x) -> %d\n", gl.GetError(), target, res);
		return res;
	}

	GLvoid GetBufferParameteriv(GLenum target, GLenum pname, GLint * params) const {
		gl.GetBufferParameteriv(target, pname, params);
		fprintf(GLMethodsDebugFile, "[%4d] GetBufferParameteriv(0x%x, 0x%x, 0x%p)\n", gl.GetError(), target, pname, params);
	}

	GLvoid GetBufferPointerv(GLenum target, GLenum pname, GLvoid ** params) const {
		gl.GetBufferPointerv(target, pname, params);
		fprintf(GLMethodsDebugFile, "[%4d] GetBufferPointerv(0x%x, 0x%x, 0x%p)\n", gl.GetError(), target, pname, params);
	}

	GLvoid BlendEquationSeparate(GLenum modeRGB, GLenum modeAlpha) const {
		gl.BlendEquationSeparate(modeRGB, modeAlpha);
		fprintf(GLMethodsDebugFile, "[%4d] BlendEquationSeparate(0x%x, 0x%x)\n", gl.GetError(), modeRGB, modeAlpha);
	}

	GLvoid DrawBuffers(GLsizei n, const GLenum * bufs) const {
		gl.DrawBuffers(n, bufs);
		fprintf(GLMethodsDebugFile, "[%4d] DrawBuffers(%d, 0x%p)\n", gl.GetError(), n, bufs);
	}

	GLvoid StencilOpSeparate(GLenum face, GLenum sfail, GLenum dpfail, GLenum dppass) const {
		gl.StencilOpSeparate(face, sfail, dpfail, dppass);
		fprintf(GLMethodsDebugFile, "[%4d] StencilOpSeparate(0x%x, 0x%x, 0x%x, 0x%x)\n", gl.GetError(), face, sfail, dpfail, dppass);
	}

	GLvoid StencilFuncSeparate(GLenum face, GLenum func, GLint ref, GLuint mask) const {
		gl.StencilFuncSeparate(face, func, ref, mask);
		fprintf(GLMethodsDebugFile, "[%4d] StencilFuncSeparate(0x%x, 0x%x, %d, %u)\n", gl.GetError(), face, func, ref, mask);
	}

	GLvoid StencilMaskSeparate(GLenum face, GLuint mask) const {
		gl.StencilMaskSeparate(face, mask);
		fprintf(GLMethodsDebugFile, "[%4d] StencilMaskSeparate(0x%x, %u)\n", gl.GetError(), face, mask);
	}

	GLvoid AttachShader(GLuint program, GLuint shader) const {
		gl.AttachShader(program, shader);
		fprintf(GLMethodsDebugFile, "[%4d] AttachShader(%u, %u)\n", gl.GetError(), program, shader);
	}

	GLvoid BindAttribLocation(GLuint program, GLuint index, const GLchar * name) const {
		gl.BindAttribLocation(program, index, name);
		fprintf(GLMethodsDebugFile, "[%4d] BindAttribLocation(%u, %u, 0x%p)\n", gl.GetError(), program, index, name);
	}

	GLvoid CompileShader(GLuint shader) const {
		gl.CompileShader(shader);
		fprintf(GLMethodsDebugFile, "[%4d] CompileShader(%u)\n", gl.GetError(), shader);
	}

	GLuint CreateProgram() const {
		GLuint res = gl.CreateProgram();
		fprintf(GLMethodsDebugFile, "[%4d] CreateProgram() -> %u\n", gl.GetError(), res);
		return res;
	}

	GLuint CreateShader(GLenum type) const {
		GLuint res = gl.CreateShader(type);
		fprintf(GLMethodsDebugFile, "[%4d] CreateShader(0x%x) -> %u\n", gl.GetError(), type, res);
		return res;
	}

	GLvoid DeleteProgram(GLuint program) const {
		gl.DeleteProgram(program);
		fprintf(GLMethodsDebugFile, "[%4d] DeleteProgram(%u)\n", gl.GetError(), program);
	}

	GLvoid DeleteShader(GLuint shader) const {
		gl.DeleteShader(shader);
		fprintf(GLMethodsDebugFile, "[%4d] DeleteShader(%u)\n", gl.GetError(), shader);
	}

	GLvoid DetachShader(GLuint program, GLuint shader) const {
		gl.DetachShader(program, shader);
		fprintf(GLMethodsDebugFile, "[%4d] DetachShader(%u, %u)\n", gl.GetError(), program, shader);
	}

	GLvoid DisableVertexAttribArray(GLuint index) const {
		gl.DisableVertexAttribArray(index);
		fprintf(GLMethodsDebugFile, "[%4d] DisableVertexAttribArray(%u)\n", gl.GetError(), index);
	}

	GLvoid EnableVertexAttribArray(GLuint index) const {
		gl.EnableVertexAttribArray(index);
		fprintf(GLMethodsDebugFile, "[%4d] EnableVertexAttribArray(%u)\n", gl.GetError(), index);
	}

	GLvoid GetActiveAttrib(GLuint program, GLuint index, GLsizei bufSize, GLsizei * length, GLint * size, GLenum * type, GLchar * name) const {
		gl.GetActiveAttrib(program, index, bufSize, length, size, type, name);
		fprintf(GLMethodsDebugFile, "[%4d] GetActiveAttrib(%u, %u, %d, 0x%p, 0x%p, 0x%p, 0x%p)\n", gl.GetError(), program, index, bufSize, length, size, type, name);
	}

	GLvoid GetActiveUniform(GLuint program, GLuint index, GLsizei bufSize, GLsizei * length, GLint * size, GLenum * type, GLchar * name) const {
		gl.GetActiveUniform(program, index, bufSize, length, size, type, name);
		fprintf(GLMethodsDebugFile, "[%4d] GetActiveUniform(%u, %u, %d, 0x%p, 0x%p, 0x%p, 0x%p)\n", gl.GetError(), program, index, bufSize, length, size, type, name);
	}

	GLvoid GetAttachedShaders(GLuint program, GLsizei maxCount, GLsizei * count, GLuint * shaders) const {
		gl.GetAttachedShaders(program, maxCount, count, shaders);
		fprintf(GLMethodsDebugFile, "[%4d] GetAttachedShaders(%u, %d, 0x%p, 0x%p)\n", gl.GetError(), program, maxCount, count, shaders);
	}

	GLint GetAttribLocation(GLuint program, const GLchar * name) const {
		GLint res = gl.GetAttribLocation(program, name);
		fprintf(GLMethodsDebugFile, "[%4d] GetAttribLocation(%u, 0x%p) -> %d\n", gl.GetError(), program, name, res);
		return res;
	}

	GLvoid GetProgramiv(GLuint program, GLenum pname, GLint * params) const {
		gl.GetProgramiv(program, pname, params);
		fprintf(GLMethodsDebugFile, "[%4d] GetProgramiv(%u, 0x%x, 0x%p)\n", gl.GetError(), program, pname, params);
	}

	GLvoid GetProgramInfoLog(GLuint program, GLsizei bufSize, GLsizei * length, GLchar * infoLog) const {
		gl.GetProgramInfoLog(program, bufSize, length, infoLog);
		fprintf(GLMethodsDebugFile, "[%4d] GetProgramInfoLog(%u, %d, 0x%p, 0x%p)\n", gl.GetError(), program, bufSize, length, infoLog);
	}

	GLvoid GetShaderiv(GLuint shader, GLenum pname, GLint * params) const {
		gl.GetShaderiv(shader, pname, params);
		fprintf(GLMethodsDebugFile, "[%4d] GetShaderiv(%u, 0x%x, 0x%p)\n", gl.GetError(), shader, pname, params);
	}

	GLvoid GetShaderInfoLog(GLuint shader, GLsizei bufSize, GLsizei * length, GLchar * infoLog) const {
		gl.GetShaderInfoLog(shader, bufSize, length, infoLog);
		fprintf(GLMethodsDebugFile, "[%4d] GetShaderInfoLog(%u, %d, 0x%p, 0x%p)\n", gl.GetError(), shader, bufSize, length, infoLog);
	}

	GLvoid GetShaderSource(GLuint shader, GLsizei bufSize, GLsizei * length, GLchar * source) const {
		gl.GetShaderSource(shader, bufSize, length, source);
		fprintf(GLMethodsDebugFile, "[%4d] GetShaderSource(%u, %d, 0x%p, 0x%p)\n", gl.GetError(), shader, bufSize, length, source);
	}

	GLint GetUniformLocation(GLuint program, const GLchar * name) const {
		GLint res = gl.GetUniformLocation(program, name);
		fprintf(GLMethodsDebugFile, "[%4d] GetUniformLocation(%u, 0x%p) -> %d\n", gl.GetError(), program, name, res);
		return res;
	}

	// GLvoid GetUniformfv(GLuint program, GLint location, GLfloat * params) const {
	// 	gl.GetUniformfv(program, location, params);
	// 	fprintf(GLMethodsDebugFile, "[%4d] GetUniformfv(%u, %d, 0x%p)\n", gl.GetError(), program, location, params);
	// }

	// GLvoid GetUniformiv(GLuint program, GLint location, GLint * params) const {
	// 	gl.GetUniformiv(program, location, params);
	// 	fprintf(GLMethodsDebugFile, "[%4d] GetUniformiv(%u, %d, 0x%p)\n", gl.GetError(), program, location, params);
	// }

	GLvoid GetVertexAttribdv(GLuint index, GLenum pname, GLdouble * params) const {
		gl.GetVertexAttribdv(index, pname, params);
		fprintf(GLMethodsDebugFile, "[%4d] GetVertexAttribdv(%u, 0x%x, 0x%p)\n", gl.GetError(), index, pname, params);
	}

	GLvoid GetVertexAttribfv(GLuint index, GLenum pname, GLfloat * params) const {
		gl.GetVertexAttribfv(index, pname, params);
		fprintf(GLMethodsDebugFile, "[%4d] GetVertexAttribfv(%u, 0x%x, 0x%p)\n", gl.GetError(), index, pname, params);
	}

	GLvoid GetVertexAttribiv(GLuint index, GLenum pname, GLint * params) const {
		gl.GetVertexAttribiv(index, pname, params);
		fprintf(GLMethodsDebugFile, "[%4d] GetVertexAttribiv(%u, 0x%x, 0x%p)\n", gl.GetError(), index, pname, params);
	}

	GLvoid GetVertexAttribPointerv(GLuint index, GLenum pname, GLvoid ** pointer) const {
		gl.GetVertexAttribPointerv(index, pname, pointer);
		fprintf(GLMethodsDebugFile, "[%4d] GetVertexAttribPointerv(%u, 0x%x, 0x%p)\n", gl.GetError(), index, pname, pointer);
	}

	GLboolean IsProgram(GLuint program) const {
		GLboolean res = gl.IsProgram(program);
		fprintf(GLMethodsDebugFile, "[%4d] IsProgram(%u) -> %d\n", gl.GetError(), program, res);
		return res;
	}

	GLboolean IsShader(GLuint shader) const {
		GLboolean res = gl.IsShader(shader);
		fprintf(GLMethodsDebugFile, "[%4d] IsShader(%u) -> %d\n", gl.GetError(), shader, res);
		return res;
	}

	GLvoid LinkProgram(GLuint program) const {
		gl.LinkProgram(program);
		fprintf(GLMethodsDebugFile, "[%4d] LinkProgram(%u)\n", gl.GetError(), program);
	}

	GLvoid ShaderSource(GLuint shader, GLsizei count, const GLchar * const* string, const GLint * length) const {
		gl.ShaderSource(shader, count, string, length);
		fprintf(GLMethodsDebugFile, "[%4d] ShaderSource(%u, %d, 0x%p, 0x%p)\n", gl.GetError(), shader, count, string, length);
	}

	GLvoid UseProgram(GLuint program) const {
		gl.UseProgram(program);
		fprintf(GLMethodsDebugFile, "[%4d] UseProgram(%u)\n", gl.GetError(), program);
	}

	GLvoid Uniform1f(GLint location, GLfloat v0) const {
		gl.Uniform1f(location, v0);
		fprintf(GLMethodsDebugFile, "[%4d] Uniform1f(%d, %f)\n", gl.GetError(), location, v0);
	}

	GLvoid Uniform2f(GLint location, GLfloat v0, GLfloat v1) const {
		gl.Uniform2f(location, v0, v1);
		fprintf(GLMethodsDebugFile, "[%4d] Uniform2f(%d, %f, %f)\n", gl.GetError(), location, v0, v1);
	}

	GLvoid Uniform3f(GLint location, GLfloat v0, GLfloat v1, GLfloat v2) const {
		gl.Uniform3f(location, v0, v1, v2);
		fprintf(GLMethodsDebugFile, "[%4d] Uniform3f(%d, %f, %f, %f)\n", gl.GetError(), location, v0, v1, v2);
	}

	GLvoid Uniform4f(GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3) const {
		gl.Uniform4f(location, v0, v1, v2, v3);
		fprintf(GLMethodsDebugFile, "[%4d] Uniform4f(%d, %f, %f, %f, %f)\n", gl.GetError(), location, v0, v1, v2, v3);
	}

	GLvoid Uniform1i(GLint location, GLint v0) const {
		gl.Uniform1i(location, v0);
		fprintf(GLMethodsDebugFile, "[%4d] Uniform1i(%d, %d)\n", gl.GetError(), location, v0);
	}

	GLvoid Uniform2i(GLint location, GLint v0, GLint v1) const {
		gl.Uniform2i(location, v0, v1);
		fprintf(GLMethodsDebugFile, "[%4d] Uniform2i(%d, %d, %d)\n", gl.GetError(), location, v0, v1);
	}

	GLvoid Uniform3i(GLint location, GLint v0, GLint v1, GLint v2) const {
		gl.Uniform3i(location, v0, v1, v2);
		fprintf(GLMethodsDebugFile, "[%4d] Uniform3i(%d, %d, %d, %d)\n", gl.GetError(), location, v0, v1, v2);
	}

	GLvoid Uniform4i(GLint location, GLint v0, GLint v1, GLint v2, GLint v3) const {
		gl.Uniform4i(location, v0, v1, v2, v3);
		fprintf(GLMethodsDebugFile, "[%4d] Uniform4i(%d, %d, %d, %d, %d)\n", gl.GetError(), location, v0, v1, v2, v3);
	}

	GLvoid Uniform1fv(GLint location, GLsizei count, const GLfloat * value) const {
		gl.Uniform1fv(location, count, value);
		fprintf(GLMethodsDebugFile, "[%4d] Uniform1fv(%d, %d, 0x%p)\n", gl.GetError(), location, count, value);
	}

	GLvoid Uniform2fv(GLint location, GLsizei count, const GLfloat * value) const {
		gl.Uniform2fv(location, count, value);
		fprintf(GLMethodsDebugFile, "[%4d] Uniform2fv(%d, %d, 0x%p)\n", gl.GetError(), location, count, value);
	}

	GLvoid Uniform3fv(GLint location, GLsizei count, const GLfloat * value) const {
		gl.Uniform3fv(location, count, value);
		fprintf(GLMethodsDebugFile, "[%4d] Uniform3fv(%d, %d, 0x%p)\n", gl.GetError(), location, count, value);
	}

	GLvoid Uniform4fv(GLint location, GLsizei count, const GLfloat * value) const {
		gl.Uniform4fv(location, count, value);
		fprintf(GLMethodsDebugFile, "[%4d] Uniform4fv(%d, %d, 0x%p)\n", gl.GetError(), location, count, value);
	}

	GLvoid Uniform1iv(GLint location, GLsizei count, const GLint * value) const {
		gl.Uniform1iv(location, count, value);
		fprintf(GLMethodsDebugFile, "[%4d] Uniform1iv(%d, %d, 0x%p)\n", gl.GetError(), location, count, value);
	}

	GLvoid Uniform2iv(GLint location, GLsizei count, const GLint * value) const {
		gl.Uniform2iv(location, count, value);
		fprintf(GLMethodsDebugFile, "[%4d] Uniform2iv(%d, %d, 0x%p)\n", gl.GetError(), location, count, value);
	}

	GLvoid Uniform3iv(GLint location, GLsizei count, const GLint * value) const {
		gl.Uniform3iv(location, count, value);
		fprintf(GLMethodsDebugFile, "[%4d] Uniform3iv(%d, %d, 0x%p)\n", gl.GetError(), location, count, value);
	}

	GLvoid Uniform4iv(GLint location, GLsizei count, const GLint * value) const {
		gl.Uniform4iv(location, count, value);
		fprintf(GLMethodsDebugFile, "[%4d] Uniform4iv(%d, %d, 0x%p)\n", gl.GetError(), location, count, value);
	}

	GLvoid UniformMatrix2fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat * value) const {
		gl.UniformMatrix2fv(location, count, transpose, value);
		fprintf(GLMethodsDebugFile, "[%4d] UniformMatrix2fv(%d, %d, %d, 0x%p)\n", gl.GetError(), location, count, transpose, value);
	}

	GLvoid UniformMatrix3fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat * value) const {
		gl.UniformMatrix3fv(location, count, transpose, value);
		fprintf(GLMethodsDebugFile, "[%4d] UniformMatrix3fv(%d, %d, %d, 0x%p)\n", gl.GetError(), location, count, transpose, value);
	}

	GLvoid UniformMatrix4fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat * value) const {
		gl.UniformMatrix4fv(location, count, transpose, value);
		fprintf(GLMethodsDebugFile, "[%4d] UniformMatrix4fv(%d, %d, %d, 0x%p)\n", gl.GetError(), location, count, transpose, value);
	}

	GLvoid ValidateProgram(GLuint program) const {
		gl.ValidateProgram(program);
		fprintf(GLMethodsDebugFile, "[%4d] ValidateProgram(%u)\n", gl.GetError(), program);
	}

	GLvoid VertexAttrib1d(GLuint index, GLdouble x) const {
		gl.VertexAttrib1d(index, x);
		fprintf(GLMethodsDebugFile, "[%4d] VertexAttrib1d(%u, %lf)\n", gl.GetError(), index, x);
	}

	GLvoid VertexAttrib1dv(GLuint index, const GLdouble * v) const {
		gl.VertexAttrib1dv(index, v);
		fprintf(GLMethodsDebugFile, "[%4d] VertexAttrib1dv(%u, 0x%p)\n", gl.GetError(), index, v);
	}

	GLvoid VertexAttrib1f(GLuint index, GLfloat x) const {
		gl.VertexAttrib1f(index, x);
		fprintf(GLMethodsDebugFile, "[%4d] VertexAttrib1f(%u, %f)\n", gl.GetError(), index, x);
	}

	GLvoid VertexAttrib1fv(GLuint index, const GLfloat * v) const {
		gl.VertexAttrib1fv(index, v);
		fprintf(GLMethodsDebugFile, "[%4d] VertexAttrib1fv(%u, 0x%p)\n", gl.GetError(), index, v);
	}

	GLvoid VertexAttrib1s(GLuint index, GLshort x) const {
		gl.VertexAttrib1s(index, x);
		fprintf(GLMethodsDebugFile, "[%4d] VertexAttrib1s(%u, %d)\n", gl.GetError(), index, x);
	}

	GLvoid VertexAttrib1sv(GLuint index, const GLshort * v) const {
		gl.VertexAttrib1sv(index, v);
		fprintf(GLMethodsDebugFile, "[%4d] VertexAttrib1sv(%u, 0x%p)\n", gl.GetError(), index, v);
	}

	GLvoid VertexAttrib2d(GLuint index, GLdouble x, GLdouble y) const {
		gl.VertexAttrib2d(index, x, y);
		fprintf(GLMethodsDebugFile, "[%4d] VertexAttrib2d(%u, %lf, %lf)\n", gl.GetError(), index, x, y);
	}

	GLvoid VertexAttrib2dv(GLuint index, const GLdouble * v) const {
		gl.VertexAttrib2dv(index, v);
		fprintf(GLMethodsDebugFile, "[%4d] VertexAttrib2dv(%u, 0x%p)\n", gl.GetError(), index, v);
	}

	GLvoid VertexAttrib2f(GLuint index, GLfloat x, GLfloat y) const {
		gl.VertexAttrib2f(index, x, y);
		fprintf(GLMethodsDebugFile, "[%4d] VertexAttrib2f(%u, %f, %f)\n", gl.GetError(), index, x, y);
	}

	GLvoid VertexAttrib2fv(GLuint index, const GLfloat * v) const {
		gl.VertexAttrib2fv(index, v);
		fprintf(GLMethodsDebugFile, "[%4d] VertexAttrib2fv(%u, 0x%p)\n", gl.GetError(), index, v);
	}

	GLvoid VertexAttrib2s(GLuint index, GLshort x, GLshort y) const {
		gl.VertexAttrib2s(index, x, y);
		fprintf(GLMethodsDebugFile, "[%4d] VertexAttrib2s(%u, %d, %d)\n", gl.GetError(), index, x, y);
	}

	GLvoid VertexAttrib2sv(GLuint index, const GLshort * v) const {
		gl.VertexAttrib2sv(index, v);
		fprintf(GLMethodsDebugFile, "[%4d] VertexAttrib2sv(%u, 0x%p)\n", gl.GetError(), index, v);
	}

	GLvoid VertexAttrib3d(GLuint index, GLdouble x, GLdouble y, GLdouble z) const {
		gl.VertexAttrib3d(index, x, y, z);
		fprintf(GLMethodsDebugFile, "[%4d] VertexAttrib3d(%u, %lf, %lf, %lf)\n", gl.GetError(), index, x, y, z);
	}

	GLvoid VertexAttrib3dv(GLuint index, const GLdouble * v) const {
		gl.VertexAttrib3dv(index, v);
		fprintf(GLMethodsDebugFile, "[%4d] VertexAttrib3dv(%u, 0x%p)\n", gl.GetError(), index, v);
	}

	GLvoid VertexAttrib3f(GLuint index, GLfloat x, GLfloat y, GLfloat z) const {
		gl.VertexAttrib3f(index, x, y, z);
		fprintf(GLMethodsDebugFile, "[%4d] VertexAttrib3f(%u, %f, %f, %f)\n", gl.GetError(), index, x, y, z);
	}

	GLvoid VertexAttrib3fv(GLuint index, const GLfloat * v) const {
		gl.VertexAttrib3fv(index, v);
		fprintf(GLMethodsDebugFile, "[%4d] VertexAttrib3fv(%u, 0x%p)\n", gl.GetError(), index, v);
	}

	GLvoid VertexAttrib3s(GLuint index, GLshort x, GLshort y, GLshort z) const {
		gl.VertexAttrib3s(index, x, y, z);
		fprintf(GLMethodsDebugFile, "[%4d] VertexAttrib3s(%u, %d, %d, %d)\n", gl.GetError(), index, x, y, z);
	}

	GLvoid VertexAttrib3sv(GLuint index, const GLshort * v) const {
		gl.VertexAttrib3sv(index, v);
		fprintf(GLMethodsDebugFile, "[%4d] VertexAttrib3sv(%u, 0x%p)\n", gl.GetError(), index, v);
	}

	GLvoid VertexAttrib4Nbv(GLuint index, const GLbyte * v) const {
		gl.VertexAttrib4Nbv(index, v);
		fprintf(GLMethodsDebugFile, "[%4d] VertexAttrib4Nbv(%u, 0x%p)\n", gl.GetError(), index, v);
	}

	GLvoid VertexAttrib4Niv(GLuint index, const GLint * v) const {
		gl.VertexAttrib4Niv(index, v);
		fprintf(GLMethodsDebugFile, "[%4d] VertexAttrib4Niv(%u, 0x%p)\n", gl.GetError(), index, v);
	}

	GLvoid VertexAttrib4Nsv(GLuint index, const GLshort * v) const {
		gl.VertexAttrib4Nsv(index, v);
		fprintf(GLMethodsDebugFile, "[%4d] VertexAttrib4Nsv(%u, 0x%p)\n", gl.GetError(), index, v);
	}

	GLvoid VertexAttrib4Nub(GLuint index, GLubyte x, GLubyte y, GLubyte z, GLubyte w) const {
		gl.VertexAttrib4Nub(index, x, y, z, w);
		fprintf(GLMethodsDebugFile, "[%4d] VertexAttrib4Nub(%u, %u, %u, %u, %u)\n", gl.GetError(), index, x, y, z, w);
	}

	GLvoid VertexAttrib4Nubv(GLuint index, const GLubyte * v) const {
		gl.VertexAttrib4Nubv(index, v);
		fprintf(GLMethodsDebugFile, "[%4d] VertexAttrib4Nubv(%u, 0x%p)\n", gl.GetError(), index, v);
	}

	GLvoid VertexAttrib4Nuiv(GLuint index, const GLuint * v) const {
		gl.VertexAttrib4Nuiv(index, v);
		fprintf(GLMethodsDebugFile, "[%4d] VertexAttrib4Nuiv(%u, 0x%p)\n", gl.GetError(), index, v);
	}

	GLvoid VertexAttrib4Nusv(GLuint index, const GLushort * v) const {
		gl.VertexAttrib4Nusv(index, v);
		fprintf(GLMethodsDebugFile, "[%4d] VertexAttrib4Nusv(%u, 0x%p)\n", gl.GetError(), index, v);
	}

	GLvoid VertexAttrib4bv(GLuint index, const GLbyte * v) const {
		gl.VertexAttrib4bv(index, v);
		fprintf(GLMethodsDebugFile, "[%4d] VertexAttrib4bv(%u, 0x%p)\n", gl.GetError(), index, v);
	}

	GLvoid VertexAttrib4d(GLuint index, GLdouble x, GLdouble y, GLdouble z, GLdouble w) const {
		gl.VertexAttrib4d(index, x, y, z, w);
		fprintf(GLMethodsDebugFile, "[%4d] VertexAttrib4d(%u, %lf, %lf, %lf, %lf)\n", gl.GetError(), index, x, y, z, w);
	}

	GLvoid VertexAttrib4dv(GLuint index, const GLdouble * v) const {
		gl.VertexAttrib4dv(index, v);
		fprintf(GLMethodsDebugFile, "[%4d] VertexAttrib4dv(%u, 0x%p)\n", gl.GetError(), index, v);
	}

	GLvoid VertexAttrib4f(GLuint index, GLfloat x, GLfloat y, GLfloat z, GLfloat w) const {
		gl.VertexAttrib4f(index, x, y, z, w);
		fprintf(GLMethodsDebugFile, "[%4d] VertexAttrib4f(%u, %f, %f, %f, %f)\n", gl.GetError(), index, x, y, z, w);
	}

	GLvoid VertexAttrib4fv(GLuint index, const GLfloat * v) const {
		gl.VertexAttrib4fv(index, v);
		fprintf(GLMethodsDebugFile, "[%4d] VertexAttrib4fv(%u, 0x%p)\n", gl.GetError(), index, v);
	}

	GLvoid VertexAttrib4iv(GLuint index, const GLint * v) const {
		gl.VertexAttrib4iv(index, v);
		fprintf(GLMethodsDebugFile, "[%4d] VertexAttrib4iv(%u, 0x%p)\n", gl.GetError(), index, v);
	}

	GLvoid VertexAttrib4s(GLuint index, GLshort x, GLshort y, GLshort z, GLshort w) const {
		gl.VertexAttrib4s(index, x, y, z, w);
		fprintf(GLMethodsDebugFile, "[%4d] VertexAttrib4s(%u, %d, %d, %d, %d)\n", gl.GetError(), index, x, y, z, w);
	}

	GLvoid VertexAttrib4sv(GLuint index, const GLshort * v) const {
		gl.VertexAttrib4sv(index, v);
		fprintf(GLMethodsDebugFile, "[%4d] VertexAttrib4sv(%u, 0x%p)\n", gl.GetError(), index, v);
	}

	GLvoid VertexAttrib4ubv(GLuint index, const GLubyte * v) const {
		gl.VertexAttrib4ubv(index, v);
		fprintf(GLMethodsDebugFile, "[%4d] VertexAttrib4ubv(%u, 0x%p)\n", gl.GetError(), index, v);
	}

	GLvoid VertexAttrib4uiv(GLuint index, const GLuint * v) const {
		gl.VertexAttrib4uiv(index, v);
		fprintf(GLMethodsDebugFile, "[%4d] VertexAttrib4uiv(%u, 0x%p)\n", gl.GetError(), index, v);
	}

	GLvoid VertexAttrib4usv(GLuint index, const GLushort * v) const {
		gl.VertexAttrib4usv(index, v);
		fprintf(GLMethodsDebugFile, "[%4d] VertexAttrib4usv(%u, 0x%p)\n", gl.GetError(), index, v);
	}

	// GLvoid VertexAttribPointer(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid * pointer) const {
	// 	gl.VertexAttribPointer(index, size, type, normalized, stride, pointer);
	// 	fprintf(GLMethodsDebugFile, "[%4d] VertexAttribPointer(%u, %d, 0x%x, %d, %d, 0x%p)\n", gl.GetError(), index, size, type, normalized, stride, pointer);
	// }

	GLvoid UniformMatrix2x3fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat * value) const {
		gl.UniformMatrix2x3fv(location, count, transpose, value);
		fprintf(GLMethodsDebugFile, "[%4d] UniformMatrix2x3fv(%d, %d, %d, 0x%p)\n", gl.GetError(), location, count, transpose, value);
	}

	GLvoid UniformMatrix3x2fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat * value) const {
		gl.UniformMatrix3x2fv(location, count, transpose, value);
		fprintf(GLMethodsDebugFile, "[%4d] UniformMatrix3x2fv(%d, %d, %d, 0x%p)\n", gl.GetError(), location, count, transpose, value);
	}

	GLvoid UniformMatrix2x4fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat * value) const {
		gl.UniformMatrix2x4fv(location, count, transpose, value);
		fprintf(GLMethodsDebugFile, "[%4d] UniformMatrix2x4fv(%d, %d, %d, 0x%p)\n", gl.GetError(), location, count, transpose, value);
	}

	GLvoid UniformMatrix4x2fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat * value) const {
		gl.UniformMatrix4x2fv(location, count, transpose, value);
		fprintf(GLMethodsDebugFile, "[%4d] UniformMatrix4x2fv(%d, %d, %d, 0x%p)\n", gl.GetError(), location, count, transpose, value);
	}

	GLvoid UniformMatrix3x4fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat * value) const {
		gl.UniformMatrix3x4fv(location, count, transpose, value);
		fprintf(GLMethodsDebugFile, "[%4d] UniformMatrix3x4fv(%d, %d, %d, 0x%p)\n", gl.GetError(), location, count, transpose, value);
	}

	GLvoid UniformMatrix4x3fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat * value) const {
		gl.UniformMatrix4x3fv(location, count, transpose, value);
		fprintf(GLMethodsDebugFile, "[%4d] UniformMatrix4x3fv(%d, %d, %d, 0x%p)\n", gl.GetError(), location, count, transpose, value);
	}

	GLvoid ColorMaski(GLuint index, GLboolean r, GLboolean g, GLboolean b, GLboolean a) const {
		gl.ColorMaski(index, r, g, b, a);
		fprintf(GLMethodsDebugFile, "[%4d] ColorMaski(%u, %d, %d, %d, %d)\n", gl.GetError(), index, r, g, b, a);
	}

	GLvoid GetBooleani_v(GLenum target, GLuint index, GLboolean * data) const {
		gl.GetBooleani_v(target, index, data);
		fprintf(GLMethodsDebugFile, "[%4d] GetBooleani_v(0x%x, %u, 0x%p)\n", gl.GetError(), target, index, data);
	}

	GLvoid GetIntegeri_v(GLenum target, GLuint index, GLint * data) const {
		gl.GetIntegeri_v(target, index, data);
		fprintf(GLMethodsDebugFile, "[%4d] GetIntegeri_v(0x%x, %u, 0x%p)\n", gl.GetError(), target, index, data);
	}

	GLvoid Enablei(GLenum target, GLuint index) const {
		gl.Enablei(target, index);
		fprintf(GLMethodsDebugFile, "[%4d] Enablei(0x%x, %u)\n", gl.GetError(), target, index);
	}

	GLvoid Disablei(GLenum target, GLuint index) const {
		gl.Disablei(target, index);
		fprintf(GLMethodsDebugFile, "[%4d] Disablei(0x%x, %u)\n", gl.GetError(), target, index);
	}

	GLboolean IsEnabledi(GLenum target, GLuint index) const {
		GLboolean res = gl.IsEnabledi(target, index);
		fprintf(GLMethodsDebugFile, "[%4d] IsEnabledi(0x%x, %u) -> %d\n", gl.GetError(), target, index, res);
		return res;
	}

	GLvoid BeginTransformFeedback(GLenum primitiveMode) const {
		gl.BeginTransformFeedback(primitiveMode);
		fprintf(GLMethodsDebugFile, "[%4d] BeginTransformFeedback(0x%x)\n", gl.GetError(), primitiveMode);
	}

	GLvoid EndTransformFeedback() const {
		gl.EndTransformFeedback();
		fprintf(GLMethodsDebugFile, "[%4d] EndTransformFeedback()\n", gl.GetError());
	}

	GLvoid BindBufferRange(GLenum target, GLuint index, GLuint buffer, GLintptr offset, GLsizeiptr size) const {
		gl.BindBufferRange(target, index, buffer, offset, size);
		fprintf(GLMethodsDebugFile, "[%4d] BindBufferRange(0x%x, %u, %u, %" LL "d, %" LL "d)\n", gl.GetError(), target, index, buffer, offset, size);
	}

	GLvoid BindBufferBase(GLenum target, GLuint index, GLuint buffer) const {
		gl.BindBufferBase(target, index, buffer);
		fprintf(GLMethodsDebugFile, "[%4d] BindBufferBase(0x%x, %u, %u)\n", gl.GetError(), target, index, buffer);
	}

	GLvoid TransformFeedbackVaryings(GLuint program, GLsizei count, const GLchar * const* varyings, GLenum bufferMode) const {
		gl.TransformFeedbackVaryings(program, count, varyings, bufferMode);
		fprintf(GLMethodsDebugFile, "[%4d] TransformFeedbackVaryings(%u, %d, 0x%p, 0x%x)\n", gl.GetError(), program, count, varyings, bufferMode);
	}

	GLvoid GetTransformFeedbackVarying(GLuint program, GLuint index, GLsizei bufSize, GLsizei * length, GLsizei * size, GLenum * type, GLchar * name) const {
		gl.GetTransformFeedbackVarying(program, index, bufSize, length, size, type, name);
		fprintf(GLMethodsDebugFile, "[%4d] GetTransformFeedbackVarying(%u, %u, %d, 0x%p, 0x%p, 0x%p, 0x%p)\n", gl.GetError(), program, index, bufSize, length, size, type, name);
	}

	GLvoid ClampColor(GLenum target, GLenum clamp) const {
		gl.ClampColor(target, clamp);
		fprintf(GLMethodsDebugFile, "[%4d] ClampColor(0x%x, 0x%x)\n", gl.GetError(), target, clamp);
	}

	GLvoid BeginConditionalRender(GLuint id, GLenum mode) const {
		gl.BeginConditionalRender(id, mode);
		fprintf(GLMethodsDebugFile, "[%4d] BeginConditionalRender(%u, 0x%x)\n", gl.GetError(), id, mode);
	}

	GLvoid EndConditionalRender() const {
		gl.EndConditionalRender();
		fprintf(GLMethodsDebugFile, "[%4d] EndConditionalRender()\n", gl.GetError());
	}

	// GLvoid VertexAttribIPointer(GLuint index, GLint size, GLenum type, GLsizei stride, const GLvoid * pointer) const {
	// 	gl.VertexAttribIPointer(index, size, type, stride, pointer);
	// 	fprintf(GLMethodsDebugFile, "[%4d] VertexAttribIPointer(%u, %d, 0x%x, %d, 0x%p)\n", gl.GetError(), index, size, type, stride, pointer);
	// }

	GLvoid GetVertexAttribIiv(GLuint index, GLenum pname, GLint * params) const {
		gl.GetVertexAttribIiv(index, pname, params);
		fprintf(GLMethodsDebugFile, "[%4d] GetVertexAttribIiv(%u, 0x%x, 0x%p)\n", gl.GetError(), index, pname, params);
	}

	GLvoid GetVertexAttribIuiv(GLuint index, GLenum pname, GLuint * params) const {
		gl.GetVertexAttribIuiv(index, pname, params);
		fprintf(GLMethodsDebugFile, "[%4d] GetVertexAttribIuiv(%u, 0x%x, 0x%p)\n", gl.GetError(), index, pname, params);
	}

	GLvoid VertexAttribI1i(GLuint index, GLint x) const {
		gl.VertexAttribI1i(index, x);
		fprintf(GLMethodsDebugFile, "[%4d] VertexAttribI1i(%u, %d)\n", gl.GetError(), index, x);
	}

	GLvoid VertexAttribI2i(GLuint index, GLint x, GLint y) const {
		gl.VertexAttribI2i(index, x, y);
		fprintf(GLMethodsDebugFile, "[%4d] VertexAttribI2i(%u, %d, %d)\n", gl.GetError(), index, x, y);
	}

	GLvoid VertexAttribI3i(GLuint index, GLint x, GLint y, GLint z) const {
		gl.VertexAttribI3i(index, x, y, z);
		fprintf(GLMethodsDebugFile, "[%4d] VertexAttribI3i(%u, %d, %d, %d)\n", gl.GetError(), index, x, y, z);
	}

	GLvoid VertexAttribI4i(GLuint index, GLint x, GLint y, GLint z, GLint w) const {
		gl.VertexAttribI4i(index, x, y, z, w);
		fprintf(GLMethodsDebugFile, "[%4d] VertexAttribI4i(%u, %d, %d, %d, %d)\n", gl.GetError(), index, x, y, z, w);
	}

	GLvoid VertexAttribI1ui(GLuint index, GLuint x) const {
		gl.VertexAttribI1ui(index, x);
		fprintf(GLMethodsDebugFile, "[%4d] VertexAttribI1ui(%u, %u)\n", gl.GetError(), index, x);
	}

	GLvoid VertexAttribI2ui(GLuint index, GLuint x, GLuint y) const {
		gl.VertexAttribI2ui(index, x, y);
		fprintf(GLMethodsDebugFile, "[%4d] VertexAttribI2ui(%u, %u, %u)\n", gl.GetError(), index, x, y);
	}

	GLvoid VertexAttribI3ui(GLuint index, GLuint x, GLuint y, GLuint z) const {
		gl.VertexAttribI3ui(index, x, y, z);
		fprintf(GLMethodsDebugFile, "[%4d] VertexAttribI3ui(%u, %u, %u, %u)\n", gl.GetError(), index, x, y, z);
	}

	GLvoid VertexAttribI4ui(GLuint index, GLuint x, GLuint y, GLuint z, GLuint w) const {
		gl.VertexAttribI4ui(index, x, y, z, w);
		fprintf(GLMethodsDebugFile, "[%4d] VertexAttribI4ui(%u, %u, %u, %u, %u)\n", gl.GetError(), index, x, y, z, w);
	}

	GLvoid VertexAttribI1iv(GLuint index, const GLint * v) const {
		gl.VertexAttribI1iv(index, v);
		fprintf(GLMethodsDebugFile, "[%4d] VertexAttribI1iv(%u, 0x%p)\n", gl.GetError(), index, v);
	}

	GLvoid VertexAttribI2iv(GLuint index, const GLint * v) const {
		gl.VertexAttribI2iv(index, v);
		fprintf(GLMethodsDebugFile, "[%4d] VertexAttribI2iv(%u, 0x%p)\n", gl.GetError(), index, v);
	}

	GLvoid VertexAttribI3iv(GLuint index, const GLint * v) const {
		gl.VertexAttribI3iv(index, v);
		fprintf(GLMethodsDebugFile, "[%4d] VertexAttribI3iv(%u, 0x%p)\n", gl.GetError(), index, v);
	}

	GLvoid VertexAttribI4iv(GLuint index, const GLint * v) const {
		gl.VertexAttribI4iv(index, v);
		fprintf(GLMethodsDebugFile, "[%4d] VertexAttribI4iv(%u, 0x%p)\n", gl.GetError(), index, v);
	}

	GLvoid VertexAttribI1uiv(GLuint index, const GLuint * v) const {
		gl.VertexAttribI1uiv(index, v);
		fprintf(GLMethodsDebugFile, "[%4d] VertexAttribI1uiv(%u, 0x%p)\n", gl.GetError(), index, v);
	}

	GLvoid VertexAttribI2uiv(GLuint index, const GLuint * v) const {
		gl.VertexAttribI2uiv(index, v);
		fprintf(GLMethodsDebugFile, "[%4d] VertexAttribI2uiv(%u, 0x%p)\n", gl.GetError(), index, v);
	}

	GLvoid VertexAttribI3uiv(GLuint index, const GLuint * v) const {
		gl.VertexAttribI3uiv(index, v);
		fprintf(GLMethodsDebugFile, "[%4d] VertexAttribI3uiv(%u, 0x%p)\n", gl.GetError(), index, v);
	}

	GLvoid VertexAttribI4uiv(GLuint index, const GLuint * v) const {
		gl.VertexAttribI4uiv(index, v);
		fprintf(GLMethodsDebugFile, "[%4d] VertexAttribI4uiv(%u, 0x%p)\n", gl.GetError(), index, v);
	}

	GLvoid VertexAttribI4bv(GLuint index, const GLbyte * v) const {
		gl.VertexAttribI4bv(index, v);
		fprintf(GLMethodsDebugFile, "[%4d] VertexAttribI4bv(%u, 0x%p)\n", gl.GetError(), index, v);
	}

	GLvoid VertexAttribI4sv(GLuint index, const GLshort * v) const {
		gl.VertexAttribI4sv(index, v);
		fprintf(GLMethodsDebugFile, "[%4d] VertexAttribI4sv(%u, 0x%p)\n", gl.GetError(), index, v);
	}

	GLvoid VertexAttribI4ubv(GLuint index, const GLubyte * v) const {
		gl.VertexAttribI4ubv(index, v);
		fprintf(GLMethodsDebugFile, "[%4d] VertexAttribI4ubv(%u, 0x%p)\n", gl.GetError(), index, v);
	}

	GLvoid VertexAttribI4usv(GLuint index, const GLushort * v) const {
		gl.VertexAttribI4usv(index, v);
		fprintf(GLMethodsDebugFile, "[%4d] VertexAttribI4usv(%u, 0x%p)\n", gl.GetError(), index, v);
	}

	// GLvoid GetUniformuiv(GLuint program, GLint location, GLuint * params) const {
	// 	gl.GetUniformuiv(program, location, params);
	// 	fprintf(GLMethodsDebugFile, "[%4d] GetUniformuiv(%u, %d, 0x%p)\n", gl.GetError(), program, location, params);
	// }

	GLvoid BindFragDataLocation(GLuint program, GLuint color, const GLchar * name) const {
		gl.BindFragDataLocation(program, color, name);
		fprintf(GLMethodsDebugFile, "[%4d] BindFragDataLocation(%u, %u, 0x%p)\n", gl.GetError(), program, color, name);
	}

	GLint GetFragDataLocation(GLuint program, const GLchar * name) const {
		GLint res = gl.GetFragDataLocation(program, name);
		fprintf(GLMethodsDebugFile, "[%4d] GetFragDataLocation(%u, 0x%p) -> %d\n", gl.GetError(), program, name, res);
		return res;
	}

	GLvoid Uniform1ui(GLint location, GLuint v0) const {
		gl.Uniform1ui(location, v0);
		fprintf(GLMethodsDebugFile, "[%4d] Uniform1ui(%d, %u)\n", gl.GetError(), location, v0);
	}

	GLvoid Uniform2ui(GLint location, GLuint v0, GLuint v1) const {
		gl.Uniform2ui(location, v0, v1);
		fprintf(GLMethodsDebugFile, "[%4d] Uniform2ui(%d, %u, %u)\n", gl.GetError(), location, v0, v1);
	}

	GLvoid Uniform3ui(GLint location, GLuint v0, GLuint v1, GLuint v2) const {
		gl.Uniform3ui(location, v0, v1, v2);
		fprintf(GLMethodsDebugFile, "[%4d] Uniform3ui(%d, %u, %u, %u)\n", gl.GetError(), location, v0, v1, v2);
	}

	GLvoid Uniform4ui(GLint location, GLuint v0, GLuint v1, GLuint v2, GLuint v3) const {
		gl.Uniform4ui(location, v0, v1, v2, v3);
		fprintf(GLMethodsDebugFile, "[%4d] Uniform4ui(%d, %u, %u, %u, %u)\n", gl.GetError(), location, v0, v1, v2, v3);
	}

	GLvoid Uniform1uiv(GLint location, GLsizei count, const GLuint * value) const {
		gl.Uniform1uiv(location, count, value);
		fprintf(GLMethodsDebugFile, "[%4d] Uniform1uiv(%d, %d, 0x%p)\n", gl.GetError(), location, count, value);
	}

	GLvoid Uniform2uiv(GLint location, GLsizei count, const GLuint * value) const {
		gl.Uniform2uiv(location, count, value);
		fprintf(GLMethodsDebugFile, "[%4d] Uniform2uiv(%d, %d, 0x%p)\n", gl.GetError(), location, count, value);
	}

	GLvoid Uniform3uiv(GLint location, GLsizei count, const GLuint * value) const {
		gl.Uniform3uiv(location, count, value);
		fprintf(GLMethodsDebugFile, "[%4d] Uniform3uiv(%d, %d, 0x%p)\n", gl.GetError(), location, count, value);
	}

	GLvoid Uniform4uiv(GLint location, GLsizei count, const GLuint * value) const {
		gl.Uniform4uiv(location, count, value);
		fprintf(GLMethodsDebugFile, "[%4d] Uniform4uiv(%d, %d, 0x%p)\n", gl.GetError(), location, count, value);
	}

	GLvoid TexParameterIiv(GLenum target, GLenum pname, const GLint * params) const {
		gl.TexParameterIiv(target, pname, params);
		fprintf(GLMethodsDebugFile, "[%4d] TexParameterIiv(0x%x, 0x%x, 0x%p)\n", gl.GetError(), target, pname, params);
	}

	GLvoid TexParameterIuiv(GLenum target, GLenum pname, const GLuint * params) const {
		gl.TexParameterIuiv(target, pname, params);
		fprintf(GLMethodsDebugFile, "[%4d] TexParameterIuiv(0x%x, 0x%x, 0x%p)\n", gl.GetError(), target, pname, params);
	}

	GLvoid GetTexParameterIiv(GLenum target, GLenum pname, GLint * params) const {
		gl.GetTexParameterIiv(target, pname, params);
		fprintf(GLMethodsDebugFile, "[%4d] GetTexParameterIiv(0x%x, 0x%x, 0x%p)\n", gl.GetError(), target, pname, params);
	}

	GLvoid GetTexParameterIuiv(GLenum target, GLenum pname, GLuint * params) const {
		gl.GetTexParameterIuiv(target, pname, params);
		fprintf(GLMethodsDebugFile, "[%4d] GetTexParameterIuiv(0x%x, 0x%x, 0x%p)\n", gl.GetError(), target, pname, params);
	}

	GLvoid ClearBufferiv(GLenum buffer, GLint drawbuffer, const GLint * value) const {
		gl.ClearBufferiv(buffer, drawbuffer, value);
		fprintf(GLMethodsDebugFile, "[%4d] ClearBufferiv(0x%x, %d, 0x%p)\n", gl.GetError(), buffer, drawbuffer, value);
	}

	GLvoid ClearBufferuiv(GLenum buffer, GLint drawbuffer, const GLuint * value) const {
		gl.ClearBufferuiv(buffer, drawbuffer, value);
		fprintf(GLMethodsDebugFile, "[%4d] ClearBufferuiv(0x%x, %d, 0x%p)\n", gl.GetError(), buffer, drawbuffer, value);
	}

	GLvoid ClearBufferfv(GLenum buffer, GLint drawbuffer, const GLfloat * value) const {
		gl.ClearBufferfv(buffer, drawbuffer, value);
		fprintf(GLMethodsDebugFile, "[%4d] ClearBufferfv(0x%x, %d, 0x%p)\n", gl.GetError(), buffer, drawbuffer, value);
	}

	GLvoid ClearBufferfi(GLenum buffer, GLint drawbuffer, GLfloat depth, GLint stencil) const {
		gl.ClearBufferfi(buffer, drawbuffer, depth, stencil);
		fprintf(GLMethodsDebugFile, "[%4d] ClearBufferfi(0x%x, %d, %f, %d)\n", gl.GetError(), buffer, drawbuffer, depth, stencil);
	}

	const GLubyte * GetStringi(GLenum name, GLuint index) const {
		const GLubyte * res = gl.GetStringi(name, index);
		fprintf(GLMethodsDebugFile, "[%4d] GetStringi(0x%x, %u) -> 0x%p\n", gl.GetError(), name, index, res);
		return res;
	}

	GLboolean IsRenderbuffer(GLuint renderbuffer) const {
		GLboolean res = gl.IsRenderbuffer(renderbuffer);
		fprintf(GLMethodsDebugFile, "[%4d] IsRenderbuffer(%u) -> %d\n", gl.GetError(), renderbuffer, res);
		return res;
	}

	GLvoid BindRenderbuffer(GLenum target, GLuint renderbuffer) const {
		gl.BindRenderbuffer(target, renderbuffer);
		fprintf(GLMethodsDebugFile, "[%4d] BindRenderbuffer(0x%x, %u)\n", gl.GetError(), target, renderbuffer);
	}

	GLvoid DeleteRenderbuffers(GLsizei n, const GLuint * renderbuffers) const {
		gl.DeleteRenderbuffers(n, renderbuffers);
		fprintf(GLMethodsDebugFile, "[%4d] DeleteRenderbuffers(%d, 0x%p)\n", gl.GetError(), n, renderbuffers);
	}

	GLvoid GenRenderbuffers(GLsizei n, GLuint * renderbuffers) const {
		gl.GenRenderbuffers(n, renderbuffers);
		fprintf(GLMethodsDebugFile, "[%4d] GenRenderbuffers(%d, 0x%p)\n", gl.GetError(), n, renderbuffers);
	}

	GLvoid RenderbufferStorage(GLenum target, GLenum internalformat, GLsizei width, GLsizei height) const {
		gl.RenderbufferStorage(target, internalformat, width, height);
		fprintf(GLMethodsDebugFile, "[%4d] RenderbufferStorage(0x%x, 0x%x, %d, %d)\n", gl.GetError(), target, internalformat, width, height);
	}

	GLvoid GetRenderbufferParameteriv(GLenum target, GLenum pname, GLint * params) const {
		gl.GetRenderbufferParameteriv(target, pname, params);
		fprintf(GLMethodsDebugFile, "[%4d] GetRenderbufferParameteriv(0x%x, 0x%x, 0x%p)\n", gl.GetError(), target, pname, params);
	}

	GLboolean IsFramebuffer(GLuint framebuffer) const {
		GLboolean res = gl.IsFramebuffer(framebuffer);
		fprintf(GLMethodsDebugFile, "[%4d] IsFramebuffer(%u) -> %d\n", gl.GetError(), framebuffer, res);
		return res;
	}

	GLvoid BindFramebuffer(GLenum target, GLuint framebuffer) const {
		gl.BindFramebuffer(target, framebuffer);
		fprintf(GLMethodsDebugFile, "[%4d] BindFramebuffer(0x%x, %u)\n", gl.GetError(), target, framebuffer);
	}

	GLvoid DeleteFramebuffers(GLsizei n, const GLuint * framebuffers) const {
		gl.DeleteFramebuffers(n, framebuffers);
		fprintf(GLMethodsDebugFile, "[%4d] DeleteFramebuffers(%d, 0x%p)\n", gl.GetError(), n, framebuffers);
	}

	GLvoid GenFramebuffers(GLsizei n, GLuint * framebuffers) const {
		gl.GenFramebuffers(n, framebuffers);
		fprintf(GLMethodsDebugFile, "[%4d] GenFramebuffers(%d, 0x%p)\n", gl.GetError(), n, framebuffers);
	}

	GLenum CheckFramebufferStatus(GLenum target) const {
		GLenum res = gl.CheckFramebufferStatus(target);
		fprintf(GLMethodsDebugFile, "[%4d] CheckFramebufferStatus(0x%x) -> 0x%x\n", gl.GetError(), target, res);
		return res;
	}

	GLvoid FramebufferTexture1D(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level) const {
		gl.FramebufferTexture1D(target, attachment, textarget, texture, level);
		fprintf(GLMethodsDebugFile, "[%4d] FramebufferTexture1D(0x%x, 0x%x, 0x%x, %u, %d)\n", gl.GetError(), target, attachment, textarget, texture, level);
	}

	GLvoid FramebufferTexture2D(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level) const {
		gl.FramebufferTexture2D(target, attachment, textarget, texture, level);
		fprintf(GLMethodsDebugFile, "[%4d] FramebufferTexture2D(0x%x, 0x%x, 0x%x, %u, %d)\n", gl.GetError(), target, attachment, textarget, texture, level);
	}

	GLvoid FramebufferTexture3D(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level, GLint zoffset) const {
		gl.FramebufferTexture3D(target, attachment, textarget, texture, level, zoffset);
		fprintf(GLMethodsDebugFile, "[%4d] FramebufferTexture3D(0x%x, 0x%x, 0x%x, %u, %d, %d)\n", gl.GetError(), target, attachment, textarget, texture, level, zoffset);
	}

	GLvoid FramebufferRenderbuffer(GLenum target, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer) const {
		gl.FramebufferRenderbuffer(target, attachment, renderbuffertarget, renderbuffer);
		fprintf(GLMethodsDebugFile, "[%4d] FramebufferRenderbuffer(0x%x, 0x%x, 0x%x, %u)\n", gl.GetError(), target, attachment, renderbuffertarget, renderbuffer);
	}

	GLvoid GetFramebufferAttachmentParameteriv(GLenum target, GLenum attachment, GLenum pname, GLint * params) const {
		gl.GetFramebufferAttachmentParameteriv(target, attachment, pname, params);
		fprintf(GLMethodsDebugFile, "[%4d] GetFramebufferAttachmentParameteriv(0x%x, 0x%x, 0x%x, 0x%p)\n", gl.GetError(), target, attachment, pname, params);
	}

	GLvoid GenerateMipmap(GLenum target) const {
		gl.GenerateMipmap(target);
		fprintf(GLMethodsDebugFile, "[%4d] GenerateMipmap(0x%x)\n", gl.GetError(), target);
	}

	GLvoid BlitFramebuffer(GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield mask, GLenum filter) const {
		gl.BlitFramebuffer(srcX0, srcY0, srcX1, srcY1, dstX0, dstY0, dstX1, dstY1, mask, filter);
		fprintf(GLMethodsDebugFile, "[%4d] BlitFramebuffer(%d, %d, %d, %d, %d, %d, %d, %d, 0x%x, 0x%x)\n", gl.GetError(), srcX0, srcY0, srcX1, srcY1, dstX0, dstY0, dstX1, dstY1, mask, filter);
	}

	GLvoid RenderbufferStorageMultisample(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height) const {
		gl.RenderbufferStorageMultisample(target, samples, internalformat, width, height);
		fprintf(GLMethodsDebugFile, "[%4d] RenderbufferStorageMultisample(0x%x, %d, 0x%x, %d, %d)\n", gl.GetError(), target, samples, internalformat, width, height);
	}

	GLvoid FramebufferTextureLayer(GLenum target, GLenum attachment, GLuint texture, GLint level, GLint layer) const {
		gl.FramebufferTextureLayer(target, attachment, texture, level, layer);
		fprintf(GLMethodsDebugFile, "[%4d] FramebufferTextureLayer(0x%x, 0x%x, %u, %d, %d)\n", gl.GetError(), target, attachment, texture, level, layer);
	}

	GLvoid * MapBufferRange(GLenum target, GLintptr offset, GLsizeiptr length, GLbitfield access) const {
		GLvoid * res = gl.MapBufferRange(target, offset, length, access);
		fprintf(GLMethodsDebugFile, "[%4d] MapBufferRange(0x%x, %" LL "d, %" LL "d, 0x%x) -> 0x%p\n", gl.GetError(), target, offset, length, access, res);
		return res;
	}

	GLvoid FlushMappedBufferRange(GLenum target, GLintptr offset, GLsizeiptr length) const {
		gl.FlushMappedBufferRange(target, offset, length);
		fprintf(GLMethodsDebugFile, "[%4d] FlushMappedBufferRange(0x%x, %" LL "d, %" LL "d)\n", gl.GetError(), target, offset, length);
	}

	GLvoid BindVertexArray(GLuint array) const {
		gl.BindVertexArray(array);
		fprintf(GLMethodsDebugFile, "[%4d] BindVertexArray(%u)\n", gl.GetError(), array);
	}

	GLvoid DeleteVertexArrays(GLsizei n, const GLuint * arrays) const {
		gl.DeleteVertexArrays(n, arrays);
		fprintf(GLMethodsDebugFile, "[%4d] DeleteVertexArrays(%d, 0x%p)\n", gl.GetError(), n, arrays);
	}

	GLvoid GenVertexArrays(GLsizei n, GLuint * arrays) const {
		gl.GenVertexArrays(n, arrays);
		fprintf(GLMethodsDebugFile, "[%4d] GenVertexArrays(%d, 0x%p)\n", gl.GetError(), n, arrays);
	}

	GLboolean IsVertexArray(GLuint array) const {
		GLboolean res = gl.IsVertexArray(array);
		fprintf(GLMethodsDebugFile, "[%4d] IsVertexArray(%u) -> %d\n", gl.GetError(), array, res);
		return res;
	}

	GLvoid DrawArraysInstanced(GLenum mode, GLint first, GLsizei count, GLsizei instancecount) const {
		gl.DrawArraysInstanced(mode, first, count, instancecount);
		fprintf(GLMethodsDebugFile, "[%4d] DrawArraysInstanced(0x%x, %d, %d, %d)\n", gl.GetError(), mode, first, count, instancecount);
	}

	GLvoid DrawElementsInstanced(GLenum mode, GLsizei count, GLenum type, const GLvoid * indices, GLsizei instancecount) const {
		gl.DrawElementsInstanced(mode, count, type, indices, instancecount);
		fprintf(GLMethodsDebugFile, "[%4d] DrawElementsInstanced(0x%x, %d, 0x%x, 0x%p, %d)\n", gl.GetError(), mode, count, type, indices, instancecount);
	}

	GLvoid TexBuffer(GLenum target, GLenum internalformat, GLuint buffer) const {
		gl.TexBuffer(target, internalformat, buffer);
		fprintf(GLMethodsDebugFile, "[%4d] TexBuffer(0x%x, 0x%x, %u)\n", gl.GetError(), target, internalformat, buffer);
	}

	GLvoid PrimitiveRestartIndex(GLuint index) const {
		gl.PrimitiveRestartIndex(index);
		fprintf(GLMethodsDebugFile, "[%4d] PrimitiveRestartIndex(%u)\n", gl.GetError(), index);
	}

	GLvoid CopyBufferSubData(GLenum readTarget, GLenum writeTarget, GLintptr readOffset, GLintptr writeOffset, GLsizeiptr size) const {
		gl.CopyBufferSubData(readTarget, writeTarget, readOffset, writeOffset, size);
		fprintf(GLMethodsDebugFile, "[%4d] CopyBufferSubData(0x%x, 0x%x, %" LL "d, %" LL "d, %" LL "d)\n", gl.GetError(), readTarget, writeTarget, readOffset, writeOffset, size);
	}

	GLvoid GetUniformIndices(GLuint program, GLsizei uniformCount, const GLchar * const* uniformNames, GLuint * uniformIndices) const {
		gl.GetUniformIndices(program, uniformCount, uniformNames, uniformIndices);
		fprintf(GLMethodsDebugFile, "[%4d] GetUniformIndices(%u, %d, 0x%p, 0x%p)\n", gl.GetError(), program, uniformCount, uniformNames, uniformIndices);
	}

	GLvoid GetActiveUniformsiv(GLuint program, GLsizei uniformCount, const GLuint * uniformIndices, GLenum pname, GLint * params) const {
		gl.GetActiveUniformsiv(program, uniformCount, uniformIndices, pname, params);
		fprintf(GLMethodsDebugFile, "[%4d] GetActiveUniformsiv(%u, %d, 0x%p, 0x%x, 0x%p)\n", gl.GetError(), program, uniformCount, uniformIndices, pname, params);
	}

	GLvoid GetActiveUniformName(GLuint program, GLuint uniformIndex, GLsizei bufSize, GLsizei * length, GLchar * uniformName) const {
		gl.GetActiveUniformName(program, uniformIndex, bufSize, length, uniformName);
		fprintf(GLMethodsDebugFile, "[%4d] GetActiveUniformName(%u, %u, %d, 0x%p, 0x%p)\n", gl.GetError(), program, uniformIndex, bufSize, length, uniformName);
	}

	GLuint GetUniformBlockIndex(GLuint program, const GLchar * uniformBlockName) const {
		GLuint res = gl.GetUniformBlockIndex(program, uniformBlockName);
		fprintf(GLMethodsDebugFile, "[%4d] GetUniformBlockIndex(%u, 0x%p) -> %u\n", gl.GetError(), program, uniformBlockName, res);
		return res;
	}

	GLvoid GetActiveUniformBlockiv(GLuint program, GLuint uniformBlockIndex, GLenum pname, GLint * params) const {
		gl.GetActiveUniformBlockiv(program, uniformBlockIndex, pname, params);
		fprintf(GLMethodsDebugFile, "[%4d] GetActiveUniformBlockiv(%u, %u, 0x%x, 0x%p)\n", gl.GetError(), program, uniformBlockIndex, pname, params);
	}

	GLvoid GetActiveUniformBlockName(GLuint program, GLuint uniformBlockIndex, GLsizei bufSize, GLsizei * length, GLchar * uniformBlockName) const {
		gl.GetActiveUniformBlockName(program, uniformBlockIndex, bufSize, length, uniformBlockName);
		fprintf(GLMethodsDebugFile, "[%4d] GetActiveUniformBlockName(%u, %u, %d, 0x%p, 0x%p)\n", gl.GetError(), program, uniformBlockIndex, bufSize, length, uniformBlockName);
	}

	GLvoid UniformBlockBinding(GLuint program, GLuint uniformBlockIndex, GLuint uniformBlockBinding) const {
		gl.UniformBlockBinding(program, uniformBlockIndex, uniformBlockBinding);
		fprintf(GLMethodsDebugFile, "[%4d] UniformBlockBinding(%u, %u, %u)\n", gl.GetError(), program, uniformBlockIndex, uniformBlockBinding);
	}

	GLvoid DrawElementsBaseVertex(GLenum mode, GLsizei count, GLenum type, const GLvoid * indices, GLint basevertex) const {
		gl.DrawElementsBaseVertex(mode, count, type, indices, basevertex);
		fprintf(GLMethodsDebugFile, "[%4d] DrawElementsBaseVertex(0x%x, %d, 0x%x, 0x%p, %d)\n", gl.GetError(), mode, count, type, indices, basevertex);
	}

	GLvoid DrawRangeElementsBaseVertex(GLenum mode, GLuint start, GLuint end, GLsizei count, GLenum type, const GLvoid * indices, GLint basevertex) const {
		gl.DrawRangeElementsBaseVertex(mode, start, end, count, type, indices, basevertex);
		fprintf(GLMethodsDebugFile, "[%4d] DrawRangeElementsBaseVertex(0x%x, %u, %u, %d, 0x%x, 0x%p, %d)\n", gl.GetError(), mode, start, end, count, type, indices, basevertex);
	}

	GLvoid DrawElementsInstancedBaseVertex(GLenum mode, GLsizei count, GLenum type, const GLvoid * indices, GLsizei instancecount, GLint basevertex) const {
		gl.DrawElementsInstancedBaseVertex(mode, count, type, indices, instancecount, basevertex);
		fprintf(GLMethodsDebugFile, "[%4d] DrawElementsInstancedBaseVertex(0x%x, %d, 0x%x, 0x%p, %d, %d)\n", gl.GetError(), mode, count, type, indices, instancecount, basevertex);
	}

	GLvoid MultiDrawElementsBaseVertex(GLenum mode, const GLsizei * count, GLenum type, const GLvoid * const* indices, GLsizei drawcount, const GLint * basevertex) const {
		gl.MultiDrawElementsBaseVertex(mode, count, type, indices, drawcount, basevertex);
		fprintf(GLMethodsDebugFile, "[%4d] MultiDrawElementsBaseVertex(0x%x, 0x%p, 0x%x, 0x%p, %d, 0x%p)\n", gl.GetError(), mode, count, type, indices, drawcount, basevertex);
	}

	GLvoid ProvokingVertex(GLenum mode) const {
		gl.ProvokingVertex(mode);
		fprintf(GLMethodsDebugFile, "[%4d] ProvokingVertex(0x%x)\n", gl.GetError(), mode);
	}

	GLsync FenceSync(GLenum condition, GLbitfield flags) const {
		GLsync res = gl.FenceSync(condition, flags);
		fprintf(GLMethodsDebugFile, "[%4d] FenceSync(0x%x, 0x%x) -> 0x%p\n", gl.GetError(), condition, flags, res);
		return res;
	}

	GLboolean IsSync(GLsync sync) const {
		GLboolean res = gl.IsSync(sync);
		fprintf(GLMethodsDebugFile, "[%4d] IsSync(0x%p) -> %d\n", gl.GetError(), sync, res);
		return res;
	}

	GLvoid DeleteSync(GLsync sync) const {
		gl.DeleteSync(sync);
		fprintf(GLMethodsDebugFile, "[%4d] DeleteSync(0x%p)\n", gl.GetError(), sync);
	}

	GLenum ClientWaitSync(GLsync sync, GLbitfield flags, GLuint64 timeout) const {
		GLenum res = gl.ClientWaitSync(sync, flags, timeout);
		fprintf(GLMethodsDebugFile, "[%4d] ClientWaitSync(0x%p, 0x%x, %llu) -> 0x%x\n", gl.GetError(), sync, flags, timeout, res);
		return res;
	}

	GLvoid WaitSync(GLsync sync, GLbitfield flags, GLuint64 timeout) const {
		gl.WaitSync(sync, flags, timeout);
		fprintf(GLMethodsDebugFile, "[%4d] WaitSync(0x%p, 0x%x, %llu)\n", gl.GetError(), sync, flags, timeout);
	}

	GLvoid GetInteger64v(GLenum pname, GLint64 * data) const {
		gl.GetInteger64v(pname, data);
		fprintf(GLMethodsDebugFile, "[%4d] GetInteger64v(0x%x, 0x%p)\n", gl.GetError(), pname, data);
	}

	GLvoid GetSynciv(GLsync sync, GLenum pname, GLsizei bufSize, GLsizei * length, GLint * values) const {
		gl.GetSynciv(sync, pname, bufSize, length, values);
		fprintf(GLMethodsDebugFile, "[%4d] GetSynciv(0x%p, 0x%x, %d, 0x%p, 0x%p)\n", gl.GetError(), sync, pname, bufSize, length, values);
	}

	GLvoid GetInteger64i_v(GLenum target, GLuint index, GLint64 * data) const {
		gl.GetInteger64i_v(target, index, data);
		fprintf(GLMethodsDebugFile, "[%4d] GetInteger64i_v(0x%x, %u, 0x%p)\n", gl.GetError(), target, index, data);
	}

	GLvoid GetBufferParameteri64v(GLenum target, GLenum pname, GLint64 * params) const {
		gl.GetBufferParameteri64v(target, pname, params);
		fprintf(GLMethodsDebugFile, "[%4d] GetBufferParameteri64v(0x%x, 0x%x, 0x%p)\n", gl.GetError(), target, pname, params);
	}

	GLvoid FramebufferTexture(GLenum target, GLenum attachment, GLuint texture, GLint level) const {
		gl.FramebufferTexture(target, attachment, texture, level);
		fprintf(GLMethodsDebugFile, "[%4d] FramebufferTexture(0x%x, 0x%x, %u, %d)\n", gl.GetError(), target, attachment, texture, level);
	}

	GLvoid TexImage2DMultisample(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLboolean fixedsamplelocations) const {
		gl.TexImage2DMultisample(target, samples, internalformat, width, height, fixedsamplelocations);
		fprintf(GLMethodsDebugFile, "[%4d] TexImage2DMultisample(0x%x, %d, 0x%x, %d, %d, %d)\n", gl.GetError(), target, samples, internalformat, width, height, fixedsamplelocations);
	}

	GLvoid TexImage3DMultisample(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLboolean fixedsamplelocations) const {
		gl.TexImage3DMultisample(target, samples, internalformat, width, height, depth, fixedsamplelocations);
		fprintf(GLMethodsDebugFile, "[%4d] TexImage3DMultisample(0x%x, %d, 0x%x, %d, %d, %d, %d)\n", gl.GetError(), target, samples, internalformat, width, height, depth, fixedsamplelocations);
	}

	GLvoid GetMultisamplefv(GLenum pname, GLuint index, GLfloat * val) const {
		gl.GetMultisamplefv(pname, index, val);
		fprintf(GLMethodsDebugFile, "[%4d] GetMultisamplefv(0x%x, %u, 0x%p)\n", gl.GetError(), pname, index, val);
	}

	GLvoid SampleMaski(GLuint maskNumber, GLbitfield mask) const {
		gl.SampleMaski(maskNumber, mask);
		fprintf(GLMethodsDebugFile, "[%4d] SampleMaski(%u, 0x%x)\n", gl.GetError(), maskNumber, mask);
	}

	GLvoid BindFragDataLocationIndexed(GLuint program, GLuint colorNumber, GLuint index, const GLchar * name) const {
		gl.BindFragDataLocationIndexed(program, colorNumber, index, name);
		fprintf(GLMethodsDebugFile, "[%4d] BindFragDataLocationIndexed(%u, %u, %u, 0x%p)\n", gl.GetError(), program, colorNumber, index, name);
	}

	GLint GetFragDataIndex(GLuint program, const GLchar * name) const {
		GLint res = gl.GetFragDataIndex(program, name);
		fprintf(GLMethodsDebugFile, "[%4d] GetFragDataIndex(%u, 0x%p) -> %d\n", gl.GetError(), program, name, res);
		return res;
	}

	GLvoid GenSamplers(GLsizei count, GLuint * samplers) const {
		gl.GenSamplers(count, samplers);
		fprintf(GLMethodsDebugFile, "[%4d] GenSamplers(%d, 0x%p)\n", gl.GetError(), count, samplers);
	}

	GLvoid DeleteSamplers(GLsizei count, const GLuint * samplers) const {
		gl.DeleteSamplers(count, samplers);
		fprintf(GLMethodsDebugFile, "[%4d] DeleteSamplers(%d, 0x%p)\n", gl.GetError(), count, samplers);
	}

	GLboolean IsSampler(GLuint sampler) const {
		GLboolean res = gl.IsSampler(sampler);
		fprintf(GLMethodsDebugFile, "[%4d] IsSampler(%u) -> %d\n", gl.GetError(), sampler, res);
		return res;
	}

	GLvoid BindSampler(GLuint unit, GLuint sampler) const {
		gl.BindSampler(unit, sampler);
		fprintf(GLMethodsDebugFile, "[%4d] BindSampler(%u, %u)\n", gl.GetError(), unit, sampler);
	}

	GLvoid SamplerParameteri(GLuint sampler, GLenum pname, GLint param) const {
		gl.SamplerParameteri(sampler, pname, param);
		fprintf(GLMethodsDebugFile, "[%4d] SamplerParameteri(%u, 0x%x, %d)\n", gl.GetError(), sampler, pname, param);
	}

	GLvoid SamplerParameteriv(GLuint sampler, GLenum pname, const GLint * param) const {
		gl.SamplerParameteriv(sampler, pname, param);
		fprintf(GLMethodsDebugFile, "[%4d] SamplerParameteriv(%u, 0x%x, 0x%p)\n", gl.GetError(), sampler, pname, param);
	}

	GLvoid SamplerParameterf(GLuint sampler, GLenum pname, GLfloat param) const {
		gl.SamplerParameterf(sampler, pname, param);
		fprintf(GLMethodsDebugFile, "[%4d] SamplerParameterf(%u, 0x%x, %f)\n", gl.GetError(), sampler, pname, param);
	}

	GLvoid SamplerParameterfv(GLuint sampler, GLenum pname, const GLfloat * param) const {
		gl.SamplerParameterfv(sampler, pname, param);
		fprintf(GLMethodsDebugFile, "[%4d] SamplerParameterfv(%u, 0x%x, 0x%p)\n", gl.GetError(), sampler, pname, param);
	}

	GLvoid SamplerParameterIiv(GLuint sampler, GLenum pname, const GLint * param) const {
		gl.SamplerParameterIiv(sampler, pname, param);
		fprintf(GLMethodsDebugFile, "[%4d] SamplerParameterIiv(%u, 0x%x, 0x%p)\n", gl.GetError(), sampler, pname, param);
	}

	GLvoid SamplerParameterIuiv(GLuint sampler, GLenum pname, const GLuint * param) const {
		gl.SamplerParameterIuiv(sampler, pname, param);
		fprintf(GLMethodsDebugFile, "[%4d] SamplerParameterIuiv(%u, 0x%x, 0x%p)\n", gl.GetError(), sampler, pname, param);
	}

	GLvoid GetSamplerParameteriv(GLuint sampler, GLenum pname, GLint * params) const {
		gl.GetSamplerParameteriv(sampler, pname, params);
		fprintf(GLMethodsDebugFile, "[%4d] GetSamplerParameteriv(%u, 0x%x, 0x%p)\n", gl.GetError(), sampler, pname, params);
	}

	GLvoid GetSamplerParameterIiv(GLuint sampler, GLenum pname, GLint * params) const {
		gl.GetSamplerParameterIiv(sampler, pname, params);
		fprintf(GLMethodsDebugFile, "[%4d] GetSamplerParameterIiv(%u, 0x%x, 0x%p)\n", gl.GetError(), sampler, pname, params);
	}

	GLvoid GetSamplerParameterfv(GLuint sampler, GLenum pname, GLfloat * params) const {
		gl.GetSamplerParameterfv(sampler, pname, params);
		fprintf(GLMethodsDebugFile, "[%4d] GetSamplerParameterfv(%u, 0x%x, 0x%p)\n", gl.GetError(), sampler, pname, params);
	}

	GLvoid GetSamplerParameterIuiv(GLuint sampler, GLenum pname, GLuint * params) const {
		gl.GetSamplerParameterIuiv(sampler, pname, params);
		fprintf(GLMethodsDebugFile, "[%4d] GetSamplerParameterIuiv(%u, 0x%x, 0x%p)\n", gl.GetError(), sampler, pname, params);
	}

	GLvoid QueryCounter(GLuint id, GLenum target) const {
		gl.QueryCounter(id, target);
		fprintf(GLMethodsDebugFile, "[%4d] QueryCounter(%u, 0x%x)\n", gl.GetError(), id, target);
	}

	GLvoid GetQueryObjecti64v(GLuint id, GLenum pname, GLint64 * params) const {
		gl.GetQueryObjecti64v(id, pname, params);
		fprintf(GLMethodsDebugFile, "[%4d] GetQueryObjecti64v(%u, 0x%x, 0x%p)\n", gl.GetError(), id, pname, params);
	}

	GLvoid GetQueryObjectui64v(GLuint id, GLenum pname, GLuint64 * params) const {
		gl.GetQueryObjectui64v(id, pname, params);
		fprintf(GLMethodsDebugFile, "[%4d] GetQueryObjectui64v(%u, 0x%x, 0x%p)\n", gl.GetError(), id, pname, params);
	}

	GLvoid VertexAttribDivisor(GLuint index, GLuint divisor) const {
		gl.VertexAttribDivisor(index, divisor);
		fprintf(GLMethodsDebugFile, "[%4d] VertexAttribDivisor(%u, %u)\n", gl.GetError(), index, divisor);
	}

	GLvoid VertexAttribP1ui(GLuint index, GLenum type, GLboolean normalized, GLuint value) const {
		gl.VertexAttribP1ui(index, type, normalized, value);
		fprintf(GLMethodsDebugFile, "[%4d] VertexAttribP1ui(%u, 0x%x, %d, %u)\n", gl.GetError(), index, type, normalized, value);
	}

	GLvoid VertexAttribP1uiv(GLuint index, GLenum type, GLboolean normalized, const GLuint * value) const {
		gl.VertexAttribP1uiv(index, type, normalized, value);
		fprintf(GLMethodsDebugFile, "[%4d] VertexAttribP1uiv(%u, 0x%x, %d, 0x%p)\n", gl.GetError(), index, type, normalized, value);
	}

	GLvoid VertexAttribP2ui(GLuint index, GLenum type, GLboolean normalized, GLuint value) const {
		gl.VertexAttribP2ui(index, type, normalized, value);
		fprintf(GLMethodsDebugFile, "[%4d] VertexAttribP2ui(%u, 0x%x, %d, %u)\n", gl.GetError(), index, type, normalized, value);
	}

	GLvoid VertexAttribP2uiv(GLuint index, GLenum type, GLboolean normalized, const GLuint * value) const {
		gl.VertexAttribP2uiv(index, type, normalized, value);
		fprintf(GLMethodsDebugFile, "[%4d] VertexAttribP2uiv(%u, 0x%x, %d, 0x%p)\n", gl.GetError(), index, type, normalized, value);
	}

	GLvoid VertexAttribP3ui(GLuint index, GLenum type, GLboolean normalized, GLuint value) const {
		gl.VertexAttribP3ui(index, type, normalized, value);
		fprintf(GLMethodsDebugFile, "[%4d] VertexAttribP3ui(%u, 0x%x, %d, %u)\n", gl.GetError(), index, type, normalized, value);
	}

	GLvoid VertexAttribP3uiv(GLuint index, GLenum type, GLboolean normalized, const GLuint * value) const {
		gl.VertexAttribP3uiv(index, type, normalized, value);
		fprintf(GLMethodsDebugFile, "[%4d] VertexAttribP3uiv(%u, 0x%x, %d, 0x%p)\n", gl.GetError(), index, type, normalized, value);
	}

	GLvoid VertexAttribP4ui(GLuint index, GLenum type, GLboolean normalized, GLuint value) const {
		gl.VertexAttribP4ui(index, type, normalized, value);
		fprintf(GLMethodsDebugFile, "[%4d] VertexAttribP4ui(%u, 0x%x, %d, %u)\n", gl.GetError(), index, type, normalized, value);
	}

	GLvoid VertexAttribP4uiv(GLuint index, GLenum type, GLboolean normalized, const GLuint * value) const {
		gl.VertexAttribP4uiv(index, type, normalized, value);
		fprintf(GLMethodsDebugFile, "[%4d] VertexAttribP4uiv(%u, 0x%x, %d, 0x%p)\n", gl.GetError(), index, type, normalized, value);
	}

	GLvoid MinSampleShading(GLfloat value) const {
		gl.MinSampleShading(value);
		fprintf(GLMethodsDebugFile, "[%4d] MinSampleShading(%f)\n", gl.GetError(), value);
	}

	GLvoid BlendEquationi(GLuint buf, GLenum mode) const {
		gl.BlendEquationi(buf, mode);
		fprintf(GLMethodsDebugFile, "[%4d] BlendEquationi(%u, 0x%x)\n", gl.GetError(), buf, mode);
	}

	GLvoid BlendEquationSeparatei(GLuint buf, GLenum modeRGB, GLenum modeAlpha) const {
		gl.BlendEquationSeparatei(buf, modeRGB, modeAlpha);
		fprintf(GLMethodsDebugFile, "[%4d] BlendEquationSeparatei(%u, 0x%x, 0x%x)\n", gl.GetError(), buf, modeRGB, modeAlpha);
	}

	GLvoid BlendFunci(GLuint buf, GLenum src, GLenum dst) const {
		gl.BlendFunci(buf, src, dst);
		fprintf(GLMethodsDebugFile, "[%4d] BlendFunci(%u, 0x%x, 0x%x)\n", gl.GetError(), buf, src, dst);
	}

	GLvoid BlendFuncSeparatei(GLuint buf, GLenum srcRGB, GLenum dstRGB, GLenum srcAlpha, GLenum dstAlpha) const {
		gl.BlendFuncSeparatei(buf, srcRGB, dstRGB, srcAlpha, dstAlpha);
		fprintf(GLMethodsDebugFile, "[%4d] BlendFuncSeparatei(%u, 0x%x, 0x%x, 0x%x, 0x%x)\n", gl.GetError(), buf, srcRGB, dstRGB, srcAlpha, dstAlpha);
	}

	GLvoid DrawArraysIndirect(GLenum mode, const GLvoid * indirect) const {
		gl.DrawArraysIndirect(mode, indirect);
		fprintf(GLMethodsDebugFile, "[%4d] DrawArraysIndirect(0x%x, 0x%p)\n", gl.GetError(), mode, indirect);
	}

	GLvoid DrawElementsIndirect(GLenum mode, GLenum type, const GLvoid * indirect) const {
		gl.DrawElementsIndirect(mode, type, indirect);
		fprintf(GLMethodsDebugFile, "[%4d] DrawElementsIndirect(0x%x, 0x%x, 0x%p)\n", gl.GetError(), mode, type, indirect);
	}

	GLvoid Uniform1d(GLint location, GLdouble x) const {
		gl.Uniform1d(location, x);
		fprintf(GLMethodsDebugFile, "[%4d] Uniform1d(%d, %lf)\n", gl.GetError(), location, x);
	}

	GLvoid Uniform2d(GLint location, GLdouble x, GLdouble y) const {
		gl.Uniform2d(location, x, y);
		fprintf(GLMethodsDebugFile, "[%4d] Uniform2d(%d, %lf, %lf)\n", gl.GetError(), location, x, y);
	}

	GLvoid Uniform3d(GLint location, GLdouble x, GLdouble y, GLdouble z) const {
		gl.Uniform3d(location, x, y, z);
		fprintf(GLMethodsDebugFile, "[%4d] Uniform3d(%d, %lf, %lf, %lf)\n", gl.GetError(), location, x, y, z);
	}

	GLvoid Uniform4d(GLint location, GLdouble x, GLdouble y, GLdouble z, GLdouble w) const {
		gl.Uniform4d(location, x, y, z, w);
		fprintf(GLMethodsDebugFile, "[%4d] Uniform4d(%d, %lf, %lf, %lf, %lf)\n", gl.GetError(), location, x, y, z, w);
	}

	GLvoid Uniform1dv(GLint location, GLsizei count, const GLdouble * value) const {
		gl.Uniform1dv(location, count, value);
		fprintf(GLMethodsDebugFile, "[%4d] Uniform1dv(%d, %d, 0x%p)\n", gl.GetError(), location, count, value);
	}

	GLvoid Uniform2dv(GLint location, GLsizei count, const GLdouble * value) const {
		gl.Uniform2dv(location, count, value);
		fprintf(GLMethodsDebugFile, "[%4d] Uniform2dv(%d, %d, 0x%p)\n", gl.GetError(), location, count, value);
	}

	GLvoid Uniform3dv(GLint location, GLsizei count, const GLdouble * value) const {
		gl.Uniform3dv(location, count, value);
		fprintf(GLMethodsDebugFile, "[%4d] Uniform3dv(%d, %d, 0x%p)\n", gl.GetError(), location, count, value);
	}

	GLvoid Uniform4dv(GLint location, GLsizei count, const GLdouble * value) const {
		gl.Uniform4dv(location, count, value);
		fprintf(GLMethodsDebugFile, "[%4d] Uniform4dv(%d, %d, 0x%p)\n", gl.GetError(), location, count, value);
	}

	GLvoid UniformMatrix2dv(GLint location, GLsizei count, GLboolean transpose, const GLdouble * value) const {
		gl.UniformMatrix2dv(location, count, transpose, value);
		fprintf(GLMethodsDebugFile, "[%4d] UniformMatrix2dv(%d, %d, %d, 0x%p)\n", gl.GetError(), location, count, transpose, value);
	}

	GLvoid UniformMatrix3dv(GLint location, GLsizei count, GLboolean transpose, const GLdouble * value) const {
		gl.UniformMatrix3dv(location, count, transpose, value);
		fprintf(GLMethodsDebugFile, "[%4d] UniformMatrix3dv(%d, %d, %d, 0x%p)\n", gl.GetError(), location, count, transpose, value);
	}

	GLvoid UniformMatrix4dv(GLint location, GLsizei count, GLboolean transpose, const GLdouble * value) const {
		gl.UniformMatrix4dv(location, count, transpose, value);
		fprintf(GLMethodsDebugFile, "[%4d] UniformMatrix4dv(%d, %d, %d, 0x%p)\n", gl.GetError(), location, count, transpose, value);
	}

	GLvoid UniformMatrix2x3dv(GLint location, GLsizei count, GLboolean transpose, const GLdouble * value) const {
		gl.UniformMatrix2x3dv(location, count, transpose, value);
		fprintf(GLMethodsDebugFile, "[%4d] UniformMatrix2x3dv(%d, %d, %d, 0x%p)\n", gl.GetError(), location, count, transpose, value);
	}

	GLvoid UniformMatrix2x4dv(GLint location, GLsizei count, GLboolean transpose, const GLdouble * value) const {
		gl.UniformMatrix2x4dv(location, count, transpose, value);
		fprintf(GLMethodsDebugFile, "[%4d] UniformMatrix2x4dv(%d, %d, %d, 0x%p)\n", gl.GetError(), location, count, transpose, value);
	}

	GLvoid UniformMatrix3x2dv(GLint location, GLsizei count, GLboolean transpose, const GLdouble * value) const {
		gl.UniformMatrix3x2dv(location, count, transpose, value);
		fprintf(GLMethodsDebugFile, "[%4d] UniformMatrix3x2dv(%d, %d, %d, 0x%p)\n", gl.GetError(), location, count, transpose, value);
	}

	GLvoid UniformMatrix3x4dv(GLint location, GLsizei count, GLboolean transpose, const GLdouble * value) const {
		gl.UniformMatrix3x4dv(location, count, transpose, value);
		fprintf(GLMethodsDebugFile, "[%4d] UniformMatrix3x4dv(%d, %d, %d, 0x%p)\n", gl.GetError(), location, count, transpose, value);
	}

	GLvoid UniformMatrix4x2dv(GLint location, GLsizei count, GLboolean transpose, const GLdouble * value) const {
		gl.UniformMatrix4x2dv(location, count, transpose, value);
		fprintf(GLMethodsDebugFile, "[%4d] UniformMatrix4x2dv(%d, %d, %d, 0x%p)\n", gl.GetError(), location, count, transpose, value);
	}

	GLvoid UniformMatrix4x3dv(GLint location, GLsizei count, GLboolean transpose, const GLdouble * value) const {
		gl.UniformMatrix4x3dv(location, count, transpose, value);
		fprintf(GLMethodsDebugFile, "[%4d] UniformMatrix4x3dv(%d, %d, %d, 0x%p)\n", gl.GetError(), location, count, transpose, value);
	}

	// GLvoid GetUniformdv(GLuint program, GLint location, GLdouble * params) const {
	// 	gl.GetUniformdv(program, location, params);
	// 	fprintf(GLMethodsDebugFile, "[%4d] GetUniformdv(%u, %d, 0x%p)\n", gl.GetError(), program, location, params);
	// }

	GLint GetSubroutineUniformLocation(GLuint program, GLenum shadertype, const GLchar * name) const {
		GLint res = gl.GetSubroutineUniformLocation(program, shadertype, name);
		fprintf(GLMethodsDebugFile, "[%4d] GetSubroutineUniformLocation(%u, 0x%x, 0x%p) -> %d\n", gl.GetError(), program, shadertype, name, res);
		return res;
	}

	GLuint GetSubroutineIndex(GLuint program, GLenum shadertype, const GLchar * name) const {
		GLuint res = gl.GetSubroutineIndex(program, shadertype, name);
		fprintf(GLMethodsDebugFile, "[%4d] GetSubroutineIndex(%u, 0x%x, 0x%p) -> %u\n", gl.GetError(), program, shadertype, name, res);
		return res;
	}

	GLvoid GetActiveSubroutineUniformiv(GLuint program, GLenum shadertype, GLuint index, GLenum pname, GLint * values) const {
		gl.GetActiveSubroutineUniformiv(program, shadertype, index, pname, values);
		fprintf(GLMethodsDebugFile, "[%4d] GetActiveSubroutineUniformiv(%u, 0x%x, %u, 0x%x, 0x%p)\n", gl.GetError(), program, shadertype, index, pname, values);
	}

	GLvoid GetActiveSubroutineUniformName(GLuint program, GLenum shadertype, GLuint index, GLsizei bufsize, GLsizei * length, GLchar * name) const {
		gl.GetActiveSubroutineUniformName(program, shadertype, index, bufsize, length, name);
		fprintf(GLMethodsDebugFile, "[%4d] GetActiveSubroutineUniformName(%u, 0x%x, %u, %d, 0x%p, 0x%p)\n", gl.GetError(), program, shadertype, index, bufsize, length, name);
	}

	GLvoid GetActiveSubroutineName(GLuint program, GLenum shadertype, GLuint index, GLsizei bufsize, GLsizei * length, GLchar * name) const {
		gl.GetActiveSubroutineName(program, shadertype, index, bufsize, length, name);
		fprintf(GLMethodsDebugFile, "[%4d] GetActiveSubroutineName(%u, 0x%x, %u, %d, 0x%p, 0x%p)\n", gl.GetError(), program, shadertype, index, bufsize, length, name);
	}

	GLvoid UniformSubroutinesuiv(GLenum shadertype, GLsizei count, const GLuint * indices) const {
		gl.UniformSubroutinesuiv(shadertype, count, indices);
		fprintf(GLMethodsDebugFile, "[%4d] UniformSubroutinesuiv(0x%x, %d, 0x%p)\n", gl.GetError(), shadertype, count, indices);
	}

	GLvoid GetUniformSubroutineuiv(GLenum shadertype, GLint location, GLuint * params) const {
		gl.GetUniformSubroutineuiv(shadertype, location, params);
		fprintf(GLMethodsDebugFile, "[%4d] GetUniformSubroutineuiv(0x%x, %d, 0x%p)\n", gl.GetError(), shadertype, location, params);
	}

	GLvoid GetProgramStageiv(GLuint program, GLenum shadertype, GLenum pname, GLint * values) const {
		gl.GetProgramStageiv(program, shadertype, pname, values);
		fprintf(GLMethodsDebugFile, "[%4d] GetProgramStageiv(%u, 0x%x, 0x%x, 0x%p)\n", gl.GetError(), program, shadertype, pname, values);
	}

	GLvoid PatchParameteri(GLenum pname, GLint value) const {
		gl.PatchParameteri(pname, value);
		fprintf(GLMethodsDebugFile, "[%4d] PatchParameteri(0x%x, %d)\n", gl.GetError(), pname, value);
	}

	GLvoid PatchParameterfv(GLenum pname, const GLfloat * values) const {
		gl.PatchParameterfv(pname, values);
		fprintf(GLMethodsDebugFile, "[%4d] PatchParameterfv(0x%x, 0x%p)\n", gl.GetError(), pname, values);
	}

	GLvoid BindTransformFeedback(GLenum target, GLuint id) const {
		gl.BindTransformFeedback(target, id);
		fprintf(GLMethodsDebugFile, "[%4d] BindTransformFeedback(0x%x, %u)\n", gl.GetError(), target, id);
	}

	GLvoid DeleteTransformFeedbacks(GLsizei n, const GLuint * ids) const {
		gl.DeleteTransformFeedbacks(n, ids);
		fprintf(GLMethodsDebugFile, "[%4d] DeleteTransformFeedbacks(%d, 0x%p)\n", gl.GetError(), n, ids);
	}

	GLvoid GenTransformFeedbacks(GLsizei n, GLuint * ids) const {
		gl.GenTransformFeedbacks(n, ids);
		fprintf(GLMethodsDebugFile, "[%4d] GenTransformFeedbacks(%d, 0x%p)\n", gl.GetError(), n, ids);
	}

	GLboolean IsTransformFeedback(GLuint id) const {
		GLboolean res = gl.IsTransformFeedback(id);
		fprintf(GLMethodsDebugFile, "[%4d] IsTransformFeedback(%u) -> %d\n", gl.GetError(), id, res);
		return res;
	}

	GLvoid PauseTransformFeedback() const {
		gl.PauseTransformFeedback();
		fprintf(GLMethodsDebugFile, "[%4d] PauseTransformFeedback()\n", gl.GetError());
	}

	GLvoid ResumeTransformFeedback() const {
		gl.ResumeTransformFeedback();
		fprintf(GLMethodsDebugFile, "[%4d] ResumeTransformFeedback()\n", gl.GetError());
	}

	GLvoid DrawTransformFeedback(GLenum mode, GLuint id) const {
		gl.DrawTransformFeedback(mode, id);
		fprintf(GLMethodsDebugFile, "[%4d] DrawTransformFeedback(0x%x, %u)\n", gl.GetError(), mode, id);
	}

	GLvoid DrawTransformFeedbackStream(GLenum mode, GLuint id, GLuint stream) const {
		gl.DrawTransformFeedbackStream(mode, id, stream);
		fprintf(GLMethodsDebugFile, "[%4d] DrawTransformFeedbackStream(0x%x, %u, %u)\n", gl.GetError(), mode, id, stream);
	}

	GLvoid BeginQueryIndexed(GLenum target, GLuint index, GLuint id) const {
		gl.BeginQueryIndexed(target, index, id);
		fprintf(GLMethodsDebugFile, "[%4d] BeginQueryIndexed(0x%x, %u, %u)\n", gl.GetError(), target, index, id);
	}

	GLvoid EndQueryIndexed(GLenum target, GLuint index) const {
		gl.EndQueryIndexed(target, index);
		fprintf(GLMethodsDebugFile, "[%4d] EndQueryIndexed(0x%x, %u)\n", gl.GetError(), target, index);
	}

	GLvoid GetQueryIndexediv(GLenum target, GLuint index, GLenum pname, GLint * params) const {
		gl.GetQueryIndexediv(target, index, pname, params);
		fprintf(GLMethodsDebugFile, "[%4d] GetQueryIndexediv(0x%x, %u, 0x%x, 0x%p)\n", gl.GetError(), target, index, pname, params);
	}

	GLvoid ReleaseShaderCompiler() const {
		gl.ReleaseShaderCompiler();
		fprintf(GLMethodsDebugFile, "[%4d] ReleaseShaderCompiler()\n", gl.GetError());
	}

	GLvoid ShaderBinary(GLsizei count, const GLuint * shaders, GLenum binaryformat, const GLvoid * binary, GLsizei length) const {
		gl.ShaderBinary(count, shaders, binaryformat, binary, length);
		fprintf(GLMethodsDebugFile, "[%4d] ShaderBinary(%d, 0x%p, 0x%x, 0x%p, %d)\n", gl.GetError(), count, shaders, binaryformat, binary, length);
	}

	GLvoid GetShaderPrecisionFormat(GLenum shadertype, GLenum precisiontype, GLint * range, GLint * precision) const {
		gl.GetShaderPrecisionFormat(shadertype, precisiontype, range, precision);
		fprintf(GLMethodsDebugFile, "[%4d] GetShaderPrecisionFormat(0x%x, 0x%x, 0x%p, 0x%p)\n", gl.GetError(), shadertype, precisiontype, range, precision);
	}

	GLvoid DepthRangef(GLfloat n, GLfloat f) const {
		gl.DepthRangef(n, f);
		fprintf(GLMethodsDebugFile, "[%4d] DepthRangef(%f, %f)\n", gl.GetError(), n, f);
	}

	GLvoid ClearDepthf(GLfloat d) const {
		gl.ClearDepthf(d);
		fprintf(GLMethodsDebugFile, "[%4d] ClearDepthf(%f)\n", gl.GetError(), d);
	}

	GLvoid GetProgramBinary(GLuint program, GLsizei bufSize, GLsizei * length, GLenum * binaryFormat, GLvoid * binary) const {
		gl.GetProgramBinary(program, bufSize, length, binaryFormat, binary);
		fprintf(GLMethodsDebugFile, "[%4d] GetProgramBinary(%u, %d, 0x%p, 0x%p, 0x%p)\n", gl.GetError(), program, bufSize, length, binaryFormat, binary);
	}

	GLvoid ProgramBinary(GLuint program, GLenum binaryFormat, const GLvoid * binary, GLsizei length) const {
		gl.ProgramBinary(program, binaryFormat, binary, length);
		fprintf(GLMethodsDebugFile, "[%4d] ProgramBinary(%u, 0x%x, 0x%p, %d)\n", gl.GetError(), program, binaryFormat, binary, length);
	}

	GLvoid ProgramParameteri(GLuint program, GLenum pname, GLint value) const {
		gl.ProgramParameteri(program, pname, value);
		fprintf(GLMethodsDebugFile, "[%4d] ProgramParameteri(%u, 0x%x, %d)\n", gl.GetError(), program, pname, value);
	}

	GLvoid UseProgramStages(GLuint pipeline, GLbitfield stages, GLuint program) const {
		gl.UseProgramStages(pipeline, stages, program);
		fprintf(GLMethodsDebugFile, "[%4d] UseProgramStages(%u, 0x%x, %u)\n", gl.GetError(), pipeline, stages, program);
	}

	GLvoid ActiveShaderProgram(GLuint pipeline, GLuint program) const {
		gl.ActiveShaderProgram(pipeline, program);
		fprintf(GLMethodsDebugFile, "[%4d] ActiveShaderProgram(%u, %u)\n", gl.GetError(), pipeline, program);
	}

	GLuint CreateShaderProgramv(GLenum type, GLsizei count, const GLchar * const* strings) const {
		GLuint res = gl.CreateShaderProgramv(type, count, strings);
		fprintf(GLMethodsDebugFile, "[%4d] CreateShaderProgramv(0x%x, %d, 0x%p) -> %u\n", gl.GetError(), type, count, strings, res);
		return res;
	}

	GLvoid BindProgramPipeline(GLuint pipeline) const {
		gl.BindProgramPipeline(pipeline);
		fprintf(GLMethodsDebugFile, "[%4d] BindProgramPipeline(%u)\n", gl.GetError(), pipeline);
	}

	GLvoid DeleteProgramPipelines(GLsizei n, const GLuint * pipelines) const {
		gl.DeleteProgramPipelines(n, pipelines);
		fprintf(GLMethodsDebugFile, "[%4d] DeleteProgramPipelines(%d, 0x%p)\n", gl.GetError(), n, pipelines);
	}

	GLvoid GenProgramPipelines(GLsizei n, GLuint * pipelines) const {
		gl.GenProgramPipelines(n, pipelines);
		fprintf(GLMethodsDebugFile, "[%4d] GenProgramPipelines(%d, 0x%p)\n", gl.GetError(), n, pipelines);
	}

	GLboolean IsProgramPipeline(GLuint pipeline) const {
		GLboolean res = gl.IsProgramPipeline(pipeline);
		fprintf(GLMethodsDebugFile, "[%4d] IsProgramPipeline(%u) -> %d\n", gl.GetError(), pipeline, res);
		return res;
	}

	GLvoid GetProgramPipelineiv(GLuint pipeline, GLenum pname, GLint * params) const {
		gl.GetProgramPipelineiv(pipeline, pname, params);
		fprintf(GLMethodsDebugFile, "[%4d] GetProgramPipelineiv(%u, 0x%x, 0x%p)\n", gl.GetError(), pipeline, pname, params);
	}

	// GLvoid ProgramUniform1i(GLuint program, GLint location, GLint v0) const {
	// 	gl.ProgramUniform1i(program, location, v0);
	// 	fprintf(GLMethodsDebugFile, "[%4d] ProgramUniform1i(%u, %d, %d)\n", gl.GetError(), program, location, v0);
	// }

	// GLvoid ProgramUniform1iv(GLuint program, GLint location, GLsizei count, const GLint * value) const {
	// 	gl.ProgramUniform1iv(program, location, count, value);
	// 	fprintf(GLMethodsDebugFile, "[%4d] ProgramUniform1iv(%u, %d, %d, 0x%p)\n", gl.GetError(), program, location, count, value);
	// }

	// GLvoid ProgramUniform1f(GLuint program, GLint location, GLfloat v0) const {
	// 	gl.ProgramUniform1f(program, location, v0);
	// 	fprintf(GLMethodsDebugFile, "[%4d] ProgramUniform1f(%u, %d, %f)\n", gl.GetError(), program, location, v0);
	// }

	// GLvoid ProgramUniform1fv(GLuint program, GLint location, GLsizei count, const GLfloat * value) const {
	// 	gl.ProgramUniform1fv(program, location, count, value);
	// 	fprintf(GLMethodsDebugFile, "[%4d] ProgramUniform1fv(%u, %d, %d, 0x%p)\n", gl.GetError(), program, location, count, value);
	// }

	// GLvoid ProgramUniform1d(GLuint program, GLint location, GLdouble v0) const {
	// 	gl.ProgramUniform1d(program, location, v0);
	// 	fprintf(GLMethodsDebugFile, "[%4d] ProgramUniform1d(%u, %d, %lf)\n", gl.GetError(), program, location, v0);
	// }

	// GLvoid ProgramUniform1dv(GLuint program, GLint location, GLsizei count, const GLdouble * value) const {
	// 	gl.ProgramUniform1dv(program, location, count, value);
	// 	fprintf(GLMethodsDebugFile, "[%4d] ProgramUniform1dv(%u, %d, %d, 0x%p)\n", gl.GetError(), program, location, count, value);
	// }

	// GLvoid ProgramUniform1ui(GLuint program, GLint location, GLuint v0) const {
	// 	gl.ProgramUniform1ui(program, location, v0);
	// 	fprintf(GLMethodsDebugFile, "[%4d] ProgramUniform1ui(%u, %d, %u)\n", gl.GetError(), program, location, v0);
	// }

	// GLvoid ProgramUniform1uiv(GLuint program, GLint location, GLsizei count, const GLuint * value) const {
	// 	gl.ProgramUniform1uiv(program, location, count, value);
	// 	fprintf(GLMethodsDebugFile, "[%4d] ProgramUniform1uiv(%u, %d, %d, 0x%p)\n", gl.GetError(), program, location, count, value);
	// }

	// GLvoid ProgramUniform2i(GLuint program, GLint location, GLint v0, GLint v1) const {
	// 	gl.ProgramUniform2i(program, location, v0, v1);
	// 	fprintf(GLMethodsDebugFile, "[%4d] ProgramUniform2i(%u, %d, %d, %d)\n", gl.GetError(), program, location, v0, v1);
	// }

	// GLvoid ProgramUniform2iv(GLuint program, GLint location, GLsizei count, const GLint * value) const {
	// 	gl.ProgramUniform2iv(program, location, count, value);
	// 	fprintf(GLMethodsDebugFile, "[%4d] ProgramUniform2iv(%u, %d, %d, 0x%p)\n", gl.GetError(), program, location, count, value);
	// }

	// GLvoid ProgramUniform2f(GLuint program, GLint location, GLfloat v0, GLfloat v1) const {
	// 	gl.ProgramUniform2f(program, location, v0, v1);
	// 	fprintf(GLMethodsDebugFile, "[%4d] ProgramUniform2f(%u, %d, %f, %f)\n", gl.GetError(), program, location, v0, v1);
	// }

	// GLvoid ProgramUniform2fv(GLuint program, GLint location, GLsizei count, const GLfloat * value) const {
	// 	gl.ProgramUniform2fv(program, location, count, value);
	// 	fprintf(GLMethodsDebugFile, "[%4d] ProgramUniform2fv(%u, %d, %d, 0x%p)\n", gl.GetError(), program, location, count, value);
	// }

	// GLvoid ProgramUniform2d(GLuint program, GLint location, GLdouble v0, GLdouble v1) const {
	// 	gl.ProgramUniform2d(program, location, v0, v1);
	// 	fprintf(GLMethodsDebugFile, "[%4d] ProgramUniform2d(%u, %d, %lf, %lf)\n", gl.GetError(), program, location, v0, v1);
	// }

	// GLvoid ProgramUniform2dv(GLuint program, GLint location, GLsizei count, const GLdouble * value) const {
	// 	gl.ProgramUniform2dv(program, location, count, value);
	// 	fprintf(GLMethodsDebugFile, "[%4d] ProgramUniform2dv(%u, %d, %d, 0x%p)\n", gl.GetError(), program, location, count, value);
	// }

	// GLvoid ProgramUniform2ui(GLuint program, GLint location, GLuint v0, GLuint v1) const {
	// 	gl.ProgramUniform2ui(program, location, v0, v1);
	// 	fprintf(GLMethodsDebugFile, "[%4d] ProgramUniform2ui(%u, %d, %u, %u)\n", gl.GetError(), program, location, v0, v1);
	// }

	// GLvoid ProgramUniform2uiv(GLuint program, GLint location, GLsizei count, const GLuint * value) const {
	// 	gl.ProgramUniform2uiv(program, location, count, value);
	// 	fprintf(GLMethodsDebugFile, "[%4d] ProgramUniform2uiv(%u, %d, %d, 0x%p)\n", gl.GetError(), program, location, count, value);
	// }

	// GLvoid ProgramUniform3i(GLuint program, GLint location, GLint v0, GLint v1, GLint v2) const {
	// 	gl.ProgramUniform3i(program, location, v0, v1, v2);
	// 	fprintf(GLMethodsDebugFile, "[%4d] ProgramUniform3i(%u, %d, %d, %d, %d)\n", gl.GetError(), program, location, v0, v1, v2);
	// }

	// GLvoid ProgramUniform3iv(GLuint program, GLint location, GLsizei count, const GLint * value) const {
	// 	gl.ProgramUniform3iv(program, location, count, value);
	// 	fprintf(GLMethodsDebugFile, "[%4d] ProgramUniform3iv(%u, %d, %d, 0x%p)\n", gl.GetError(), program, location, count, value);
	// }

	// GLvoid ProgramUniform3f(GLuint program, GLint location, GLfloat v0, GLfloat v1, GLfloat v2) const {
	// 	gl.ProgramUniform3f(program, location, v0, v1, v2);
	// 	fprintf(GLMethodsDebugFile, "[%4d] ProgramUniform3f(%u, %d, %f, %f, %f)\n", gl.GetError(), program, location, v0, v1, v2);
	// }

	// GLvoid ProgramUniform3fv(GLuint program, GLint location, GLsizei count, const GLfloat * value) const {
	// 	gl.ProgramUniform3fv(program, location, count, value);
	// 	fprintf(GLMethodsDebugFile, "[%4d] ProgramUniform3fv(%u, %d, %d, 0x%p)\n", gl.GetError(), program, location, count, value);
	// }

	// GLvoid ProgramUniform3d(GLuint program, GLint location, GLdouble v0, GLdouble v1, GLdouble v2) const {
	// 	gl.ProgramUniform3d(program, location, v0, v1, v2);
	// 	fprintf(GLMethodsDebugFile, "[%4d] ProgramUniform3d(%u, %d, %lf, %lf, %lf)\n", gl.GetError(), program, location, v0, v1, v2);
	// }

	// GLvoid ProgramUniform3dv(GLuint program, GLint location, GLsizei count, const GLdouble * value) const {
	// 	gl.ProgramUniform3dv(program, location, count, value);
	// 	fprintf(GLMethodsDebugFile, "[%4d] ProgramUniform3dv(%u, %d, %d, 0x%p)\n", gl.GetError(), program, location, count, value);
	// }

	// GLvoid ProgramUniform3ui(GLuint program, GLint location, GLuint v0, GLuint v1, GLuint v2) const {
	// 	gl.ProgramUniform3ui(program, location, v0, v1, v2);
	// 	fprintf(GLMethodsDebugFile, "[%4d] ProgramUniform3ui(%u, %d, %u, %u, %u)\n", gl.GetError(), program, location, v0, v1, v2);
	// }

	// GLvoid ProgramUniform3uiv(GLuint program, GLint location, GLsizei count, const GLuint * value) const {
	// 	gl.ProgramUniform3uiv(program, location, count, value);
	// 	fprintf(GLMethodsDebugFile, "[%4d] ProgramUniform3uiv(%u, %d, %d, 0x%p)\n", gl.GetError(), program, location, count, value);
	// }

	// GLvoid ProgramUniform4i(GLuint program, GLint location, GLint v0, GLint v1, GLint v2, GLint v3) const {
	// 	gl.ProgramUniform4i(program, location, v0, v1, v2, v3);
	// 	fprintf(GLMethodsDebugFile, "[%4d] ProgramUniform4i(%u, %d, %d, %d, %d, %d)\n", gl.GetError(), program, location, v0, v1, v2, v3);
	// }

	// GLvoid ProgramUniform4iv(GLuint program, GLint location, GLsizei count, const GLint * value) const {
	// 	gl.ProgramUniform4iv(program, location, count, value);
	// 	fprintf(GLMethodsDebugFile, "[%4d] ProgramUniform4iv(%u, %d, %d, 0x%p)\n", gl.GetError(), program, location, count, value);
	// }

	// GLvoid ProgramUniform4f(GLuint program, GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3) const {
	// 	gl.ProgramUniform4f(program, location, v0, v1, v2, v3);
	// 	fprintf(GLMethodsDebugFile, "[%4d] ProgramUniform4f(%u, %d, %f, %f, %f, %f)\n", gl.GetError(), program, location, v0, v1, v2, v3);
	// }

	// GLvoid ProgramUniform4fv(GLuint program, GLint location, GLsizei count, const GLfloat * value) const {
	// 	gl.ProgramUniform4fv(program, location, count, value);
	// 	fprintf(GLMethodsDebugFile, "[%4d] ProgramUniform4fv(%u, %d, %d, 0x%p)\n", gl.GetError(), program, location, count, value);
	// }

	// GLvoid ProgramUniform4d(GLuint program, GLint location, GLdouble v0, GLdouble v1, GLdouble v2, GLdouble v3) const {
	// 	gl.ProgramUniform4d(program, location, v0, v1, v2, v3);
	// 	fprintf(GLMethodsDebugFile, "[%4d] ProgramUniform4d(%u, %d, %lf, %lf, %lf, %lf)\n", gl.GetError(), program, location, v0, v1, v2, v3);
	// }

	// GLvoid ProgramUniform4dv(GLuint program, GLint location, GLsizei count, const GLdouble * value) const {
	// 	gl.ProgramUniform4dv(program, location, count, value);
	// 	fprintf(GLMethodsDebugFile, "[%4d] ProgramUniform4dv(%u, %d, %d, 0x%p)\n", gl.GetError(), program, location, count, value);
	// }

	// GLvoid ProgramUniform4ui(GLuint program, GLint location, GLuint v0, GLuint v1, GLuint v2, GLuint v3) const {
	// 	gl.ProgramUniform4ui(program, location, v0, v1, v2, v3);
	// 	fprintf(GLMethodsDebugFile, "[%4d] ProgramUniform4ui(%u, %d, %u, %u, %u, %u)\n", gl.GetError(), program, location, v0, v1, v2, v3);
	// }

	// GLvoid ProgramUniform4uiv(GLuint program, GLint location, GLsizei count, const GLuint * value) const {
	// 	gl.ProgramUniform4uiv(program, location, count, value);
	// 	fprintf(GLMethodsDebugFile, "[%4d] ProgramUniform4uiv(%u, %d, %d, 0x%p)\n", gl.GetError(), program, location, count, value);
	// }

	// GLvoid ProgramUniformMatrix2fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat * value) const {
	// 	gl.ProgramUniformMatrix2fv(program, location, count, transpose, value);
	// 	fprintf(GLMethodsDebugFile, "[%4d] ProgramUniformMatrix2fv(%u, %d, %d, %d, 0x%p)\n", gl.GetError(), program, location, count, transpose, value);
	// }

	// GLvoid ProgramUniformMatrix3fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat * value) const {
	// 	gl.ProgramUniformMatrix3fv(program, location, count, transpose, value);
	// 	fprintf(GLMethodsDebugFile, "[%4d] ProgramUniformMatrix3fv(%u, %d, %d, %d, 0x%p)\n", gl.GetError(), program, location, count, transpose, value);
	// }

	// GLvoid ProgramUniformMatrix4fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat * value) const {
	// 	gl.ProgramUniformMatrix4fv(program, location, count, transpose, value);
	// 	fprintf(GLMethodsDebugFile, "[%4d] ProgramUniformMatrix4fv(%u, %d, %d, %d, 0x%p)\n", gl.GetError(), program, location, count, transpose, value);
	// }

	// GLvoid ProgramUniformMatrix2dv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble * value) const {
	// 	gl.ProgramUniformMatrix2dv(program, location, count, transpose, value);
	// 	fprintf(GLMethodsDebugFile, "[%4d] ProgramUniformMatrix2dv(%u, %d, %d, %d, 0x%p)\n", gl.GetError(), program, location, count, transpose, value);
	// }

	// GLvoid ProgramUniformMatrix3dv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble * value) const {
	// 	gl.ProgramUniformMatrix3dv(program, location, count, transpose, value);
	// 	fprintf(GLMethodsDebugFile, "[%4d] ProgramUniformMatrix3dv(%u, %d, %d, %d, 0x%p)\n", gl.GetError(), program, location, count, transpose, value);
	// }

	// GLvoid ProgramUniformMatrix4dv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble * value) const {
	// 	gl.ProgramUniformMatrix4dv(program, location, count, transpose, value);
	// 	fprintf(GLMethodsDebugFile, "[%4d] ProgramUniformMatrix4dv(%u, %d, %d, %d, 0x%p)\n", gl.GetError(), program, location, count, transpose, value);
	// }

	// GLvoid ProgramUniformMatrix2x3fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat * value) const {
	// 	gl.ProgramUniformMatrix2x3fv(program, location, count, transpose, value);
	// 	fprintf(GLMethodsDebugFile, "[%4d] ProgramUniformMatrix2x3fv(%u, %d, %d, %d, 0x%p)\n", gl.GetError(), program, location, count, transpose, value);
	// }

	// GLvoid ProgramUniformMatrix3x2fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat * value) const {
	// 	gl.ProgramUniformMatrix3x2fv(program, location, count, transpose, value);
	// 	fprintf(GLMethodsDebugFile, "[%4d] ProgramUniformMatrix3x2fv(%u, %d, %d, %d, 0x%p)\n", gl.GetError(), program, location, count, transpose, value);
	// }

	// GLvoid ProgramUniformMatrix2x4fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat * value) const {
	// 	gl.ProgramUniformMatrix2x4fv(program, location, count, transpose, value);
	// 	fprintf(GLMethodsDebugFile, "[%4d] ProgramUniformMatrix2x4fv(%u, %d, %d, %d, 0x%p)\n", gl.GetError(), program, location, count, transpose, value);
	// }

	// GLvoid ProgramUniformMatrix4x2fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat * value) const {
	// 	gl.ProgramUniformMatrix4x2fv(program, location, count, transpose, value);
	// 	fprintf(GLMethodsDebugFile, "[%4d] ProgramUniformMatrix4x2fv(%u, %d, %d, %d, 0x%p)\n", gl.GetError(), program, location, count, transpose, value);
	// }

	// GLvoid ProgramUniformMatrix3x4fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat * value) const {
	// 	gl.ProgramUniformMatrix3x4fv(program, location, count, transpose, value);
	// 	fprintf(GLMethodsDebugFile, "[%4d] ProgramUniformMatrix3x4fv(%u, %d, %d, %d, 0x%p)\n", gl.GetError(), program, location, count, transpose, value);
	// }

	// GLvoid ProgramUniformMatrix4x3fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat * value) const {
	// 	gl.ProgramUniformMatrix4x3fv(program, location, count, transpose, value);
	// 	fprintf(GLMethodsDebugFile, "[%4d] ProgramUniformMatrix4x3fv(%u, %d, %d, %d, 0x%p)\n", gl.GetError(), program, location, count, transpose, value);
	// }

	// GLvoid ProgramUniformMatrix2x3dv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble * value) const {
	// 	gl.ProgramUniformMatrix2x3dv(program, location, count, transpose, value);
	// 	fprintf(GLMethodsDebugFile, "[%4d] ProgramUniformMatrix2x3dv(%u, %d, %d, %d, 0x%p)\n", gl.GetError(), program, location, count, transpose, value);
	// }

	// GLvoid ProgramUniformMatrix3x2dv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble * value) const {
	// 	gl.ProgramUniformMatrix3x2dv(program, location, count, transpose, value);
	// 	fprintf(GLMethodsDebugFile, "[%4d] ProgramUniformMatrix3x2dv(%u, %d, %d, %d, 0x%p)\n", gl.GetError(), program, location, count, transpose, value);
	// }

	// GLvoid ProgramUniformMatrix2x4dv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble * value) const {
	// 	gl.ProgramUniformMatrix2x4dv(program, location, count, transpose, value);
	// 	fprintf(GLMethodsDebugFile, "[%4d] ProgramUniformMatrix2x4dv(%u, %d, %d, %d, 0x%p)\n", gl.GetError(), program, location, count, transpose, value);
	// }

	// GLvoid ProgramUniformMatrix4x2dv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble * value) const {
	// 	gl.ProgramUniformMatrix4x2dv(program, location, count, transpose, value);
	// 	fprintf(GLMethodsDebugFile, "[%4d] ProgramUniformMatrix4x2dv(%u, %d, %d, %d, 0x%p)\n", gl.GetError(), program, location, count, transpose, value);
	// }

	// GLvoid ProgramUniformMatrix3x4dv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble * value) const {
	// 	gl.ProgramUniformMatrix3x4dv(program, location, count, transpose, value);
	// 	fprintf(GLMethodsDebugFile, "[%4d] ProgramUniformMatrix3x4dv(%u, %d, %d, %d, 0x%p)\n", gl.GetError(), program, location, count, transpose, value);
	// }

	// GLvoid ProgramUniformMatrix4x3dv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble * value) const {
	// 	gl.ProgramUniformMatrix4x3dv(program, location, count, transpose, value);
	// 	fprintf(GLMethodsDebugFile, "[%4d] ProgramUniformMatrix4x3dv(%u, %d, %d, %d, 0x%p)\n", gl.GetError(), program, location, count, transpose, value);
	// }

	GLvoid ValidateProgramPipeline(GLuint pipeline) const {
		gl.ValidateProgramPipeline(pipeline);
		fprintf(GLMethodsDebugFile, "[%4d] ValidateProgramPipeline(%u)\n", gl.GetError(), pipeline);
	}

	GLvoid GetProgramPipelineInfoLog(GLuint pipeline, GLsizei bufSize, GLsizei * length, GLchar * infoLog) const {
		gl.GetProgramPipelineInfoLog(pipeline, bufSize, length, infoLog);
		fprintf(GLMethodsDebugFile, "[%4d] GetProgramPipelineInfoLog(%u, %d, 0x%p, 0x%p)\n", gl.GetError(), pipeline, bufSize, length, infoLog);
	}

	GLvoid VertexAttribL1d(GLuint index, GLdouble x) const {
		gl.VertexAttribL1d(index, x);
		fprintf(GLMethodsDebugFile, "[%4d] VertexAttribL1d(%u, %lf)\n", gl.GetError(), index, x);
	}

	GLvoid VertexAttribL2d(GLuint index, GLdouble x, GLdouble y) const {
		gl.VertexAttribL2d(index, x, y);
		fprintf(GLMethodsDebugFile, "[%4d] VertexAttribL2d(%u, %lf, %lf)\n", gl.GetError(), index, x, y);
	}

	GLvoid VertexAttribL3d(GLuint index, GLdouble x, GLdouble y, GLdouble z) const {
		gl.VertexAttribL3d(index, x, y, z);
		fprintf(GLMethodsDebugFile, "[%4d] VertexAttribL3d(%u, %lf, %lf, %lf)\n", gl.GetError(), index, x, y, z);
	}

	GLvoid VertexAttribL4d(GLuint index, GLdouble x, GLdouble y, GLdouble z, GLdouble w) const {
		gl.VertexAttribL4d(index, x, y, z, w);
		fprintf(GLMethodsDebugFile, "[%4d] VertexAttribL4d(%u, %lf, %lf, %lf, %lf)\n", gl.GetError(), index, x, y, z, w);
	}

	GLvoid VertexAttribL1dv(GLuint index, const GLdouble * v) const {
		gl.VertexAttribL1dv(index, v);
		fprintf(GLMethodsDebugFile, "[%4d] VertexAttribL1dv(%u, 0x%p)\n", gl.GetError(), index, v);
	}

	GLvoid VertexAttribL2dv(GLuint index, const GLdouble * v) const {
		gl.VertexAttribL2dv(index, v);
		fprintf(GLMethodsDebugFile, "[%4d] VertexAttribL2dv(%u, 0x%p)\n", gl.GetError(), index, v);
	}

	GLvoid VertexAttribL3dv(GLuint index, const GLdouble * v) const {
		gl.VertexAttribL3dv(index, v);
		fprintf(GLMethodsDebugFile, "[%4d] VertexAttribL3dv(%u, 0x%p)\n", gl.GetError(), index, v);
	}

	GLvoid VertexAttribL4dv(GLuint index, const GLdouble * v) const {
		gl.VertexAttribL4dv(index, v);
		fprintf(GLMethodsDebugFile, "[%4d] VertexAttribL4dv(%u, 0x%p)\n", gl.GetError(), index, v);
	}

	// GLvoid VertexAttribLPointer(GLuint index, GLint size, GLenum type, GLsizei stride, const GLvoid * pointer) const {
	// 	gl.VertexAttribLPointer(index, size, type, stride, pointer);
	// 	fprintf(GLMethodsDebugFile, "[%4d] VertexAttribLPointer(%u, %d, 0x%x, %d, 0x%p)\n", gl.GetError(), index, size, type, stride, pointer);
	// }

	GLvoid GetVertexAttribLdv(GLuint index, GLenum pname, GLdouble * params) const {
		gl.GetVertexAttribLdv(index, pname, params);
		fprintf(GLMethodsDebugFile, "[%4d] GetVertexAttribLdv(%u, 0x%x, 0x%p)\n", gl.GetError(), index, pname, params);
	}

	GLvoid ViewportArrayv(GLuint first, GLsizei count, const GLfloat * v) const {
		gl.ViewportArrayv(first, count, v);
		fprintf(GLMethodsDebugFile, "[%4d] ViewportArrayv(%u, %d, 0x%p)\n", gl.GetError(), first, count, v);
	}

	GLvoid ViewportIndexedf(GLuint index, GLfloat x, GLfloat y, GLfloat w, GLfloat h) const {
		gl.ViewportIndexedf(index, x, y, w, h);
		fprintf(GLMethodsDebugFile, "[%4d] ViewportIndexedf(%u, %f, %f, %f, %f)\n", gl.GetError(), index, x, y, w, h);
	}

	GLvoid ViewportIndexedfv(GLuint index, const GLfloat * v) const {
		gl.ViewportIndexedfv(index, v);
		fprintf(GLMethodsDebugFile, "[%4d] ViewportIndexedfv(%u, 0x%p)\n", gl.GetError(), index, v);
	}

	GLvoid ScissorArrayv(GLuint first, GLsizei count, const GLint * v) const {
		gl.ScissorArrayv(first, count, v);
		fprintf(GLMethodsDebugFile, "[%4d] ScissorArrayv(%u, %d, 0x%p)\n", gl.GetError(), first, count, v);
	}

	GLvoid ScissorIndexed(GLuint index, GLint left, GLint bottom, GLsizei width, GLsizei height) const {
		gl.ScissorIndexed(index, left, bottom, width, height);
		fprintf(GLMethodsDebugFile, "[%4d] ScissorIndexed(%u, %d, %d, %d, %d)\n", gl.GetError(), index, left, bottom, width, height);
	}

	GLvoid ScissorIndexedv(GLuint index, const GLint * v) const {
		gl.ScissorIndexedv(index, v);
		fprintf(GLMethodsDebugFile, "[%4d] ScissorIndexedv(%u, 0x%p)\n", gl.GetError(), index, v);
	}

	GLvoid DepthRangeArrayv(GLuint first, GLsizei count, const GLdouble * v) const {
		gl.DepthRangeArrayv(first, count, v);
		fprintf(GLMethodsDebugFile, "[%4d] DepthRangeArrayv(%u, %d, 0x%p)\n", gl.GetError(), first, count, v);
	}

	GLvoid DepthRangeIndexed(GLuint index, GLdouble n, GLdouble f) const {
		gl.DepthRangeIndexed(index, n, f);
		fprintf(GLMethodsDebugFile, "[%4d] DepthRangeIndexed(%u, %lf, %lf)\n", gl.GetError(), index, n, f);
	}

	GLvoid GetFloati_v(GLenum target, GLuint index, GLfloat * data) const {
		gl.GetFloati_v(target, index, data);
		fprintf(GLMethodsDebugFile, "[%4d] GetFloati_v(0x%x, %u, 0x%p)\n", gl.GetError(), target, index, data);
	}

	GLvoid GetDoublei_v(GLenum target, GLuint index, GLdouble * data) const {
		gl.GetDoublei_v(target, index, data);
		fprintf(GLMethodsDebugFile, "[%4d] GetDoublei_v(0x%x, %u, 0x%p)\n", gl.GetError(), target, index, data);
	}

	GLvoid DrawArraysInstancedBaseInstance(GLenum mode, GLint first, GLsizei count, GLsizei instancecount, GLuint baseinstance) const {
		gl.DrawArraysInstancedBaseInstance(mode, first, count, instancecount, baseinstance);
		fprintf(GLMethodsDebugFile, "[%4d] DrawArraysInstancedBaseInstance(0x%x, %d, %d, %d, %u)\n", gl.GetError(), mode, first, count, instancecount, baseinstance);
	}

	GLvoid DrawElementsInstancedBaseInstance(GLenum mode, GLsizei count, GLenum type, const GLvoid * indices, GLsizei instancecount, GLuint baseinstance) const {
		gl.DrawElementsInstancedBaseInstance(mode, count, type, indices, instancecount, baseinstance);
		fprintf(GLMethodsDebugFile, "[%4d] DrawElementsInstancedBaseInstance(0x%x, %d, 0x%x, 0x%p, %d, %u)\n", gl.GetError(), mode, count, type, indices, instancecount, baseinstance);
	}

	GLvoid DrawElementsInstancedBaseVertexBaseInstance(GLenum mode, GLsizei count, GLenum type, const GLvoid * indices, GLsizei instancecount, GLint basevertex, GLuint baseinstance) const {
		gl.DrawElementsInstancedBaseVertexBaseInstance(mode, count, type, indices, instancecount, basevertex, baseinstance);
		fprintf(GLMethodsDebugFile, "[%4d] DrawElementsInstancedBaseVertexBaseInstance(0x%x, %d, 0x%x, 0x%p, %d, %d, %u)\n", gl.GetError(), mode, count, type, indices, instancecount, basevertex, baseinstance);
	}

	GLvoid GetInternalformativ(GLenum target, GLenum internalformat, GLenum pname, GLsizei bufSize, GLint * params) const {
		gl.GetInternalformativ(target, internalformat, pname, bufSize, params);
		fprintf(GLMethodsDebugFile, "[%4d] GetInternalformativ(0x%x, 0x%x, 0x%x, %d, 0x%p)\n", gl.GetError(), target, internalformat, pname, bufSize, params);
	}

	GLvoid GetActiveAtomicCounterBufferiv(GLuint program, GLuint bufferIndex, GLenum pname, GLint * params) const {
		gl.GetActiveAtomicCounterBufferiv(program, bufferIndex, pname, params);
		fprintf(GLMethodsDebugFile, "[%4d] GetActiveAtomicCounterBufferiv(%u, %u, 0x%x, 0x%p)\n", gl.GetError(), program, bufferIndex, pname, params);
	}

	GLvoid BindImageTexture(GLuint unit, GLuint texture, GLint level, GLboolean layered, GLint layer, GLenum access, GLenum format) const {
		gl.BindImageTexture(unit, texture, level, layered, layer, access, format);
		fprintf(GLMethodsDebugFile, "[%4d] BindImageTexture(%u, %u, %d, %d, %d, 0x%x, 0x%x)\n", gl.GetError(), unit, texture, level, layered, layer, access, format);
	}

	GLvoid MemoryBarrier(GLbitfield barriers) const {
		gl.MemoryBarrier(barriers);
		fprintf(GLMethodsDebugFile, "[%4d] MemoryBarrier(0x%x)\n", gl.GetError(), barriers);
	}

	GLvoid TexStorage1D(GLenum target, GLsizei levels, GLenum internalformat, GLsizei width) const {
		gl.TexStorage1D(target, levels, internalformat, width);
		fprintf(GLMethodsDebugFile, "[%4d] TexStorage1D(0x%x, %d, 0x%x, %d)\n", gl.GetError(), target, levels, internalformat, width);
	}

	GLvoid TexStorage2D(GLenum target, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height) const {
		gl.TexStorage2D(target, levels, internalformat, width, height);
		fprintf(GLMethodsDebugFile, "[%4d] TexStorage2D(0x%x, %d, 0x%x, %d, %d)\n", gl.GetError(), target, levels, internalformat, width, height);
	}

	GLvoid TexStorage3D(GLenum target, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth) const {
		gl.TexStorage3D(target, levels, internalformat, width, height, depth);
		fprintf(GLMethodsDebugFile, "[%4d] TexStorage3D(0x%x, %d, 0x%x, %d, %d, %d)\n", gl.GetError(), target, levels, internalformat, width, height, depth);
	}

	GLvoid DrawTransformFeedbackInstanced(GLenum mode, GLuint id, GLsizei instancecount) const {
		gl.DrawTransformFeedbackInstanced(mode, id, instancecount);
		fprintf(GLMethodsDebugFile, "[%4d] DrawTransformFeedbackInstanced(0x%x, %u, %d)\n", gl.GetError(), mode, id, instancecount);
	}

	GLvoid DrawTransformFeedbackStreamInstanced(GLenum mode, GLuint id, GLuint stream, GLsizei instancecount) const {
		gl.DrawTransformFeedbackStreamInstanced(mode, id, stream, instancecount);
		fprintf(GLMethodsDebugFile, "[%4d] DrawTransformFeedbackStreamInstanced(0x%x, %u, %u, %d)\n", gl.GetError(), mode, id, stream, instancecount);
	}

	GLvoid ClearBufferData(GLenum target, GLenum internalformat, GLenum format, GLenum type, const GLvoid * data) const {
		gl.ClearBufferData(target, internalformat, format, type, data);
		fprintf(GLMethodsDebugFile, "[%4d] ClearBufferData(0x%x, 0x%x, 0x%x, 0x%x, 0x%p)\n", gl.GetError(), target, internalformat, format, type, data);
	}

	GLvoid ClearBufferSubData(GLenum target, GLenum internalformat, GLintptr offset, GLsizeiptr size, GLenum format, GLenum type, const GLvoid * data) const {
		gl.ClearBufferSubData(target, internalformat, offset, size, format, type, data);
		fprintf(GLMethodsDebugFile, "[%4d] ClearBufferSubData(0x%x, 0x%x, %" LL "d, %" LL "d, 0x%x, 0x%x, 0x%p)\n", gl.GetError(), target, internalformat, offset, size, format, type, data);
	}

	GLvoid DispatchCompute(GLuint num_groups_x, GLuint num_groups_y, GLuint num_groups_z) const {
		gl.DispatchCompute(num_groups_x, num_groups_y, num_groups_z);
		fprintf(GLMethodsDebugFile, "[%4d] DispatchCompute(%u, %u, %u)\n", gl.GetError(), num_groups_x, num_groups_y, num_groups_z);
	}

	GLvoid DispatchComputeIndirect(GLintptr indirect) const {
		gl.DispatchComputeIndirect(indirect);
		fprintf(GLMethodsDebugFile, "[%4d] DispatchComputeIndirect(%" LL "d)\n", gl.GetError(), indirect);
	}

	GLvoid CopyImageSubData(GLuint srcName, GLenum srcTarget, GLint srcLevel, GLint srcX, GLint srcY, GLint srcZ, GLuint dstName, GLenum dstTarget, GLint dstLevel, GLint dstX, GLint dstY, GLint dstZ, GLsizei srcWidth, GLsizei srcHeight, GLsizei srcDepth) const {
		gl.CopyImageSubData(srcName, srcTarget, srcLevel, srcX, srcY, srcZ, dstName, dstTarget, dstLevel, dstX, dstY, dstZ, srcWidth, srcHeight, srcDepth);
		fprintf(GLMethodsDebugFile, "[%4d] CopyImageSubData(%u, 0x%x, %d, %d, %d, %d, %u, 0x%x, %d, %d, %d, %d, %d, %d, %d)\n", gl.GetError(), srcName, srcTarget, srcLevel, srcX, srcY, srcZ, dstName, dstTarget, dstLevel, dstX, dstY, dstZ, srcWidth, srcHeight, srcDepth);
	}

	GLvoid FramebufferParameteri(GLenum target, GLenum pname, GLint param) const {
		gl.FramebufferParameteri(target, pname, param);
		fprintf(GLMethodsDebugFile, "[%4d] FramebufferParameteri(0x%x, 0x%x, %d)\n", gl.GetError(), target, pname, param);
	}

	GLvoid GetFramebufferParameteriv(GLenum target, GLenum pname, GLint * params) const {
		gl.GetFramebufferParameteriv(target, pname, params);
		fprintf(GLMethodsDebugFile, "[%4d] GetFramebufferParameteriv(0x%x, 0x%x, 0x%p)\n", gl.GetError(), target, pname, params);
	}

	GLvoid GetInternalformati64v(GLenum target, GLenum internalformat, GLenum pname, GLsizei bufSize, GLint64 * params) const {
		gl.GetInternalformati64v(target, internalformat, pname, bufSize, params);
		fprintf(GLMethodsDebugFile, "[%4d] GetInternalformati64v(0x%x, 0x%x, 0x%x, %d, 0x%p)\n", gl.GetError(), target, internalformat, pname, bufSize, params);
	}

	GLvoid InvalidateTexSubImage(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth) const {
		gl.InvalidateTexSubImage(texture, level, xoffset, yoffset, zoffset, width, height, depth);
		fprintf(GLMethodsDebugFile, "[%4d] InvalidateTexSubImage(%u, %d, %d, %d, %d, %d, %d, %d)\n", gl.GetError(), texture, level, xoffset, yoffset, zoffset, width, height, depth);
	}

	GLvoid InvalidateTexImage(GLuint texture, GLint level) const {
		gl.InvalidateTexImage(texture, level);
		fprintf(GLMethodsDebugFile, "[%4d] InvalidateTexImage(%u, %d)\n", gl.GetError(), texture, level);
	}

	GLvoid InvalidateBufferSubData(GLuint buffer, GLintptr offset, GLsizeiptr length) const {
		gl.InvalidateBufferSubData(buffer, offset, length);
		fprintf(GLMethodsDebugFile, "[%4d] InvalidateBufferSubData(%u, %" LL "d, %" LL "d)\n", gl.GetError(), buffer, offset, length);
	}

	GLvoid InvalidateBufferData(GLuint buffer) const {
		gl.InvalidateBufferData(buffer);
		fprintf(GLMethodsDebugFile, "[%4d] InvalidateBufferData(%u)\n", gl.GetError(), buffer);
	}

	GLvoid InvalidateFramebuffer(GLenum target, GLsizei numAttachments, const GLenum * attachments) const {
		gl.InvalidateFramebuffer(target, numAttachments, attachments);
		fprintf(GLMethodsDebugFile, "[%4d] InvalidateFramebuffer(0x%x, %d, 0x%p)\n", gl.GetError(), target, numAttachments, attachments);
	}

	GLvoid InvalidateSubFramebuffer(GLenum target, GLsizei numAttachments, const GLenum * attachments, GLint x, GLint y, GLsizei width, GLsizei height) const {
		gl.InvalidateSubFramebuffer(target, numAttachments, attachments, x, y, width, height);
		fprintf(GLMethodsDebugFile, "[%4d] InvalidateSubFramebuffer(0x%x, %d, 0x%p, %d, %d, %d, %d)\n", gl.GetError(), target, numAttachments, attachments, x, y, width, height);
	}

	GLvoid MultiDrawArraysIndirect(GLenum mode, const GLvoid * indirect, GLsizei drawcount, GLsizei stride) const {
		gl.MultiDrawArraysIndirect(mode, indirect, drawcount, stride);
		fprintf(GLMethodsDebugFile, "[%4d] MultiDrawArraysIndirect(0x%x, 0x%p, %d, %d)\n", gl.GetError(), mode, indirect, drawcount, stride);
	}

	GLvoid MultiDrawElementsIndirect(GLenum mode, GLenum type, const GLvoid * indirect, GLsizei drawcount, GLsizei stride) const {
		gl.MultiDrawElementsIndirect(mode, type, indirect, drawcount, stride);
		fprintf(GLMethodsDebugFile, "[%4d] MultiDrawElementsIndirect(0x%x, 0x%x, 0x%p, %d, %d)\n", gl.GetError(), mode, type, indirect, drawcount, stride);
	}

	GLvoid GetProgramInterfaceiv(GLuint program, GLenum programInterface, GLenum pname, GLint * params) const {
		gl.GetProgramInterfaceiv(program, programInterface, pname, params);
		fprintf(GLMethodsDebugFile, "[%4d] GetProgramInterfaceiv(%u, 0x%x, 0x%x, 0x%p)\n", gl.GetError(), program, programInterface, pname, params);
	}

	GLuint GetProgramResourceIndex(GLuint program, GLenum programInterface, const GLchar * name) const {
		GLuint res = gl.GetProgramResourceIndex(program, programInterface, name);
		fprintf(GLMethodsDebugFile, "[%4d] GetProgramResourceIndex(%u, 0x%x, 0x%p) -> %u\n", gl.GetError(), program, programInterface, name, res);
		return res;
	}

	GLvoid GetProgramResourceName(GLuint program, GLenum programInterface, GLuint index, GLsizei bufSize, GLsizei * length, GLchar * name) const {
		gl.GetProgramResourceName(program, programInterface, index, bufSize, length, name);
		fprintf(GLMethodsDebugFile, "[%4d] GetProgramResourceName(%u, 0x%x, %u, %d, 0x%p, 0x%p)\n", gl.GetError(), program, programInterface, index, bufSize, length, name);
	}

	GLvoid GetProgramResourceiv(GLuint program, GLenum programInterface, GLuint index, GLsizei propCount, const GLenum * props, GLsizei bufSize, GLsizei * length, GLint * params) const {
		gl.GetProgramResourceiv(program, programInterface, index, propCount, props, bufSize, length, params);
		fprintf(GLMethodsDebugFile, "[%4d] GetProgramResourceiv(%u, 0x%x, %u, %d, 0x%p, %d, 0x%p, 0x%p)\n", gl.GetError(), program, programInterface, index, propCount, props, bufSize, length, params);
	}

	GLint GetProgramResourceLocation(GLuint program, GLenum programInterface, const GLchar * name) const {
		GLint res = gl.GetProgramResourceLocation(program, programInterface, name);
		fprintf(GLMethodsDebugFile, "[%4d] GetProgramResourceLocation(%u, 0x%x, 0x%p) -> %d\n", gl.GetError(), program, programInterface, name, res);
		return res;
	}

	GLint GetProgramResourceLocationIndex(GLuint program, GLenum programInterface, const GLchar * name) const {
		GLint res = gl.GetProgramResourceLocationIndex(program, programInterface, name);
		fprintf(GLMethodsDebugFile, "[%4d] GetProgramResourceLocationIndex(%u, 0x%x, 0x%p) -> %d\n", gl.GetError(), program, programInterface, name, res);
		return res;
	}

	GLvoid ShaderStorageBlockBinding(GLuint program, GLuint storageBlockIndex, GLuint storageBlockBinding) const {
		gl.ShaderStorageBlockBinding(program, storageBlockIndex, storageBlockBinding);
		fprintf(GLMethodsDebugFile, "[%4d] ShaderStorageBlockBinding(%u, %u, %u)\n", gl.GetError(), program, storageBlockIndex, storageBlockBinding);
	}

	GLvoid TexBufferRange(GLenum target, GLenum internalformat, GLuint buffer, GLintptr offset, GLsizeiptr size) const {
		gl.TexBufferRange(target, internalformat, buffer, offset, size);
		fprintf(GLMethodsDebugFile, "[%4d] TexBufferRange(0x%x, 0x%x, %u, %" LL "d, %" LL "d)\n", gl.GetError(), target, internalformat, buffer, offset, size);
	}

	GLvoid TexStorage2DMultisample(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLboolean fixedsamplelocations) const {
		gl.TexStorage2DMultisample(target, samples, internalformat, width, height, fixedsamplelocations);
		fprintf(GLMethodsDebugFile, "[%4d] TexStorage2DMultisample(0x%x, %d, 0x%x, %d, %d, %d)\n", gl.GetError(), target, samples, internalformat, width, height, fixedsamplelocations);
	}

	GLvoid TexStorage3DMultisample(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLboolean fixedsamplelocations) const {
		gl.TexStorage3DMultisample(target, samples, internalformat, width, height, depth, fixedsamplelocations);
		fprintf(GLMethodsDebugFile, "[%4d] TexStorage3DMultisample(0x%x, %d, 0x%x, %d, %d, %d, %d)\n", gl.GetError(), target, samples, internalformat, width, height, depth, fixedsamplelocations);
	}

	GLvoid TextureView(GLuint texture, GLenum target, GLuint origtexture, GLenum internalformat, GLuint minlevel, GLuint numlevels, GLuint minlayer, GLuint numlayers) const {
		gl.TextureView(texture, target, origtexture, internalformat, minlevel, numlevels, minlayer, numlayers);
		fprintf(GLMethodsDebugFile, "[%4d] TextureView(%u, 0x%x, %u, 0x%x, %u, %u, %u, %u)\n", gl.GetError(), texture, target, origtexture, internalformat, minlevel, numlevels, minlayer, numlayers);
	}

	GLvoid BindVertexBuffer(GLuint bindingindex, GLuint buffer, GLintptr offset, GLsizei stride) const {
		gl.BindVertexBuffer(bindingindex, buffer, offset, stride);
		fprintf(GLMethodsDebugFile, "[%4d] BindVertexBuffer(%u, %u, %" LL "d, %d)\n", gl.GetError(), bindingindex, buffer, offset, stride);
	}

	GLvoid VertexAttribFormat(GLuint attribindex, GLint size, GLenum type, GLboolean normalized, GLuint relativeoffset) const {
		gl.VertexAttribFormat(attribindex, size, type, normalized, relativeoffset);
		fprintf(GLMethodsDebugFile, "[%4d] VertexAttribFormat(%u, %d, 0x%x, %d, %u)\n", gl.GetError(), attribindex, size, type, normalized, relativeoffset);
	}

	GLvoid VertexAttribIFormat(GLuint attribindex, GLint size, GLenum type, GLuint relativeoffset) const {
		gl.VertexAttribIFormat(attribindex, size, type, relativeoffset);
		fprintf(GLMethodsDebugFile, "[%4d] VertexAttribIFormat(%u, %d, 0x%x, %u)\n", gl.GetError(), attribindex, size, type, relativeoffset);
	}

	GLvoid VertexAttribLFormat(GLuint attribindex, GLint size, GLenum type, GLuint relativeoffset) const {
		gl.VertexAttribLFormat(attribindex, size, type, relativeoffset);
		fprintf(GLMethodsDebugFile, "[%4d] VertexAttribLFormat(%u, %d, 0x%x, %u)\n", gl.GetError(), attribindex, size, type, relativeoffset);
	}

	GLvoid VertexAttribBinding(GLuint attribindex, GLuint bindingindex) const {
		gl.VertexAttribBinding(attribindex, bindingindex);
		fprintf(GLMethodsDebugFile, "[%4d] VertexAttribBinding(%u, %u)\n", gl.GetError(), attribindex, bindingindex);
	}

	GLvoid VertexBindingDivisor(GLuint bindingindex, GLuint divisor) const {
		gl.VertexBindingDivisor(bindingindex, divisor);
		fprintf(GLMethodsDebugFile, "[%4d] VertexBindingDivisor(%u, %u)\n", gl.GetError(), bindingindex, divisor);
	}

	GLvoid DebugMessageControl(GLenum source, GLenum type, GLenum severity, GLsizei count, const GLuint * ids, GLboolean enabled) const {
		gl.DebugMessageControl(source, type, severity, count, ids, enabled);
		fprintf(GLMethodsDebugFile, "[%4d] DebugMessageControl(0x%x, 0x%x, 0x%x, %d, 0x%p, %d)\n", gl.GetError(), source, type, severity, count, ids, enabled);
	}

	GLvoid DebugMessageInsert(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar * buf) const {
		gl.DebugMessageInsert(source, type, id, severity, length, buf);
		fprintf(GLMethodsDebugFile, "[%4d] DebugMessageInsert(0x%x, 0x%x, %u, 0x%x, %d, 0x%p)\n", gl.GetError(), source, type, id, severity, length, buf);
	}

	GLvoid DebugMessageCallback(GLDEBUGPROC callback, const GLvoid * userParam) const {
		gl.DebugMessageCallback(callback, userParam);
		fprintf(GLMethodsDebugFile, "[%4d] DebugMessageCallback(0x%p, 0x%p)\n", gl.GetError(), callback, userParam);
	}

	GLuint GetDebugMessageLog(GLuint count, GLsizei bufSize, GLenum * sources, GLenum * types, GLuint * ids, GLenum * severities, GLsizei * lengths, GLchar * messageLog) const {
		GLuint res = gl.GetDebugMessageLog(count, bufSize, sources, types, ids, severities, lengths, messageLog);
		fprintf(GLMethodsDebugFile, "[%4d] GetDebugMessageLog(%u, %d, 0x%p, 0x%p, 0x%p, 0x%p, 0x%p, 0x%p) -> %u\n", gl.GetError(), count, bufSize, sources, types, ids, severities, lengths, messageLog, res);
		return res;
	}

	GLvoid PushDebugGroup(GLenum source, GLuint id, GLsizei length, const GLchar * message) const {
		gl.PushDebugGroup(source, id, length, message);
		fprintf(GLMethodsDebugFile, "[%4d] PushDebugGroup(0x%x, %u, %d, 0x%p)\n", gl.GetError(), source, id, length, message);
	}

	GLvoid PopDebugGroup() const {
		gl.PopDebugGroup();
		fprintf(GLMethodsDebugFile, "[%4d] PopDebugGroup()\n", gl.GetError());
	}

	GLvoid ObjectLabel(GLenum identifier, GLuint name, GLsizei length, const GLchar * label) const {
		gl.ObjectLabel(identifier, name, length, label);
		fprintf(GLMethodsDebugFile, "[%4d] ObjectLabel(0x%x, %u, %d, 0x%p)\n", gl.GetError(), identifier, name, length, label);
	}

	GLvoid GetObjectLabel(GLenum identifier, GLuint name, GLsizei bufSize, GLsizei * length, GLchar * label) const {
		gl.GetObjectLabel(identifier, name, bufSize, length, label);
		fprintf(GLMethodsDebugFile, "[%4d] GetObjectLabel(0x%x, %u, %d, 0x%p, 0x%p)\n", gl.GetError(), identifier, name, bufSize, length, label);
	}

	GLvoid ObjectPtrLabel(const GLvoid * ptr, GLsizei length, const GLchar * label) const {
		gl.ObjectPtrLabel(ptr, length, label);
		fprintf(GLMethodsDebugFile, "[%4d] ObjectPtrLabel( 0x%p, %d, 0x%p)\n", gl.GetError(), ptr, length, label);
	}

	GLvoid GetObjectPtrLabel(const GLvoid * ptr, GLsizei bufSize, GLsizei * length, GLchar * label) const {
		gl.GetObjectPtrLabel(ptr, bufSize, length, label);
		fprintf(GLMethodsDebugFile, "[%4d] GetObjectPtrLabel( 0x%p, %d, 0x%p, 0x%p)\n", gl.GetError(), ptr, bufSize, length, label);
	}

	GLvoid BufferStorage(GLenum target, GLsizeiptr size, const GLvoid * data, GLbitfield flags) const {
		gl.BufferStorage(target, size, data, flags);
		fprintf(GLMethodsDebugFile, "[%4d] BufferStorage(0x%x, %" LL "d, 0x%p, 0x%x)\n", gl.GetError(), target, size, data, flags);
	}

	GLvoid ClearTexImage(GLuint texture, GLint level, GLenum format, GLenum type, const GLvoid * data) const {
		gl.ClearTexImage(texture, level, format, type, data);
		fprintf(GLMethodsDebugFile, "[%4d] ClearTexImage(%u, %d, 0x%x, 0x%x, 0x%p)\n", gl.GetError(), texture, level, format, type, data);
	}

	GLvoid ClearTexSubImage(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const GLvoid * data) const {
		gl.ClearTexSubImage(texture, level, xoffset, yoffset, zoffset, width, height, depth, format, type, data);
		fprintf(GLMethodsDebugFile, "[%4d] ClearTexSubImage(%u, %d, %d, %d, %d, %d, %d, %d, 0x%x, 0x%x, 0x%p)\n", gl.GetError(), texture, level, xoffset, yoffset, zoffset, width, height, depth, format, type, data);
	}

	GLvoid BindBuffersBase(GLenum target, GLuint first, GLsizei count, const GLuint * buffers) const {
		gl.BindBuffersBase(target, first, count, buffers);
		fprintf(GLMethodsDebugFile, "[%4d] BindBuffersBase(0x%x, %u, %d, 0x%p)\n", gl.GetError(), target, first, count, buffers);
	}

	GLvoid BindBuffersRange(GLenum target, GLuint first, GLsizei count, const GLuint * buffers, const GLintptr * offsets, const GLsizeiptr * sizes) const {
		gl.BindBuffersRange(target, first, count, buffers, offsets, sizes);
		fprintf(GLMethodsDebugFile, "[%4d] BindBuffersRange(0x%x, %u, %d, 0x%p, 0x%p, 0x%p)\n", gl.GetError(), target, first, count, buffers, offsets, sizes);
	}

	GLvoid BindTextures(GLuint first, GLsizei count, const GLuint * textures) const {
		gl.BindTextures(first, count, textures);
		fprintf(GLMethodsDebugFile, "[%4d] BindTextures(%u, %d, 0x%p)\n", gl.GetError(), first, count, textures);
	}

	GLvoid BindSamplers(GLuint first, GLsizei count, const GLuint * samplers) const {
		gl.BindSamplers(first, count, samplers);
		fprintf(GLMethodsDebugFile, "[%4d] BindSamplers(%u, %d, 0x%p)\n", gl.GetError(), first, count, samplers);
	}

	GLvoid BindImageTextures(GLuint first, GLsizei count, const GLuint * textures) const {
		gl.BindImageTextures(first, count, textures);
		fprintf(GLMethodsDebugFile, "[%4d] BindImageTextures(%u, %d, 0x%p)\n", gl.GetError(), first, count, textures);
	}

	GLvoid BindVertexBuffers(GLuint first, GLsizei count, const GLuint * buffers, const GLintptr * offsets, const GLsizei * strides) const {
		gl.BindVertexBuffers(first, count, buffers, offsets, strides);
		fprintf(GLMethodsDebugFile, "[%4d] BindVertexBuffers(%u, %d, 0x%p, 0x%p, 0x%p)\n", gl.GetError(), first, count, buffers, offsets, strides);
	}

	GLvoid ClipControl(GLenum origin, GLenum depth) const {
		gl.ClipControl(origin, depth);
		fprintf(GLMethodsDebugFile, "[%4d] ClipControl(0x%x, 0x%x)\n", gl.GetError(), origin, depth);
	}

	GLvoid CreateTransformFeedbacks(GLsizei n, GLuint * ids) const {
		gl.CreateTransformFeedbacks(n, ids);
		fprintf(GLMethodsDebugFile, "[%4d] CreateTransformFeedbacks(%d, 0x%p)\n", gl.GetError(), n, ids);
	}

	GLvoid TransformFeedbackBufferBase(GLuint xfb, GLuint index, GLuint buffer) const {
		gl.TransformFeedbackBufferBase(xfb, index, buffer);
		fprintf(GLMethodsDebugFile, "[%4d] TransformFeedbackBufferBase(%u, %u, %u)\n", gl.GetError(), xfb, index, buffer);
	}

	GLvoid TransformFeedbackBufferRange(GLuint xfb, GLuint index, GLuint buffer, GLintptr offset, GLsizeiptr size) const {
		gl.TransformFeedbackBufferRange(xfb, index, buffer, offset, size);
		fprintf(GLMethodsDebugFile, "[%4d] TransformFeedbackBufferRange(%u, %u, %u, %" LL "d, %" LL "d)\n", gl.GetError(), xfb, index, buffer, offset, size);
	}

	GLvoid GetTransformFeedbackiv(GLuint xfb, GLenum pname, GLint * param) const {
		gl.GetTransformFeedbackiv(xfb, pname, param);
		fprintf(GLMethodsDebugFile, "[%4d] GetTransformFeedbackiv(%u, 0x%x, 0x%p)\n", gl.GetError(), xfb, pname, param);
	}

	GLvoid GetTransformFeedbacki_v(GLuint xfb, GLenum pname, GLuint index, GLint * param) const {
		gl.GetTransformFeedbacki_v(xfb, pname, index, param);
		fprintf(GLMethodsDebugFile, "[%4d] GetTransformFeedbacki_v(%u, 0x%x, %u, 0x%p)\n", gl.GetError(), xfb, pname, index, param);
	}

	GLvoid GetTransformFeedbacki64_v(GLuint xfb, GLenum pname, GLuint index, GLint64 * param) const {
		gl.GetTransformFeedbacki64_v(xfb, pname, index, param);
		fprintf(GLMethodsDebugFile, "[%4d] GetTransformFeedbacki64_v(%u, 0x%x, %u, 0x%p)\n", gl.GetError(), xfb, pname, index, param);
	}

	GLvoid CreateBuffers(GLsizei n, GLuint * buffers) const {
		gl.CreateBuffers(n, buffers);
		fprintf(GLMethodsDebugFile, "[%4d] CreateBuffers(%d, 0x%p)\n", gl.GetError(), n, buffers);
	}

	GLvoid NamedBufferStorage(GLuint buffer, GLsizeiptr size, const GLvoid * data, GLbitfield flags) const {
		gl.NamedBufferStorage(buffer, size, data, flags);
		fprintf(GLMethodsDebugFile, "[%4d] NamedBufferStorage(%u, %" LL "d, 0x%p, 0x%x)\n", gl.GetError(), buffer, size, data, flags);
	}

	GLvoid NamedBufferData(GLuint buffer, GLsizeiptr size, const GLvoid * data, GLenum usage) const {
		gl.NamedBufferData(buffer, size, data, usage);
		fprintf(GLMethodsDebugFile, "[%4d] NamedBufferData(%u, %" LL "d, 0x%p, 0x%x)\n", gl.GetError(), buffer, size, data, usage);
	}

	GLvoid NamedBufferSubData(GLuint buffer, GLintptr offset, GLsizeiptr size, const GLvoid * data) const {
		gl.NamedBufferSubData(buffer, offset, size, data);
		fprintf(GLMethodsDebugFile, "[%4d] NamedBufferSubData(%u, %" LL "d, %" LL "d, 0x%p)\n", gl.GetError(), buffer, offset, size, data);
	}

	GLvoid CopyNamedBufferSubData(GLuint readBuffer, GLuint writeBuffer, GLintptr readOffset, GLintptr writeOffset, GLsizeiptr size) const {
		gl.CopyNamedBufferSubData(readBuffer, writeBuffer, readOffset, writeOffset, size);
		fprintf(GLMethodsDebugFile, "[%4d] CopyNamedBufferSubData(%u, %u, %" LL "d, %" LL "d, %" LL "d)\n", gl.GetError(), readBuffer, writeBuffer, readOffset, writeOffset, size);
	}

	GLvoid ClearNamedBufferData(GLuint buffer, GLenum internalformat, GLenum format, GLenum type, const GLvoid * data) const {
		gl.ClearNamedBufferData(buffer, internalformat, format, type, data);
		fprintf(GLMethodsDebugFile, "[%4d] ClearNamedBufferData(%u, 0x%x, 0x%x, 0x%x, 0x%p)\n", gl.GetError(), buffer, internalformat, format, type, data);
	}

	GLvoid ClearNamedBufferSubData(GLuint buffer, GLenum internalformat, GLintptr offset, GLsizeiptr size, GLenum format, GLenum type, const GLvoid * data) const {
		gl.ClearNamedBufferSubData(buffer, internalformat, offset, size, format, type, data);
		fprintf(GLMethodsDebugFile, "[%4d] ClearNamedBufferSubData(%u, 0x%x, %" LL "d, %" LL "d, 0x%x, 0x%x, 0x%p)\n", gl.GetError(), buffer, internalformat, offset, size, format, type, data);
	}

	GLvoid * MapNamedBuffer(GLuint buffer, GLenum access) const {
		GLvoid * res = gl.MapNamedBuffer(buffer, access);
		fprintf(GLMethodsDebugFile, "[%4d] MapNamedBuffer(%u, 0x%x) -> 0x%p\n", gl.GetError(), buffer, access, res);
		return res;
	}

	GLvoid * MapNamedBufferRange(GLuint buffer, GLintptr offset, GLsizeiptr length, GLbitfield access) const {
		GLvoid * res = gl.MapNamedBufferRange(buffer, offset, length, access);
		fprintf(GLMethodsDebugFile, "[%4d] MapNamedBufferRange(%u, %" LL "d, %" LL "d, 0x%x) -> 0x%p\n", gl.GetError(), buffer, offset, length, access, res);
		return res;
	}

	GLboolean UnmapNamedBuffer(GLuint buffer) const {
		GLboolean res = gl.UnmapNamedBuffer(buffer);
		fprintf(GLMethodsDebugFile, "[%4d] UnmapNamedBuffer(%u) -> %d\n", gl.GetError(), buffer, res);
		return res;
	}

	GLvoid FlushMappedNamedBufferRange(GLuint buffer, GLintptr offset, GLsizeiptr length) const {
		gl.FlushMappedNamedBufferRange(buffer, offset, length);
		fprintf(GLMethodsDebugFile, "[%4d] FlushMappedNamedBufferRange(%u, %" LL "d, %" LL "d)\n", gl.GetError(), buffer, offset, length);
	}

	GLvoid GetNamedBufferParameteriv(GLuint buffer, GLenum pname, GLint * params) const {
		gl.GetNamedBufferParameteriv(buffer, pname, params);
		fprintf(GLMethodsDebugFile, "[%4d] GetNamedBufferParameteriv(%u, 0x%x, 0x%p)\n", gl.GetError(), buffer, pname, params);
	}

	GLvoid GetNamedBufferParameteri64v(GLuint buffer, GLenum pname, GLint64 * params) const {
		gl.GetNamedBufferParameteri64v(buffer, pname, params);
		fprintf(GLMethodsDebugFile, "[%4d] GetNamedBufferParameteri64v(%u, 0x%x, 0x%p)\n", gl.GetError(), buffer, pname, params);
	}

	GLvoid GetNamedBufferPointerv(GLuint buffer, GLenum pname, GLvoid ** params) const {
		gl.GetNamedBufferPointerv(buffer, pname, params);
		fprintf(GLMethodsDebugFile, "[%4d] GetNamedBufferPointerv(%u, 0x%x, 0x%p)\n", gl.GetError(), buffer, pname, params);
	}

	GLvoid GetNamedBufferSubData(GLuint buffer, GLintptr offset, GLsizeiptr size, GLvoid * data) const {
		gl.GetNamedBufferSubData(buffer, offset, size, data);
		fprintf(GLMethodsDebugFile, "[%4d] GetNamedBufferSubData(%u, %" LL "d, %" LL "d, 0x%p)\n", gl.GetError(), buffer, offset, size, data);
	}

	GLvoid CreateFramebuffers(GLsizei n, GLuint * framebuffers) const {
		gl.CreateFramebuffers(n, framebuffers);
		fprintf(GLMethodsDebugFile, "[%4d] CreateFramebuffers(%d, 0x%p)\n", gl.GetError(), n, framebuffers);
	}

	GLvoid NamedFramebufferRenderbuffer(GLuint framebuffer, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer) const {
		gl.NamedFramebufferRenderbuffer(framebuffer, attachment, renderbuffertarget, renderbuffer);
		fprintf(GLMethodsDebugFile, "[%4d] NamedFramebufferRenderbuffer(%u, 0x%x, 0x%x, %u)\n", gl.GetError(), framebuffer, attachment, renderbuffertarget, renderbuffer);
	}

	GLvoid NamedFramebufferParameteri(GLuint framebuffer, GLenum pname, GLint param) const {
		gl.NamedFramebufferParameteri(framebuffer, pname, param);
		fprintf(GLMethodsDebugFile, "[%4d] NamedFramebufferParameteri(%u, 0x%x, %d)\n", gl.GetError(), framebuffer, pname, param);
	}

	GLvoid NamedFramebufferTexture(GLuint framebuffer, GLenum attachment, GLuint texture, GLint level) const {
		gl.NamedFramebufferTexture(framebuffer, attachment, texture, level);
		fprintf(GLMethodsDebugFile, "[%4d] NamedFramebufferTexture(%u, 0x%x, %u, %d)\n", gl.GetError(), framebuffer, attachment, texture, level);
	}

	GLvoid NamedFramebufferTextureLayer(GLuint framebuffer, GLenum attachment, GLuint texture, GLint level, GLint layer) const {
		gl.NamedFramebufferTextureLayer(framebuffer, attachment, texture, level, layer);
		fprintf(GLMethodsDebugFile, "[%4d] NamedFramebufferTextureLayer(%u, 0x%x, %u, %d, %d)\n", gl.GetError(), framebuffer, attachment, texture, level, layer);
	}

	GLvoid NamedFramebufferDrawBuffer(GLuint framebuffer, GLenum buf) const {
		gl.NamedFramebufferDrawBuffer(framebuffer, buf);
		fprintf(GLMethodsDebugFile, "[%4d] NamedFramebufferDrawBuffer(%u, 0x%x)\n", gl.GetError(), framebuffer, buf);
	}

	GLvoid NamedFramebufferDrawBuffers(GLuint framebuffer, GLsizei n, const GLenum * bufs) const {
		gl.NamedFramebufferDrawBuffers(framebuffer, n, bufs);
		fprintf(GLMethodsDebugFile, "[%4d] NamedFramebufferDrawBuffers(%u, %d, 0x%p)\n", gl.GetError(), framebuffer, n, bufs);
	}

	GLvoid NamedFramebufferReadBuffer(GLuint framebuffer, GLenum src) const {
		gl.NamedFramebufferReadBuffer(framebuffer, src);
		fprintf(GLMethodsDebugFile, "[%4d] NamedFramebufferReadBuffer(%u, 0x%x)\n", gl.GetError(), framebuffer, src);
	}

	GLvoid InvalidateNamedFramebufferData(GLuint framebuffer, GLsizei numAttachments, const GLenum * attachments) const {
		gl.InvalidateNamedFramebufferData(framebuffer, numAttachments, attachments);
		fprintf(GLMethodsDebugFile, "[%4d] InvalidateNamedFramebufferData(%u, %d, 0x%p)\n", gl.GetError(), framebuffer, numAttachments, attachments);
	}

	GLvoid InvalidateNamedFramebufferSubData(GLuint framebuffer, GLsizei numAttachments, const GLenum * attachments, GLint x, GLint y, GLsizei width, GLsizei height) const {
		gl.InvalidateNamedFramebufferSubData(framebuffer, numAttachments, attachments, x, y, width, height);
		fprintf(GLMethodsDebugFile, "[%4d] InvalidateNamedFramebufferSubData(%u, %d, 0x%p, %d, %d, %d, %d)\n", gl.GetError(), framebuffer, numAttachments, attachments, x, y, width, height);
	}

	GLvoid ClearNamedFramebufferiv(GLuint framebuffer, GLenum buffer, GLint drawbuffer, const GLint * value) const {
		gl.ClearNamedFramebufferiv(framebuffer, buffer, drawbuffer, value);
		fprintf(GLMethodsDebugFile, "[%4d] ClearNamedFramebufferiv(%u, 0x%x, %d, 0x%p)\n", gl.GetError(), framebuffer, buffer, drawbuffer, value);
	}

	GLvoid ClearNamedFramebufferuiv(GLuint framebuffer, GLenum buffer, GLint drawbuffer, const GLuint * value) const {
		gl.ClearNamedFramebufferuiv(framebuffer, buffer, drawbuffer, value);
		fprintf(GLMethodsDebugFile, "[%4d] ClearNamedFramebufferuiv(%u, 0x%x, %d, 0x%p)\n", gl.GetError(), framebuffer, buffer, drawbuffer, value);
	}

	GLvoid ClearNamedFramebufferfv(GLuint framebuffer, GLenum buffer, GLint drawbuffer, const GLfloat * value) const {
		gl.ClearNamedFramebufferfv(framebuffer, buffer, drawbuffer, value);
		fprintf(GLMethodsDebugFile, "[%4d] ClearNamedFramebufferfv(%u, 0x%x, %d, 0x%p)\n", gl.GetError(), framebuffer, buffer, drawbuffer, value);
	}

	GLvoid ClearNamedFramebufferfi(GLuint framebuffer, GLenum buffer, GLint drawbuffer, GLfloat depth, GLint stencil) const {
		gl.ClearNamedFramebufferfi(framebuffer, buffer, drawbuffer, depth, stencil);
		fprintf(GLMethodsDebugFile, "[%4d] ClearNamedFramebufferfi(%u, 0x%x, %d, %f, %d)\n", gl.GetError(), framebuffer, buffer, drawbuffer, depth, stencil);
	}

	GLvoid BlitNamedFramebuffer(GLuint readFramebuffer, GLuint drawFramebuffer, GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield mask, GLenum filter) const {
		gl.BlitNamedFramebuffer(readFramebuffer, drawFramebuffer, srcX0, srcY0, srcX1, srcY1, dstX0, dstY0, dstX1, dstY1, mask, filter);
		fprintf(GLMethodsDebugFile, "[%4d] BlitNamedFramebuffer(%u, %u, %d, %d, %d, %d, %d, %d, %d, %d, 0x%x, 0x%x)\n", gl.GetError(), readFramebuffer, drawFramebuffer, srcX0, srcY0, srcX1, srcY1, dstX0, dstY0, dstX1, dstY1, mask, filter);
	}

	GLenum CheckNamedFramebufferStatus(GLuint framebuffer, GLenum target) const {
		GLenum res = gl.CheckNamedFramebufferStatus(framebuffer, target);
		fprintf(GLMethodsDebugFile, "[%4d] CheckNamedFramebufferStatus(%u, 0x%x) -> 0x%x\n", gl.GetError(), framebuffer, target, res);
		return res;
	}

	GLvoid GetNamedFramebufferParameteriv(GLuint framebuffer, GLenum pname, GLint * param) const {
		gl.GetNamedFramebufferParameteriv(framebuffer, pname, param);
		fprintf(GLMethodsDebugFile, "[%4d] GetNamedFramebufferParameteriv(%u, 0x%x, 0x%p)\n", gl.GetError(), framebuffer, pname, param);
	}

	GLvoid GetNamedFramebufferAttachmentParameteriv(GLuint framebuffer, GLenum attachment, GLenum pname, GLint * params) const {
		gl.GetNamedFramebufferAttachmentParameteriv(framebuffer, attachment, pname, params);
		fprintf(GLMethodsDebugFile, "[%4d] GetNamedFramebufferAttachmentParameteriv(%u, 0x%x, 0x%x, 0x%p)\n", gl.GetError(), framebuffer, attachment, pname, params);
	}

	GLvoid CreateRenderbuffers(GLsizei n, GLuint * renderbuffers) const {
		gl.CreateRenderbuffers(n, renderbuffers);
		fprintf(GLMethodsDebugFile, "[%4d] CreateRenderbuffers(%d, 0x%p)\n", gl.GetError(), n, renderbuffers);
	}

	GLvoid NamedRenderbufferStorage(GLuint renderbuffer, GLenum internalformat, GLsizei width, GLsizei height) const {
		gl.NamedRenderbufferStorage(renderbuffer, internalformat, width, height);
		fprintf(GLMethodsDebugFile, "[%4d] NamedRenderbufferStorage(%u, 0x%x, %d, %d)\n", gl.GetError(), renderbuffer, internalformat, width, height);
	}

	GLvoid NamedRenderbufferStorageMultisample(GLuint renderbuffer, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height) const {
		gl.NamedRenderbufferStorageMultisample(renderbuffer, samples, internalformat, width, height);
		fprintf(GLMethodsDebugFile, "[%4d] NamedRenderbufferStorageMultisample(%u, %d, 0x%x, %d, %d)\n", gl.GetError(), renderbuffer, samples, internalformat, width, height);
	}

	GLvoid GetNamedRenderbufferParameteriv(GLuint renderbuffer, GLenum pname, GLint * params) const {
		gl.GetNamedRenderbufferParameteriv(renderbuffer, pname, params);
		fprintf(GLMethodsDebugFile, "[%4d] GetNamedRenderbufferParameteriv(%u, 0x%x, 0x%p)\n", gl.GetError(), renderbuffer, pname, params);
	}

	GLvoid CreateTextures(GLenum target, GLsizei n, GLuint * textures) const {
		gl.CreateTextures(target, n, textures);
		fprintf(GLMethodsDebugFile, "[%4d] CreateTextures(0x%x, %d, 0x%p)\n", gl.GetError(), target, n, textures);
	}

	GLvoid TextureBuffer(GLuint texture, GLenum internalformat, GLuint buffer) const {
		gl.TextureBuffer(texture, internalformat, buffer);
		fprintf(GLMethodsDebugFile, "[%4d] TextureBuffer(%u, 0x%x, %u)\n", gl.GetError(), texture, internalformat, buffer);
	}

	GLvoid TextureBufferRange(GLuint texture, GLenum internalformat, GLuint buffer, GLintptr offset, GLsizeiptr size) const {
		gl.TextureBufferRange(texture, internalformat, buffer, offset, size);
		fprintf(GLMethodsDebugFile, "[%4d] TextureBufferRange(%u, 0x%x, %u, %" LL "d, %" LL "d)\n", gl.GetError(), texture, internalformat, buffer, offset, size);
	}

	GLvoid TextureStorage1D(GLuint texture, GLsizei levels, GLenum internalformat, GLsizei width) const {
		gl.TextureStorage1D(texture, levels, internalformat, width);
		fprintf(GLMethodsDebugFile, "[%4d] TextureStorage1D(%u, %d, 0x%x, %d)\n", gl.GetError(), texture, levels, internalformat, width);
	}

	GLvoid TextureStorage2D(GLuint texture, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height) const {
		gl.TextureStorage2D(texture, levels, internalformat, width, height);
		fprintf(GLMethodsDebugFile, "[%4d] TextureStorage2D(%u, %d, 0x%x, %d, %d)\n", gl.GetError(), texture, levels, internalformat, width, height);
	}

	GLvoid TextureStorage3D(GLuint texture, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth) const {
		gl.TextureStorage3D(texture, levels, internalformat, width, height, depth);
		fprintf(GLMethodsDebugFile, "[%4d] TextureStorage3D(%u, %d, 0x%x, %d, %d, %d)\n", gl.GetError(), texture, levels, internalformat, width, height, depth);
	}

	GLvoid TextureStorage2DMultisample(GLuint texture, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLboolean fixedsamplelocations) const {
		gl.TextureStorage2DMultisample(texture, samples, internalformat, width, height, fixedsamplelocations);
		fprintf(GLMethodsDebugFile, "[%4d] TextureStorage2DMultisample(%u, %d, 0x%x, %d, %d, %d)\n", gl.GetError(), texture, samples, internalformat, width, height, fixedsamplelocations);
	}

	GLvoid TextureStorage3DMultisample(GLuint texture, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLboolean fixedsamplelocations) const {
		gl.TextureStorage3DMultisample(texture, samples, internalformat, width, height, depth, fixedsamplelocations);
		fprintf(GLMethodsDebugFile, "[%4d] TextureStorage3DMultisample(%u, %d, 0x%x, %d, %d, %d, %d)\n", gl.GetError(), texture, samples, internalformat, width, height, depth, fixedsamplelocations);
	}

	GLvoid TextureSubImage1D(GLuint texture, GLint level, GLint xoffset, GLsizei width, GLenum format, GLenum type, const GLvoid * pixels) const {
		gl.TextureSubImage1D(texture, level, xoffset, width, format, type, pixels);
		fprintf(GLMethodsDebugFile, "[%4d] TextureSubImage1D(%u, %d, %d, %d, 0x%x, 0x%x, 0x%p)\n", gl.GetError(), texture, level, xoffset, width, format, type, pixels);
	}

	GLvoid TextureSubImage2D(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid * pixels) const {
		gl.TextureSubImage2D(texture, level, xoffset, yoffset, width, height, format, type, pixels);
		fprintf(GLMethodsDebugFile, "[%4d] TextureSubImage2D(%u, %d, %d, %d, %d, %d, 0x%x, 0x%x, 0x%p)\n", gl.GetError(), texture, level, xoffset, yoffset, width, height, format, type, pixels);
	}

	GLvoid TextureSubImage3D(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const GLvoid * pixels) const {
		gl.TextureSubImage3D(texture, level, xoffset, yoffset, zoffset, width, height, depth, format, type, pixels);
		fprintf(GLMethodsDebugFile, "[%4d] TextureSubImage3D(%u, %d, %d, %d, %d, %d, %d, %d, 0x%x, 0x%x, 0x%p)\n", gl.GetError(), texture, level, xoffset, yoffset, zoffset, width, height, depth, format, type, pixels);
	}

	GLvoid CompressedTextureSubImage1D(GLuint texture, GLint level, GLint xoffset, GLsizei width, GLenum format, GLsizei imageSize, const GLvoid * data) const {
		gl.CompressedTextureSubImage1D(texture, level, xoffset, width, format, imageSize, data);
		fprintf(GLMethodsDebugFile, "[%4d] CompressedTextureSubImage1D(%u, %d, %d, %d, 0x%x, %d, 0x%p)\n", gl.GetError(), texture, level, xoffset, width, format, imageSize, data);
	}

	GLvoid CompressedTextureSubImage2D(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const GLvoid * data) const {
		gl.CompressedTextureSubImage2D(texture, level, xoffset, yoffset, width, height, format, imageSize, data);
		fprintf(GLMethodsDebugFile, "[%4d] CompressedTextureSubImage2D(%u, %d, %d, %d, %d, %d, 0x%x, %d, 0x%p)\n", gl.GetError(), texture, level, xoffset, yoffset, width, height, format, imageSize, data);
	}

	GLvoid CompressedTextureSubImage3D(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLsizei imageSize, const GLvoid * data) const {
		gl.CompressedTextureSubImage3D(texture, level, xoffset, yoffset, zoffset, width, height, depth, format, imageSize, data);
		fprintf(GLMethodsDebugFile, "[%4d] CompressedTextureSubImage3D(%u, %d, %d, %d, %d, %d, %d, %d, 0x%x, %d, 0x%p)\n", gl.GetError(), texture, level, xoffset, yoffset, zoffset, width, height, depth, format, imageSize, data);
	}

	GLvoid CopyTextureSubImage1D(GLuint texture, GLint level, GLint xoffset, GLint x, GLint y, GLsizei width) const {
		gl.CopyTextureSubImage1D(texture, level, xoffset, x, y, width);
		fprintf(GLMethodsDebugFile, "[%4d] CopyTextureSubImage1D(%u, %d, %d, %d, %d, %d)\n", gl.GetError(), texture, level, xoffset, x, y, width);
	}

	GLvoid CopyTextureSubImage2D(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height) const {
		gl.CopyTextureSubImage2D(texture, level, xoffset, yoffset, x, y, width, height);
		fprintf(GLMethodsDebugFile, "[%4d] CopyTextureSubImage2D(%u, %d, %d, %d, %d, %d, %d, %d)\n", gl.GetError(), texture, level, xoffset, yoffset, x, y, width, height);
	}

	GLvoid CopyTextureSubImage3D(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLint x, GLint y, GLsizei width, GLsizei height) const {
		gl.CopyTextureSubImage3D(texture, level, xoffset, yoffset, zoffset, x, y, width, height);
		fprintf(GLMethodsDebugFile, "[%4d] CopyTextureSubImage3D(%u, %d, %d, %d, %d, %d, %d, %d, %d)\n", gl.GetError(), texture, level, xoffset, yoffset, zoffset, x, y, width, height);
	}

	GLvoid TextureParameterf(GLuint texture, GLenum pname, GLfloat param) const {
		gl.TextureParameterf(texture, pname, param);
		fprintf(GLMethodsDebugFile, "[%4d] TextureParameterf(%u, 0x%x, %f)\n", gl.GetError(), texture, pname, param);
	}

	GLvoid TextureParameterfv(GLuint texture, GLenum pname, const GLfloat * param) const {
		gl.TextureParameterfv(texture, pname, param);
		fprintf(GLMethodsDebugFile, "[%4d] TextureParameterfv(%u, 0x%x, 0x%p)\n", gl.GetError(), texture, pname, param);
	}

	GLvoid TextureParameteri(GLuint texture, GLenum pname, GLint param) const {
		gl.TextureParameteri(texture, pname, param);
		fprintf(GLMethodsDebugFile, "[%4d] TextureParameteri(%u, 0x%x, %d)\n", gl.GetError(), texture, pname, param);
	}

	GLvoid TextureParameterIiv(GLuint texture, GLenum pname, const GLint * params) const {
		gl.TextureParameterIiv(texture, pname, params);
		fprintf(GLMethodsDebugFile, "[%4d] TextureParameterIiv(%u, 0x%x, 0x%p)\n", gl.GetError(), texture, pname, params);
	}

	GLvoid TextureParameterIuiv(GLuint texture, GLenum pname, const GLuint * params) const {
		gl.TextureParameterIuiv(texture, pname, params);
		fprintf(GLMethodsDebugFile, "[%4d] TextureParameterIuiv(%u, 0x%x, 0x%p)\n", gl.GetError(), texture, pname, params);
	}

	GLvoid TextureParameteriv(GLuint texture, GLenum pname, const GLint * param) const {
		gl.TextureParameteriv(texture, pname, param);
		fprintf(GLMethodsDebugFile, "[%4d] TextureParameteriv(%u, 0x%x, 0x%p)\n", gl.GetError(), texture, pname, param);
	}

	GLvoid GenerateTextureMipmap(GLuint texture) const {
		gl.GenerateTextureMipmap(texture);
		fprintf(GLMethodsDebugFile, "[%4d] GenerateTextureMipmap(%u)\n", gl.GetError(), texture);
	}

	GLvoid BindTextureUnit(GLuint unit, GLuint texture) const {
		gl.BindTextureUnit(unit, texture);
		fprintf(GLMethodsDebugFile, "[%4d] BindTextureUnit(%u, %u)\n", gl.GetError(), unit, texture);
	}

	GLvoid GetTextureImage(GLuint texture, GLint level, GLenum format, GLenum type, GLsizei bufSize, GLvoid * pixels) const {
		gl.GetTextureImage(texture, level, format, type, bufSize, pixels);
		fprintf(GLMethodsDebugFile, "[%4d] GetTextureImage(%u, %d, 0x%x, 0x%x, %d, 0x%p)\n", gl.GetError(), texture, level, format, type, bufSize, pixels);
	}

	GLvoid GetCompressedTextureImage(GLuint texture, GLint level, GLsizei bufSize, GLvoid * pixels) const {
		gl.GetCompressedTextureImage(texture, level, bufSize, pixels);
		fprintf(GLMethodsDebugFile, "[%4d] GetCompressedTextureImage(%u, %d, %d, 0x%p)\n", gl.GetError(), texture, level, bufSize, pixels);
	}

	GLvoid GetTextureLevelParameterfv(GLuint texture, GLint level, GLenum pname, GLfloat * params) const {
		gl.GetTextureLevelParameterfv(texture, level, pname, params);
		fprintf(GLMethodsDebugFile, "[%4d] GetTextureLevelParameterfv(%u, %d, 0x%x, 0x%p)\n", gl.GetError(), texture, level, pname, params);
	}

	GLvoid GetTextureLevelParameteriv(GLuint texture, GLint level, GLenum pname, GLint * params) const {
		gl.GetTextureLevelParameteriv(texture, level, pname, params);
		fprintf(GLMethodsDebugFile, "[%4d] GetTextureLevelParameteriv(%u, %d, 0x%x, 0x%p)\n", gl.GetError(), texture, level, pname, params);
	}

	GLvoid GetTextureParameterfv(GLuint texture, GLenum pname, GLfloat * params) const {
		gl.GetTextureParameterfv(texture, pname, params);
		fprintf(GLMethodsDebugFile, "[%4d] GetTextureParameterfv(%u, 0x%x, 0x%p)\n", gl.GetError(), texture, pname, params);
	}

	GLvoid GetTextureParameterIiv(GLuint texture, GLenum pname, GLint * params) const {
		gl.GetTextureParameterIiv(texture, pname, params);
		fprintf(GLMethodsDebugFile, "[%4d] GetTextureParameterIiv(%u, 0x%x, 0x%p)\n", gl.GetError(), texture, pname, params);
	}

	GLvoid GetTextureParameterIuiv(GLuint texture, GLenum pname, GLuint * params) const {
		gl.GetTextureParameterIuiv(texture, pname, params);
		fprintf(GLMethodsDebugFile, "[%4d] GetTextureParameterIuiv(%u, 0x%x, 0x%p)\n", gl.GetError(), texture, pname, params);
	}

	GLvoid GetTextureParameteriv(GLuint texture, GLenum pname, GLint * params) const {
		gl.GetTextureParameteriv(texture, pname, params);
		fprintf(GLMethodsDebugFile, "[%4d] GetTextureParameteriv(%u, 0x%x, 0x%p)\n", gl.GetError(), texture, pname, params);
	}

	GLvoid CreateVertexArrays(GLsizei n, GLuint * arrays) const {
		gl.CreateVertexArrays(n, arrays);
		fprintf(GLMethodsDebugFile, "[%4d] CreateVertexArrays(%d, 0x%p)\n", gl.GetError(), n, arrays);
	}

	GLvoid DisableVertexArrayAttrib(GLuint vaobj, GLuint index) const {
		gl.DisableVertexArrayAttrib(vaobj, index);
		fprintf(GLMethodsDebugFile, "[%4d] DisableVertexArrayAttrib(%u, %u)\n", gl.GetError(), vaobj, index);
	}

	GLvoid EnableVertexArrayAttrib(GLuint vaobj, GLuint index) const {
		gl.EnableVertexArrayAttrib(vaobj, index);
		fprintf(GLMethodsDebugFile, "[%4d] EnableVertexArrayAttrib(%u, %u)\n", gl.GetError(), vaobj, index);
	}

	GLvoid VertexArrayElementBuffer(GLuint vaobj, GLuint buffer) const {
		gl.VertexArrayElementBuffer(vaobj, buffer);
		fprintf(GLMethodsDebugFile, "[%4d] VertexArrayElementBuffer(%u, %u)\n", gl.GetError(), vaobj, buffer);
	}

	GLvoid VertexArrayVertexBuffer(GLuint vaobj, GLuint bindingindex, GLuint buffer, GLintptr offset, GLsizei stride) const {
		gl.VertexArrayVertexBuffer(vaobj, bindingindex, buffer, offset, stride);
		fprintf(GLMethodsDebugFile, "[%4d] VertexArrayVertexBuffer(%u, %u, %u, %" LL "d, %d)\n", gl.GetError(), vaobj, bindingindex, buffer, offset, stride);
	}

	GLvoid VertexArrayVertexBuffers(GLuint vaobj, GLuint first, GLsizei count, const GLuint * buffers, const GLintptr * offsets, const GLsizei * strides) const {
		gl.VertexArrayVertexBuffers(vaobj, first, count, buffers, offsets, strides);
		fprintf(GLMethodsDebugFile, "[%4d] VertexArrayVertexBuffers(%u, %u, %d, 0x%p, 0x%p, 0x%p)\n", gl.GetError(), vaobj, first, count, buffers, offsets, strides);
	}

	GLvoid VertexArrayAttribBinding(GLuint vaobj, GLuint attribindex, GLuint bindingindex) const {
		gl.VertexArrayAttribBinding(vaobj, attribindex, bindingindex);
		fprintf(GLMethodsDebugFile, "[%4d] VertexArrayAttribBinding(%u, %u, %u)\n", gl.GetError(), vaobj, attribindex, bindingindex);
	}

	GLvoid VertexArrayAttribFormat(GLuint vaobj, GLuint attribindex, GLint size, GLenum type, GLboolean normalized, GLuint relativeoffset) const {
		gl.VertexArrayAttribFormat(vaobj, attribindex, size, type, normalized, relativeoffset);
		fprintf(GLMethodsDebugFile, "[%4d] VertexArrayAttribFormat(%u, %u, %d, 0x%x, %d, %u)\n", gl.GetError(), vaobj, attribindex, size, type, normalized, relativeoffset);
	}

	GLvoid VertexArrayAttribIFormat(GLuint vaobj, GLuint attribindex, GLint size, GLenum type, GLuint relativeoffset) const {
		gl.VertexArrayAttribIFormat(vaobj, attribindex, size, type, relativeoffset);
		fprintf(GLMethodsDebugFile, "[%4d] VertexArrayAttribIFormat(%u, %u, %d, 0x%x, %u)\n", gl.GetError(), vaobj, attribindex, size, type, relativeoffset);
	}

	GLvoid VertexArrayAttribLFormat(GLuint vaobj, GLuint attribindex, GLint size, GLenum type, GLuint relativeoffset) const {
		gl.VertexArrayAttribLFormat(vaobj, attribindex, size, type, relativeoffset);
		fprintf(GLMethodsDebugFile, "[%4d] VertexArrayAttribLFormat(%u, %u, %d, 0x%x, %u)\n", gl.GetError(), vaobj, attribindex, size, type, relativeoffset);
	}

	GLvoid VertexArrayBindingDivisor(GLuint vaobj, GLuint bindingindex, GLuint divisor) const {
		gl.VertexArrayBindingDivisor(vaobj, bindingindex, divisor);
		fprintf(GLMethodsDebugFile, "[%4d] VertexArrayBindingDivisor(%u, %u, %u)\n", gl.GetError(), vaobj, bindingindex, divisor);
	}

	GLvoid GetVertexArrayiv(GLuint vaobj, GLenum pname, GLint * param) const {
		gl.GetVertexArrayiv(vaobj, pname, param);
		fprintf(GLMethodsDebugFile, "[%4d] GetVertexArrayiv(%u, 0x%x, 0x%p)\n", gl.GetError(), vaobj, pname, param);
	}

	GLvoid GetVertexArrayIndexediv(GLuint vaobj, GLuint index, GLenum pname, GLint * param) const {
		gl.GetVertexArrayIndexediv(vaobj, index, pname, param);
		fprintf(GLMethodsDebugFile, "[%4d] GetVertexArrayIndexediv(%u, %u, 0x%x, 0x%p)\n", gl.GetError(), vaobj, index, pname, param);
	}

	GLvoid GetVertexArrayIndexed64iv(GLuint vaobj, GLuint index, GLenum pname, GLint64 * param) const {
		gl.GetVertexArrayIndexed64iv(vaobj, index, pname, param);
		fprintf(GLMethodsDebugFile, "[%4d] GetVertexArrayIndexed64iv(%u, %u, 0x%x, 0x%p)\n", gl.GetError(), vaobj, index, pname, param);
	}

	GLvoid CreateSamplers(GLsizei n, GLuint * samplers) const {
		gl.CreateSamplers(n, samplers);
		fprintf(GLMethodsDebugFile, "[%4d] CreateSamplers(%d, 0x%p)\n", gl.GetError(), n, samplers);
	}

	GLvoid CreateProgramPipelines(GLsizei n, GLuint * pipelines) const {
		gl.CreateProgramPipelines(n, pipelines);
		fprintf(GLMethodsDebugFile, "[%4d] CreateProgramPipelines(%d, 0x%p)\n", gl.GetError(), n, pipelines);
	}

	GLvoid CreateQueries(GLenum target, GLsizei n, GLuint * ids) const {
		gl.CreateQueries(target, n, ids);
		fprintf(GLMethodsDebugFile, "[%4d] CreateQueries(0x%x, %d, 0x%p)\n", gl.GetError(), target, n, ids);
	}

	GLvoid GetQueryBufferObjecti64v(GLuint id, GLuint buffer, GLenum pname, GLintptr offset) const {
		gl.GetQueryBufferObjecti64v(id, buffer, pname, offset);
		fprintf(GLMethodsDebugFile, "[%4d] GetQueryBufferObjecti64v(%u, %u, 0x%x, %" LL "d)\n", gl.GetError(), id, buffer, pname, offset);
	}

	GLvoid GetQueryBufferObjectiv(GLuint id, GLuint buffer, GLenum pname, GLintptr offset) const {
		gl.GetQueryBufferObjectiv(id, buffer, pname, offset);
		fprintf(GLMethodsDebugFile, "[%4d] GetQueryBufferObjectiv(%u, %u, 0x%x, %" LL "d)\n", gl.GetError(), id, buffer, pname, offset);
	}

	GLvoid GetQueryBufferObjectui64v(GLuint id, GLuint buffer, GLenum pname, GLintptr offset) const {
		gl.GetQueryBufferObjectui64v(id, buffer, pname, offset);
		fprintf(GLMethodsDebugFile, "[%4d] GetQueryBufferObjectui64v(%u, %u, 0x%x, %" LL "d)\n", gl.GetError(), id, buffer, pname, offset);
	}

	GLvoid GetQueryBufferObjectuiv(GLuint id, GLuint buffer, GLenum pname, GLintptr offset) const {
		gl.GetQueryBufferObjectuiv(id, buffer, pname, offset);
		fprintf(GLMethodsDebugFile, "[%4d] GetQueryBufferObjectuiv(%u, %u, 0x%x, %" LL "d)\n", gl.GetError(), id, buffer, pname, offset);
	}

	GLvoid MemoryBarrierByRegion(GLbitfield barriers) const {
		gl.MemoryBarrierByRegion(barriers);
		fprintf(GLMethodsDebugFile, "[%4d] MemoryBarrierByRegion(0x%x)\n", gl.GetError(), barriers);
	}

	GLvoid GetTextureSubImage(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, GLsizei bufSize, GLvoid * pixels) const {
		gl.GetTextureSubImage(texture, level, xoffset, yoffset, zoffset, width, height, depth, format, type, bufSize, pixels);
		fprintf(GLMethodsDebugFile, "[%4d] GetTextureSubImage(%u, %d, %d, %d, %d, %d, %d, %d, 0x%x, 0x%x, %d, 0x%p)\n", gl.GetError(), texture, level, xoffset, yoffset, zoffset, width, height, depth, format, type, bufSize, pixels);
	}

	GLvoid GetCompressedTextureSubImage(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLsizei bufSize, GLvoid * pixels) const {
		gl.GetCompressedTextureSubImage(texture, level, xoffset, yoffset, zoffset, width, height, depth, bufSize, pixels);
		fprintf(GLMethodsDebugFile, "[%4d] GetCompressedTextureSubImage(%u, %d, %d, %d, %d, %d, %d, %d, %d, 0x%p)\n", gl.GetError(), texture, level, xoffset, yoffset, zoffset, width, height, depth, bufSize, pixels);
	}

	GLenum GetGraphicsResetStatus() const {
		GLenum res = gl.GetGraphicsResetStatus();
		fprintf(GLMethodsDebugFile, "[%4d] GetGraphicsResetStatus() -> 0x%x\n", gl.GetError(), res);
		return res;
	}

	GLvoid GetnCompressedTexImage(GLenum target, GLint lod, GLsizei bufSize, GLvoid * pixels) const {
		gl.GetnCompressedTexImage(target, lod, bufSize, pixels);
		fprintf(GLMethodsDebugFile, "[%4d] GetnCompressedTexImage(0x%x, %d, %d, 0x%p)\n", gl.GetError(), target, lod, bufSize, pixels);
	}

	GLvoid GetnTexImage(GLenum target, GLint level, GLenum format, GLenum type, GLsizei bufSize, GLvoid * pixels) const {
		gl.GetnTexImage(target, level, format, type, bufSize, pixels);
		fprintf(GLMethodsDebugFile, "[%4d] GetnTexImage(0x%x, %d, 0x%x, 0x%x, %d, 0x%p)\n", gl.GetError(), target, level, format, type, bufSize, pixels);
	}

	GLvoid GetnUniformdv(GLuint program, GLint location, GLsizei bufSize, GLdouble * params) const {
		gl.GetnUniformdv(program, location, bufSize, params);
		fprintf(GLMethodsDebugFile, "[%4d] GetnUniformdv(%u, %d, %d, 0x%p)\n", gl.GetError(), program, location, bufSize, params);
	}

	GLvoid GetnUniformfv(GLuint program, GLint location, GLsizei bufSize, GLfloat * params) const {
		gl.GetnUniformfv(program, location, bufSize, params);
		fprintf(GLMethodsDebugFile, "[%4d] GetnUniformfv(%u, %d, %d, 0x%p)\n", gl.GetError(), program, location, bufSize, params);
	}

	GLvoid GetnUniformiv(GLuint program, GLint location, GLsizei bufSize, GLint * params) const {
		gl.GetnUniformiv(program, location, bufSize, params);
		fprintf(GLMethodsDebugFile, "[%4d] GetnUniformiv(%u, %d, %d, 0x%p)\n", gl.GetError(), program, location, bufSize, params);
	}

	GLvoid GetnUniformuiv(GLuint program, GLint location, GLsizei bufSize, GLuint * params) const {
		gl.GetnUniformuiv(program, location, bufSize, params);
		fprintf(GLMethodsDebugFile, "[%4d] GetnUniformuiv(%u, %d, %d, 0x%p)\n", gl.GetError(), program, location, bufSize, params);
	}

	GLvoid ReadnPixels(GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, GLsizei bufSize, GLvoid * data) const {
		gl.ReadnPixels(x, y, width, height, format, type, bufSize, data);
		fprintf(GLMethodsDebugFile, "[%4d] ReadnPixels(%d, %d, %d, %d, 0x%x, 0x%x, %d, 0x%p)\n", gl.GetError(), x, y, width, height, format, type, bufSize, data);
	}

	GLvoid TextureBarrier() const {
		gl.TextureBarrier();
		fprintf(GLMethodsDebugFile, "[%4d] TextureBarrier()\n", gl.GetError());
	}

	PROC_glVertexAttribIPointer VertexAttribIPointer;
	PROC_glVertexAttribLPointer VertexAttribLPointer;
	PROC_glVertexAttribPointer VertexAttribPointer;

	PROC_glGetUniformdv GetUniformdv;
	PROC_glGetUniformfv GetUniformfv;
	PROC_glGetUniformiv GetUniformiv;
	PROC_glGetUniformuiv GetUniformuiv;

	PROC_glProgramUniform1d ProgramUniform1d;
	PROC_glProgramUniform1dv ProgramUniform1dv;
	PROC_glProgramUniform1f ProgramUniform1f;
	PROC_glProgramUniform1fv ProgramUniform1fv;
	PROC_glProgramUniform1i ProgramUniform1i;
	PROC_glProgramUniform1iv ProgramUniform1iv;
	PROC_glProgramUniform1ui ProgramUniform1ui;
	PROC_glProgramUniform1uiv ProgramUniform1uiv;
	PROC_glProgramUniform2d ProgramUniform2d;
	PROC_glProgramUniform2dv ProgramUniform2dv;
	PROC_glProgramUniform2f ProgramUniform2f;
	PROC_glProgramUniform2fv ProgramUniform2fv;
	PROC_glProgramUniform2i ProgramUniform2i;
	PROC_glProgramUniform2iv ProgramUniform2iv;
	PROC_glProgramUniform2ui ProgramUniform2ui;
	PROC_glProgramUniform2uiv ProgramUniform2uiv;
	PROC_glProgramUniform3d ProgramUniform3d;
	PROC_glProgramUniform3dv ProgramUniform3dv;
	PROC_glProgramUniform3f ProgramUniform3f;
	PROC_glProgramUniform3fv ProgramUniform3fv;
	PROC_glProgramUniform3i ProgramUniform3i;
	PROC_glProgramUniform3iv ProgramUniform3iv;
	PROC_glProgramUniform3ui ProgramUniform3ui;
	PROC_glProgramUniform3uiv ProgramUniform3uiv;
	PROC_glProgramUniform4d ProgramUniform4d;
	PROC_glProgramUniform4dv ProgramUniform4dv;
	PROC_glProgramUniform4f ProgramUniform4f;
	PROC_glProgramUniform4fv ProgramUniform4fv;
	PROC_glProgramUniform4i ProgramUniform4i;
	PROC_glProgramUniform4iv ProgramUniform4iv;
	PROC_glProgramUniform4ui ProgramUniform4ui;
	PROC_glProgramUniform4uiv ProgramUniform4uiv;
	PROC_glProgramUniformMatrix2dv ProgramUniformMatrix2dv;
	PROC_glProgramUniformMatrix2fv ProgramUniformMatrix2fv;
	PROC_glProgramUniformMatrix2x3dv ProgramUniformMatrix2x3dv;
	PROC_glProgramUniformMatrix2x3fv ProgramUniformMatrix2x3fv;
	PROC_glProgramUniformMatrix2x4dv ProgramUniformMatrix2x4dv;
	PROC_glProgramUniformMatrix2x4fv ProgramUniformMatrix2x4fv;
	PROC_glProgramUniformMatrix3dv ProgramUniformMatrix3dv;
	PROC_glProgramUniformMatrix3fv ProgramUniformMatrix3fv;
	PROC_glProgramUniformMatrix3x2dv ProgramUniformMatrix3x2dv;
	PROC_glProgramUniformMatrix3x2fv ProgramUniformMatrix3x2fv;
	PROC_glProgramUniformMatrix3x4dv ProgramUniformMatrix3x4dv;
	PROC_glProgramUniformMatrix3x4fv ProgramUniformMatrix3x4fv;
	PROC_glProgramUniformMatrix4dv ProgramUniformMatrix4dv;
	PROC_glProgramUniformMatrix4fv ProgramUniformMatrix4fv;
	PROC_glProgramUniformMatrix4x2dv ProgramUniformMatrix4x2dv;
	PROC_glProgramUniformMatrix4x2fv ProgramUniformMatrix4x2fv;
	PROC_glProgramUniformMatrix4x3dv ProgramUniformMatrix4x3dv;
	PROC_glProgramUniformMatrix4x3fv ProgramUniformMatrix4x3fv;

	bool load() {
		bool success = gl.load();

		VertexAttribIPointer = gl.VertexAttribIPointer;
		VertexAttribLPointer = gl.VertexAttribLPointer;
		VertexAttribPointer = gl.VertexAttribPointer;

		GetUniformdv = gl.GetUniformdv;
		GetUniformfv = gl.GetUniformfv;
		GetUniformiv = gl.GetUniformiv;
		GetUniformuiv = gl.GetUniformuiv;

		ProgramUniform1d = gl.ProgramUniform1d;
		ProgramUniform1dv = gl.ProgramUniform1dv;
		ProgramUniform1f = gl.ProgramUniform1f;
		ProgramUniform1fv = gl.ProgramUniform1fv;
		ProgramUniform1i = gl.ProgramUniform1i;
		ProgramUniform1iv = gl.ProgramUniform1iv;
		ProgramUniform1ui = gl.ProgramUniform1ui;
		ProgramUniform1uiv = gl.ProgramUniform1uiv;
		ProgramUniform2d = gl.ProgramUniform2d;
		ProgramUniform2dv = gl.ProgramUniform2dv;
		ProgramUniform2f = gl.ProgramUniform2f;
		ProgramUniform2fv = gl.ProgramUniform2fv;
		ProgramUniform2i = gl.ProgramUniform2i;
		ProgramUniform2iv = gl.ProgramUniform2iv;
		ProgramUniform2ui = gl.ProgramUniform2ui;
		ProgramUniform2uiv = gl.ProgramUniform2uiv;
		ProgramUniform3d = gl.ProgramUniform3d;
		ProgramUniform3dv = gl.ProgramUniform3dv;
		ProgramUniform3f = gl.ProgramUniform3f;
		ProgramUniform3fv = gl.ProgramUniform3fv;
		ProgramUniform3i = gl.ProgramUniform3i;
		ProgramUniform3iv = gl.ProgramUniform3iv;
		ProgramUniform3ui = gl.ProgramUniform3ui;
		ProgramUniform3uiv = gl.ProgramUniform3uiv;
		ProgramUniform4d = gl.ProgramUniform4d;
		ProgramUniform4dv = gl.ProgramUniform4dv;
		ProgramUniform4f = gl.ProgramUniform4f;
		ProgramUniform4fv = gl.ProgramUniform4fv;
		ProgramUniform4i = gl.ProgramUniform4i;
		ProgramUniform4iv = gl.ProgramUniform4iv;
		ProgramUniform4ui = gl.ProgramUniform4ui;
		ProgramUniform4uiv = gl.ProgramUniform4uiv;
		ProgramUniformMatrix2dv = gl.ProgramUniformMatrix2dv;
		ProgramUniformMatrix2fv = gl.ProgramUniformMatrix2fv;
		ProgramUniformMatrix2x3dv = gl.ProgramUniformMatrix2x3dv;
		ProgramUniformMatrix2x3fv = gl.ProgramUniformMatrix2x3fv;
		ProgramUniformMatrix2x4dv = gl.ProgramUniformMatrix2x4dv;
		ProgramUniformMatrix2x4fv = gl.ProgramUniformMatrix2x4fv;
		ProgramUniformMatrix3dv = gl.ProgramUniformMatrix3dv;
		ProgramUniformMatrix3fv = gl.ProgramUniformMatrix3fv;
		ProgramUniformMatrix3x2dv = gl.ProgramUniformMatrix3x2dv;
		ProgramUniformMatrix3x2fv = gl.ProgramUniformMatrix3x2fv;
		ProgramUniformMatrix3x4dv = gl.ProgramUniformMatrix3x4dv;
		ProgramUniformMatrix3x4fv = gl.ProgramUniformMatrix3x4fv;
		ProgramUniformMatrix4dv = gl.ProgramUniformMatrix4dv;
		ProgramUniformMatrix4fv = gl.ProgramUniformMatrix4fv;
		ProgramUniformMatrix4x2dv = gl.ProgramUniformMatrix4x2dv;
		ProgramUniformMatrix4x2fv = gl.ProgramUniformMatrix4x2fv;
		ProgramUniformMatrix4x3dv = gl.ProgramUniformMatrix4x3dv;
		ProgramUniformMatrix4x3fv = gl.ProgramUniformMatrix4x3fv;

		return success;
	}

private:
	GLMethodsDebugImpl(const GLMethodsDebugImpl & copy);
	void operator = (const GLMethodsDebugImpl & rhs);
};

#endif
