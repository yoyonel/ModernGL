#include "Python-ModernGL.hpp"

#include "Python-Types.hpp"
#include "ModernGL.hpp"

bool initialized = false;
PyObject * ModuleError;

PyObject * InitializeModernGL(PyObject * self, PyObject * args);

PyObject * ExtensionActive(PyObject * self, PyObject * args) {
	if (!PyArg_ParseTuple(args, ":ExtensionActive")) {
		PyErr_SetString(ModuleError, "exlqbywv");
		return 0;
	}

	if (ModernGL::ExtensionActive()) {
		Py_RETURN_TRUE;
	} else {
		Py_RETURN_FALSE;
	}
}

PyObject * GetError(PyObject * self, PyObject * args) {
	if (!PyArg_ParseTuple(args, ":GetError")) {
		PyErr_SetString(ModuleError, "nkwsmtfl");
		return 0;
	}

	return PyUnicode_FromString(ModernGL::GetError());
}

PyObject * GetInfo(PyObject * self, PyObject * args) {
	if (!PyArg_ParseTuple(args, ":GetInfo")) {
		PyErr_SetString(ModuleError, "dmvirybw");
		return 0;
	}

	ModernGL::Info info = ModernGL::GetInfo();
	return Py_BuildValue("iiiss", info.major, info.minor, info.samples, info.vendor, info.renderer);
}

PyObject * Viewport(PyObject * self, PyObject * args, PyObject * kwargs) {
	int x;
	int y;
	int width;
	int height;

	static const char * kwlist[] = {"x", "y", "width", "height", 0};

	if (!PyArg_ParseTupleAndKeywords(args, kwargs, "iiii:Viewport", (char **)kwlist, &x, &y, &width, &height)) {
		PyErr_SetString(ModuleError, "mjckhbse");
		return 0;
	}

	ModernGL::Viewport(x, y, width, height);
	Py_RETURN_NONE;
}

PyObject * Clear(PyObject * self, PyObject * args, PyObject * kwargs) {
	unsigned char r = 0;
	unsigned char g = 0;
	unsigned char b = 0;
	unsigned char a = 255;

	static const char * kwlist[] = {"r", "g", "b", "a", 0};

	if (!PyArg_ParseTupleAndKeywords(args, kwargs, "|bbbb:Clear", (char **)kwlist, &r, &g, &b, &a)) {
		PyErr_SetString(ModuleError, "rtlqkfcl");
		return 0;
	}

	ModernGL::Clear(r, g, b, a);
	Py_RETURN_NONE;
}

PyObject * PointSize(PyObject * self, PyObject * args) {
	float size;

	if (!PyArg_ParseTuple(args, "f:PointSize", &size)) {
		PyErr_SetString(ModuleError, "jvbfqdwg");
		return 0;
	}

	ModernGL::PointSize(size);
	Py_RETURN_NONE;
}

PyObject * LineSize(PyObject * self, PyObject * args) {
	float size;

	if (!PyArg_ParseTuple(args, "f:LineSize", &size)) {
		PyErr_SetString(ModuleError, "iaphsgtx");
		return 0;
	}

	ModernGL::LineSize(size);
	Py_RETURN_NONE;
}

PyObject * EnableOnly(PyObject * self, PyObject * args) {
	unsigned mask;

	if (!PyArg_ParseTuple(args, "I:EnableOnly", &mask)) {
		PyErr_SetString(ModuleError, "ltvmyxzj");
		return 0;
	}

	ModernGL::EnableOnly(mask);
	Py_RETURN_NONE;
}

PyObject * EnableBlend(PyObject * self, PyObject * args) {
	if (!PyArg_ParseTuple(args, ":EnableBlend")) {
		PyErr_SetString(ModuleError, "wrublzoc");
		return 0;
	}

	ModernGL::EnableBlend();
	Py_RETURN_NONE;
}

PyObject * DisableBlend(PyObject * self, PyObject * args) {
	if (!PyArg_ParseTuple(args, ":DisableBlend")) {
		PyErr_SetString(ModuleError, "iglmurfx");
		return 0;
	}

	ModernGL::DisableBlend();
	Py_RETURN_NONE;
}

PyObject * EnableCullFace(PyObject * self, PyObject * args) {
	if (!PyArg_ParseTuple(args, ":EnableCullFace")) {
		PyErr_SetString(ModuleError, "lgzfqlyh");
		return 0;
	}

	ModernGL::EnableCullFace();
	Py_RETURN_NONE;
}

PyObject * DisableCullFace(PyObject * self, PyObject * args) {
	if (!PyArg_ParseTuple(args, ":DisableCullFace")) {
		PyErr_SetString(ModuleError, "mvkrwcph");
		return 0;
	}

	ModernGL::DisableCullFace();
	Py_RETURN_NONE;
}

PyObject * EnableDepthTest(PyObject * self, PyObject * args) {
	if (!PyArg_ParseTuple(args, ":EnableDepthTest")) {
		PyErr_SetString(ModuleError, "fpgeoqdz");
		return 0;
	}

	ModernGL::EnableDepthTest();
	Py_RETURN_NONE;
}

PyObject * DisableDepthTest(PyObject * self, PyObject * args) {
	if (!PyArg_ParseTuple(args, ":DisableDepthTest")) {
		PyErr_SetString(ModuleError, "kqhdetyu");
		return 0;
	}

	ModernGL::DisableDepthTest();
	Py_RETURN_NONE;
}

PyObject * EnableMultisample(PyObject * self, PyObject * args) {
	if (!PyArg_ParseTuple(args, ":EnableMultisample")) {
		PyErr_SetString(ModuleError, "fmalwrvd");
		return 0;
	}

	ModernGL::EnableMultisample();
	Py_RETURN_NONE;
}

PyObject * DisableMultisample(PyObject * self, PyObject * args) {
	if (!PyArg_ParseTuple(args, ":DisableMultisample")) {
		PyErr_SetString(ModuleError, "chbmiest");
		return 0;
	}

	ModernGL::DisableMultisample();
	Py_RETURN_NONE;
}

PyObject * NewVertexShader(PyObject * self, PyObject * args) {
	const char * source;

	if (!PyArg_ParseTuple(args, "s:NewVertexShader", &source)) {
		PyErr_SetString(ModuleError, "wrljfqbi");
		return 0;
	}

	return CreateShaderType(ModernGL::NewVertexShader(source));
}

PyObject * NewFragmentShader(PyObject * self, PyObject * args) {
	const char * source;

	if (!PyArg_ParseTuple(args, "s:NewFragmentShader", &source)) {
		PyErr_SetString(ModuleError, "aswmpzdf");
		return 0;
	}

	return CreateShaderType(ModernGL::NewFragmentShader(source));
}

PyObject * NewGeometryShader(PyObject * self, PyObject * args) {
	const char * source;

	if (!PyArg_ParseTuple(args, "s:NewGeometryShader", &source)) {
		PyErr_SetString(ModuleError, "yvdspmhl");
		return 0;
	}

	return CreateShaderType(ModernGL::NewGeometryShader(source));
}

PyObject * DeleteShader(PyObject * self, PyObject * args) {
	Shader * shader;

	if (!PyArg_ParseTuple(args, "O:DeleteShader", &shader)) {
		PyErr_SetString(ModuleError, "sdhfalou");
		return 0;
	}

	if (!PyObject_TypeCheck((PyObject *)shader, &ShaderType)) {
		PyErr_SetString(ModuleError, "hvbcirna");
		return 0;
	}

	ModernGL::DeleteShader(shader->shader);
	Py_RETURN_NONE;
}

PyObject * NewProgram(PyObject * self, PyObject * args) {
	PyObject * lst;

	if (!PyArg_ParseTuple(args, "O:NewProgram", &lst)) {
		PyErr_SetString(ModuleError, "avrnfotj");
		return 0;
	}

	if (!PyObject_TypeCheck((PyObject *)lst, &PyList_Type)) {
		PyErr_SetString(ModuleError, "caoypwbf");
		return 0;
	}

	int count = (int)PyList_Size(lst);
	int * shader_array = new int[count];
	for (int i = 0; i < count; ++i) {
		Shader * shader = (Shader *)PyList_GetItem(lst, i);
		if (!PyObject_TypeCheck((PyObject *)shader, &ShaderType)) {
			PyErr_SetString(ModuleError, "fexnjdzq");
			return 0;
		}
		shader_array[i] = shader->shader;
	}
	int program = ModernGL::NewProgram(shader_array, count);
	delete[] shader_array;

	return CreateProgramType(program);
}

PyObject * DeleteProgram(PyObject * self, PyObject * args) {
	Program * program;

	if (!PyArg_ParseTuple(args, "O:DeleteProgram", &program)) {
		PyErr_SetString(ModuleError, "lbltafke");
		return 0;
	}

	if (!PyObject_TypeCheck((PyObject *)program, &ProgramType)) {
		PyErr_SetString(ModuleError, "tnapjoqu");
		return 0;
	}

	ModernGL::DeleteProgram(program->program);
	Py_RETURN_NONE;
}

PyObject * UseProgram(PyObject * self, PyObject * args) {
	Program * program;

	if (!PyArg_ParseTuple(args, "O:UseProgram", &program)) {
		PyErr_SetString(ModuleError, "wdeayruv");
		return 0;
	}

	if (!PyObject_TypeCheck((PyObject *)program, &ProgramType)) {
		PyErr_SetString(ModuleError, "lalsmrdz");
		return 0;
	}

	ModernGL::UseProgram(program->program);
	Py_RETURN_NONE;
}

PyObject * UseDefaultProgram(PyObject * self, PyObject * args) {
	if (!PyArg_ParseTuple(args, ":UseDefaultProgram")) {
		PyErr_SetString(ModuleError, "kijdpngu");
		return 0;
	}

	ModernGL::UseDefaultProgram();
	Py_RETURN_NONE;
}

PyObject * CompilerLog(PyObject * self, PyObject * args) {
	if (!PyArg_ParseTuple(args, ":CompilerLog")) {
		PyErr_SetString(ModuleError, "gokalhcj");
		return 0;
	}

	return PyUnicode_FromString(ModernGL::CompilerLog());
}

PyObject * GetAttributeLocation(PyObject * self, PyObject * args, PyObject * kwargs) {
	Program * program;
	const char * name;

	static const char * kwlist[] = {"program", "name", 0};

	if (!PyArg_ParseTupleAndKeywords(args, kwargs, "Os:GetAttributeLocation", (char **)kwlist, &program, &name)) {
		PyErr_SetString(ModuleError, "xwtudqbn");
		return 0;
	}

	if (!PyObject_TypeCheck((PyObject *)program, &ProgramType)) {
		PyErr_SetString(ModuleError, "caoypwbf");
		return 0;
	}

	return CreateAttributeLocationType(ModernGL::GetAttributeLocation(program->program, name));
}

PyObject * GetUniformLocation(PyObject * self, PyObject * args, PyObject * kwargs) {
	Program * program;
	const char * name;

	static const char * kwlist[] = {"program", "name", 0};

	if (!PyArg_ParseTupleAndKeywords(args, kwargs, "Os:GetUniformLocation", (char **)kwlist, &program, &name)) {
		PyErr_SetString(ModuleError, "blaypukz");
		return 0;
	}

	if (!PyObject_TypeCheck((PyObject *)program, &ProgramType)) {
		PyErr_SetString(ModuleError, "caoypwbf");
		return 0;
	}

	return CreateUniformLocationType(ModernGL::GetUniformLocation(program->program, name));
}

PyObject * GetUniformBlockLocation(PyObject * self, PyObject * args, PyObject * kwargs) {
	Program * program;
	const char * name;

	static const char * kwlist[] = {"program", "name", 0};

	if (!PyArg_ParseTupleAndKeywords(args, kwargs, "Os:GetUniformBlockLocation", (char **)kwlist, &program, &name)) {
		PyErr_SetString(ModuleError, "zlfavgkq");
		return 0;
	}

	if (!PyObject_TypeCheck((PyObject *)program, &ProgramType)) {
		PyErr_SetString(ModuleError, "caoypwbf");
		return 0;
	}

	return CreateUniformBlockLocationType(ModernGL::GetUniformBlockLocation(program->program, name));
}

PyObject * Uniform1f(PyObject * self, PyObject * args) {
	UniformLocation * location;
	float v0;

	if (!PyArg_ParseTuple(args, "Of:Uniform1f", &location, &v0)) {
		PyErr_SetString(ModuleError, "qaxfzicr");
		return 0;
	}

	if (!PyObject_TypeCheck((PyObject *)location, &UniformLocationType)) {
		PyErr_SetString(ModuleError, "caoypwbf");
		return 0;
	}

	ModernGL::Uniform1f(location->location, v0);
	Py_RETURN_NONE;
}

PyObject * Uniform2f(PyObject * self, PyObject * args) {
	UniformLocation * location;
	float v0;
	float v1;

	if (!PyArg_ParseTuple(args, "Off:Uniform2f", &location, &v0, &v1)) {
		PyErr_SetString(ModuleError, "kfqmuaoy");
		return 0;
	}

	if (!PyObject_TypeCheck((PyObject *)location, &UniformLocationType)) {
		PyErr_SetString(ModuleError, "caoypwbf");
		return 0;
	}

	ModernGL::Uniform2f(location->location, v0, v1);
	Py_RETURN_NONE;
}

PyObject * Uniform3f(PyObject * self, PyObject * args) {
	UniformLocation * location;
	float v0;
	float v1;
	float v2;

	if (!PyArg_ParseTuple(args, "Offf:Uniform3f", &location, &v0, &v1, &v2)) {
		PyErr_SetString(ModuleError, "wlvzmscp");
		return 0;
	}

	if (!PyObject_TypeCheck((PyObject *)location, &UniformLocationType)) {
		PyErr_SetString(ModuleError, "caoypwbf");
		return 0;
	}

	ModernGL::Uniform3f(location->location, v0, v1, v2);
	Py_RETURN_NONE;
}

PyObject * Uniform4f(PyObject * self, PyObject * args) {
	UniformLocation * location;
	float v0;
	float v1;
	float v2;
	float v3;

	if (!PyArg_ParseTuple(args, "Offff:Uniform4f", &location, &v0, &v1, &v2, &v3)) {
		PyErr_SetString(ModuleError, "ojkqtfcw");
		return 0;
	}

	if (!PyObject_TypeCheck((PyObject *)location, &UniformLocationType)) {
		PyErr_SetString(ModuleError, "caoypwbf");
		return 0;
	}

	ModernGL::Uniform4f(location->location, v0, v1, v2, v3);
	Py_RETURN_NONE;
}

PyObject * Uniform1i(PyObject * self, PyObject * args) {
	UniformLocation * location;
	int v0;

	if (!PyArg_ParseTuple(args, "Oi:Uniform1i", &location, &v0)) {
		PyErr_SetString(ModuleError, "xqpcozbk");
		return 0;
	}

	if (!PyObject_TypeCheck((PyObject *)location, &UniformLocationType)) {
		PyErr_SetString(ModuleError, "caoypwbf");
		return 0;
	}

	ModernGL::Uniform1i(location->location, v0);
	Py_RETURN_NONE;
}

PyObject * Uniform2i(PyObject * self, PyObject * args) {
	UniformLocation * location;
	int v0;
	int v1;

	if (!PyArg_ParseTuple(args, "Oii:Uniform2i", &location, &v0, &v1)) {
		PyErr_SetString(ModuleError, "ikcsvayz");
		return 0;
	}

	if (!PyObject_TypeCheck((PyObject *)location, &UniformLocationType)) {
		PyErr_SetString(ModuleError, "caoypwbf");
		return 0;
	}

	ModernGL::Uniform2i(location->location, v0, v1);
	Py_RETURN_NONE;
}

PyObject * Uniform3i(PyObject * self, PyObject * args) {
	UniformLocation * location;
	int v0;
	int v1;
	int v2;

	if (!PyArg_ParseTuple(args, "Oiii:Uniform3i", &location, &v0, &v1, &v2)) {
		PyErr_SetString(ModuleError, "egurbpxt");
		return 0;
	}

	if (!PyObject_TypeCheck((PyObject *)location, &UniformLocationType)) {
		PyErr_SetString(ModuleError, "caoypwbf");
		return 0;
	}

	ModernGL::Uniform3i(location->location, v0, v1, v2);
	Py_RETURN_NONE;
}

PyObject * Uniform4i(PyObject * self, PyObject * args) {
	UniformLocation * location;
	int v0;
	int v1;
	int v2;
	int v3;

	if (!PyArg_ParseTuple(args, "Oiiii:Uniform4i", &location, &v0, &v1, &v2, &v3)) {
		PyErr_SetString(ModuleError, "uxhoveqg");
		return 0;
	}

	if (!PyObject_TypeCheck((PyObject *)location, &UniformLocationType)) {
		PyErr_SetString(ModuleError, "caoypwbf");
		return 0;
	}

	ModernGL::Uniform4i(location->location, v0, v1, v2, v3);
	Py_RETURN_NONE;
}

PyObject * UniformMatrix(PyObject * self, PyObject * args) {
	UniformLocation * location;
	PyObject * lst;

	if (!PyArg_ParseTuple(args, "OO:UniformMatrix", &location, &lst)) {
		PyErr_SetString(ModuleError, "cswzjnvx");
		return 0;
	}

	if (!PyObject_TypeCheck((PyObject *)location, &UniformLocationType)) {
		PyErr_SetString(ModuleError, "caoypwbf");
		return 0;
	}

	if (!PyObject_TypeCheck((PyObject *)lst, &PyList_Type)) {
		PyErr_SetString(ModuleError, "caoypwbf");
		return 0;
	}

	float matrix[16];

	int count = (int)PyList_Size(lst);
	for (int i = 0; i < count; ++i) {
		matrix[i] = (float)PyFloat_AsDouble(PyList_GetItem(lst, i));
	}

	ModernGL::UniformMatrix(location->location, matrix);
	Py_RETURN_NONE;
}

PyObject * UniformTransposeMatrix(PyObject * self, PyObject * args) {
	UniformLocation * location;
	PyObject * lst;

	if (!PyArg_ParseTuple(args, "OO:UniformTransposeMatrix", &location, &lst)) {
		PyErr_SetString(ModuleError, "buazcrsv");
		return 0;
	}

	if (!PyObject_TypeCheck((PyObject *)location, &UniformLocationType)) {
		PyErr_SetString(ModuleError, "caoypwbf");
		return 0;
	}

	if (!PyObject_TypeCheck((PyObject *)lst, &PyList_Type)) {
		PyErr_SetString(ModuleError, "caoypwbf");
		return 0;
	}

	float matrix[16];

	int count = (int)PyList_Size(lst);
	for (int i = 0; i < count; ++i) {
		matrix[i] = (float)PyFloat_AsDouble(PyList_GetItem(lst, i));
	}

	ModernGL::UniformTransposeMatrix(location->location, matrix);
	Py_RETURN_NONE;
}

PyObject * UseUniformBlock(PyObject * self, PyObject * args, PyObject * kwargs) {
	UniformBlockLocation * location;
	int buffer;

	static const char * kwlist[] = {"location", "buffer", 0};

	if (!PyArg_ParseTupleAndKeywords(args, kwargs, "Oi:UseUniformBlock", (char **)kwlist, &location, &buffer)) {
		PyErr_SetString(ModuleError, "byviqlph");
		return 0;
	}

	if (!PyObject_TypeCheck((PyObject *)location, &UniformBlockLocationType)) {
		PyErr_SetString(ModuleError, "caoypwbf");
		return 0;
	}

	ModernGL::UseUniformBlock(location->location, buffer);
	Py_RETURN_NONE;
}

PyObject * NewTexture(PyObject * self, PyObject * args, PyObject * kwargs) {
	int width;
	int height;
	const void * data;
	int components = 3;
	int size;

	static const char * kwlist[] = {"width", "height", "data", "components", 0};

	if (!PyArg_ParseTupleAndKeywords(args, kwargs, "iiy#|i:NewTexture", (char **)kwlist, &width, &height, &data, &size, &components)) {
		PyErr_SetString(ModuleError, "lwnrkbjo");
		return 0;
	}

	return CreateTextureType(ModernGL::NewTexture(width, height, data, components));
}

PyObject * DeleteTexture(PyObject * self, PyObject * args) {
	Texture * texture;

	if (!PyArg_ParseTuple(args, "O:DeleteTexture", &texture)) {
		PyErr_SetString(ModuleError, "szncgvmh");
		return 0;
	}

	if (!PyObject_TypeCheck((PyObject *)texture, &TextureType)) {
		PyErr_SetString(ModuleError, "caoypwbf");
		return 0;
	}

	ModernGL::DeleteTexture(texture->texture);
	Py_RETURN_NONE;
}

PyObject * UpdateTexture(PyObject * self, PyObject * args, PyObject * kwargs) {
	Texture * texture;
	int x;
	int y;
	int width;
	int height;
	const void * data;
	int components = 3;
	int size;

	static const char * kwlist[] = {"texture", "x", "y", "width", "height", "data", "components", 0};

	if (!PyArg_ParseTupleAndKeywords(args, kwargs, "Oiiiiy#|i:UpdateTexture", (char **)kwlist, &texture, &x, &y, &width, &height, &data, &size, &components)) {
		PyErr_SetString(ModuleError, "khvglbpr");
		return 0;
	}

	if (!PyObject_TypeCheck((PyObject *)texture, &TextureType)) {
		PyErr_SetString(ModuleError, "caoypwbf");
		return 0;
	}

	ModernGL::UpdateTexture(texture->texture, x, y, width, height, data, components);
	Py_RETURN_NONE;
}

PyObject * UseTexture(PyObject * self, PyObject * args) {
	Texture * texture;
	int location = 0;

	if (!PyArg_ParseTuple(args, "O|i:UseTexture", &texture, &location)) {
		PyErr_SetString(ModuleError, "hgpnyora");
		return 0;
	}

	if (!PyObject_TypeCheck((PyObject *)texture, &TextureType)) {
		PyErr_SetString(ModuleError, "caoypwbf");
		return 0;
	}

	ModernGL::UseTexture(texture->texture, location);
	Py_RETURN_NONE;
}

PyObject * SetTexturePixelated(PyObject * self, PyObject * args) {
	Texture * texture;
	
	if (!PyArg_ParseTuple(args, "O:SetTexturePixelated", &texture)) {
		PyErr_SetString(ModuleError, "rbqlyasl");
		return 0;
	}

	if (!PyObject_TypeCheck((PyObject *)texture, &TextureType)) {
		PyErr_SetString(ModuleError, "caoypwbf");
		return 0;
	}

	ModernGL::SetTexturePixelated(texture->texture);
	Py_RETURN_NONE;
}

PyObject * SetTextureFiltered(PyObject * self, PyObject * args) {
	Texture * texture;
	
	if (!PyArg_ParseTuple(args, "O:SetTextureFiltered", &texture)) {
		PyErr_SetString(ModuleError, "mfxizpan");
		return 0;
	}

	if (!PyObject_TypeCheck((PyObject *)texture, &TextureType)) {
		PyErr_SetString(ModuleError, "caoypwbf");
		return 0;
	}

	ModernGL::SetTextureFiltered(texture->texture);
	Py_RETURN_NONE;
}

PyObject * SetTextureMipmapped(PyObject * self, PyObject * args) {
	Texture * texture;
	
	if (!PyArg_ParseTuple(args, "O:SetTextureMipmapped", &texture)) {
		PyErr_SetString(ModuleError, "pjfcsuly");
		return 0;
	}

	if (!PyObject_TypeCheck((PyObject *)texture, &TextureType)) {
		PyErr_SetString(ModuleError, "caoypwbf");
		return 0;
	}

	ModernGL::SetTextureMipmapped(texture->texture);
	Py_RETURN_NONE;
}

PyObject * BuildMipmap(PyObject * self, PyObject * args, PyObject * kwargs) {
	Texture * texture;
	int base = 0;
	int max = 1000;

	static const char * kwlist[] = {"texture", "base", "max", 0};

	if (!PyArg_ParseTupleAndKeywords(args, kwargs, "O|ii:BuildMipmap", (char **)kwlist, &texture, &base, &max)) {
		PyErr_SetString(ModuleError, "nugflxsc");
		return 0;
	}

	if (!PyObject_TypeCheck((PyObject *)texture, &TextureType)) {
		PyErr_SetString(ModuleError, "caoypwbf");
		return 0;
	}

	ModernGL::BuildMipmap(texture->texture, base, max);
	Py_RETURN_NONE;
}

PyObject * NewVertexArray(PyObject * self, PyObject * args) {
	const char * format;
	PyObject * lst;

	IndexBuffer * indexBuffer = 0;

	if (!PyArg_ParseTuple(args, "sO|O:NewVertexArray", &format, &lst, &indexBuffer)) {
		PyErr_SetString(ModuleError, "hjzalkdw");
		return 0;
	}

	if (!PyObject_TypeCheck((PyObject *)lst, &PyList_Type)) {
		PyErr_SetString(ModuleError, "caoypwbf");
		return 0;
	}

	if (indexBuffer) {
		if (!PyObject_TypeCheck((PyObject *)indexBuffer, &IndexBufferType)) {
			PyErr_SetString(ModuleError, "caoypwbf");
			return 0;
		}
	}

	int count = (int)PyList_Size(lst);
	ModernGL::VertexBufferAndAttribute * attribs = new ModernGL::VertexBufferAndAttribute[count];
	for (int i = 0; i < count; ++i) {
		PyObject * tuple = PyList_GetItem(lst, i);

		VertexBuffer * buffer = (VertexBuffer *)PyTuple_GetItem(tuple, 0);

		if (!PyObject_TypeCheck((PyObject *)buffer, &VertexBufferType)) {
			PyErr_SetString(ModuleError, "caoypwbf");
			return 0;
		}

		AttributeLocation * location = (AttributeLocation *)PyTuple_GetItem(tuple, 1);

		if (!PyObject_TypeCheck((PyObject *)location, &AttributeLocationType)) {
			PyErr_SetString(ModuleError, "caoypwbf");
			return 0;
		}

		attribs[i].buffer = buffer->vbo;
		attribs[i].attribute = location->location;
	}

	PyObject * result = CreateVertexArrayType(ModernGL::NewVertexArray(format, attribs, indexBuffer ? indexBuffer->ibo : 0));
	delete[] attribs;
	return result;
}

PyObject * DeleteVertexArray(PyObject * self, PyObject * args) {
	VertexArray * vao;

	if (!PyArg_ParseTuple(args, "O:DeleteVertexArray", &vao)) {
		PyErr_SetString(ModuleError, "sxueawod");
		return 0;
	}

	if (!PyObject_TypeCheck((PyObject *)vao, &VertexArrayType)) {
		PyErr_SetString(ModuleError, "caoypwbf");
		return 0;
	}

	ModernGL::DeleteVertexArray(vao->vao);
	Py_RETURN_NONE;
}

PyObject * EnableAttribute(PyObject * self, PyObject * args, PyObject * kwargs) {
	VertexArray * vao;
	AttributeLocation * location;

	static const char * kwlist[] = {"vao", "target", 0};

	if (!PyArg_ParseTupleAndKeywords(args, kwargs, "OO:EnableAttribute", (char **)kwlist, &vao, &location)) {
		PyErr_SetString(ModuleError, "itneqllz");
		return 0;
	}

	if (!PyObject_TypeCheck((PyObject *)vao, &VertexArrayType)) {
		PyErr_SetString(ModuleError, "caoypwbf");
		return 0;
	}

	if (!PyObject_TypeCheck((PyObject *)location, &AttributeLocationType)) {
		PyErr_SetString(ModuleError, "caoypwbf");
		return 0;
	}

	ModernGL::EnableAttribute(vao->vao, location->location);
	Py_RETURN_NONE;
}

PyObject * DisableAttribute(PyObject * self, PyObject * args, PyObject * kwargs) {
	VertexArray * vao;
	AttributeLocation * location;

	static const char * kwlist[] = {"vao", "target", 0};

	if (!PyArg_ParseTupleAndKeywords(args, kwargs, "OO:DisableAttribute", (char **)kwlist, &vao, &location)) {
		PyErr_SetString(ModuleError, "rklhgpmo");
		return 0;
	}

	if (!PyObject_TypeCheck((PyObject *)vao, &VertexArrayType)) {
		PyErr_SetString(ModuleError, "caoypwbf");
		return 0;
	}

	if (!PyObject_TypeCheck((PyObject *)location, &AttributeLocationType)) {
		PyErr_SetString(ModuleError, "caoypwbf");
		return 0;
	}

	ModernGL::DisableAttribute(vao->vao, location->location);
	Py_RETURN_NONE;
}

PyObject * EnableAttributes(PyObject * self, PyObject * args, PyObject * kwargs) {
	VertexArray * vao;
	PyObject * attribs;

	static const char * kwlist[] = {"vao", "targets", 0};

	if (!PyArg_ParseTupleAndKeywords(args, kwargs, "OO:EnableAttributes", (char **)kwlist, &vao, &attribs)) {
		PyErr_SetString(ModuleError, "tuqldrme");
		return 0;
	}

	if (!PyObject_TypeCheck((PyObject *)vao, &VertexArrayType)) {
		PyErr_SetString(ModuleError, "caoypwbf");
		return 0;
	}

	if (!PyObject_TypeCheck((PyObject *)attribs, &PyList_Type)) {
		PyErr_SetString(ModuleError, "caoypwbf");
		return 0;
	}

	int size = (int)PyList_Size(attribs);
	int * attrib_array = new int[size];
	for (int i = 0; i < size; ++i) {
		AttributeLocation * location = (AttributeLocation *)PyList_GetItem(attribs, i);

		if (!PyObject_TypeCheck((PyObject *)location, &AttributeLocationType)) {
			PyErr_SetString(ModuleError, "caoypwbf");
			return 0;
		}

		attrib_array[i] = location->location;
	}
	ModernGL::EnableAttributes(vao->vao, attrib_array, size);
	delete[] attrib_array;
	Py_RETURN_NONE;
}

PyObject * DisableAttributes(PyObject * self, PyObject * args, PyObject * kwargs) {
	VertexArray * vao;
	PyObject * attribs;

	static const char * kwlist[] = {"vao", "targets", 0};

	if (!PyArg_ParseTupleAndKeywords(args, kwargs, "OO:DisableAttributes", (char **)kwlist, &vao, &attribs)) {
		PyErr_SetString(ModuleError, "aqtznkvh");
		return 0;
	}

	if (!PyObject_TypeCheck((PyObject *)vao, &VertexArrayType)) {
		PyErr_SetString(ModuleError, "caoypwbf");
		return 0;
	}

	if (!PyObject_TypeCheck((PyObject *)attribs, &PyList_Type)) {
		PyErr_SetString(ModuleError, "caoypwbf");
		return 0;
	}

	int size = (int)PyList_Size(attribs);
	int * attrib_array = new int[size];
	for (int i = 0; i < size; ++i) {
		AttributeLocation * location = (AttributeLocation *)PyList_GetItem(attribs, i);

		if (!PyObject_TypeCheck((PyObject *)location, &AttributeLocationType)) {
			PyErr_SetString(ModuleError, "caoypwbf");
			return 0;
		}

		attrib_array[i] = location->location;
	}
	ModernGL::DisableAttributes(vao->vao, attrib_array, size);
	delete[] attrib_array;
	Py_RETURN_NONE;
}

PyObject * NewVertexBuffer(PyObject * self, PyObject * args) {
	const void * data;
	int size;

	if (!PyArg_ParseTuple(args, "y#:NewVertexBuffer", &data, &size)) {
		PyErr_SetString(ModuleError, "lljuhybq");
		return 0;
	}

	return CreateVertexBufferType(ModernGL::NewVertexBuffer(data, size));
}

PyObject * NewIndexBuffer(PyObject * self, PyObject * args) {
	const void * data;
	int size;

	if (!PyArg_ParseTuple(args, "y#:NewIndexBuffer", &data, &size)) {
		PyErr_SetString(ModuleError, "itcyrnos");
		return 0;
	}

	return CreateIndexBufferType(ModernGL::NewIndexBuffer(data, size));
}

PyObject * NewUniformBuffer(PyObject * self, PyObject * args) {
	const void * data;
	int size;

	if (!PyArg_ParseTuple(args, "y#:NewUniformBuffer", &data, &size)) {
		PyErr_SetString(ModuleError, "tgdsecul");
		return 0;
	}

	return CreateUniformBufferType(ModernGL::NewUniformBuffer(data, size));
}

PyObject * NewDynamicVertexBuffer(PyObject * self, PyObject * args) {
	const void * data;
	int size;

	if (!PyArg_ParseTuple(args, "y#:NewDynamicVertexBuffer", &data, &size)) {
		PyErr_SetString(ModuleError, "slmdahqn");
		return 0;
	}

	return CreateVertexBufferType(ModernGL::NewDynamicVertexBuffer(data, size));
}

PyObject * NewDynamicIndexBuffer(PyObject * self, PyObject * args) {
	const void * data;
	int size;

	if (!PyArg_ParseTuple(args, "y#:NewDynamicIndexBuffer", &data, &size)) {
		PyErr_SetString(ModuleError, "xmslqfur");
		return 0;
	}

	return CreateIndexBufferType(ModernGL::NewDynamicIndexBuffer(data, size));
}

PyObject * NewDynamicUniformBuffer(PyObject * self, PyObject * args) {
	const void * data;
	int size;

	if (!PyArg_ParseTuple(args, "y#:NewDynamicUniformBuffer", &data, &size)) {
		PyErr_SetString(ModuleError, "vdbjqrsl");
		return 0;
	}

	return CreateUniformBufferType(ModernGL::NewDynamicUniformBuffer(data, size));
}

PyObject * DeleteVertexBuffer(PyObject * self, PyObject * args) {
	VertexBuffer * buffer;

	if (!PyArg_ParseTuple(args, "O:DeleteVertexBuffer", &buffer)) {
		PyErr_SetString(ModuleError, "snpklqxa");
		return 0;
	}

	if (!PyObject_TypeCheck((PyObject *)buffer, &VertexBufferType)) {
		PyErr_SetString(ModuleError, "caoypwbf");
		return 0;
	}

	ModernGL::DeleteVertexBuffer(buffer->vbo);
	Py_RETURN_NONE;
}

PyObject * DeleteIndexBuffer(PyObject * self, PyObject * args) {
	IndexBuffer * buffer;

	if (!PyArg_ParseTuple(args, "O:DeleteIndexBuffer", &buffer)) {
		PyErr_SetString(ModuleError, "snpklqxa");
		return 0;
	}

	if (!PyObject_TypeCheck((PyObject *)buffer, &IndexBufferType)) {
		PyErr_SetString(ModuleError, "caoypwbf");
		return 0;
	}

	ModernGL::DeleteIndexBuffer(buffer->ibo);
	Py_RETURN_NONE;
}

PyObject * DeleteUniformBuffer(PyObject * self, PyObject * args) {
	UniformBuffer * buffer;

	if (!PyArg_ParseTuple(args, "O:DeleteUniformBuffer", &buffer)) {
		PyErr_SetString(ModuleError, "snpklqxa");
		return 0;
	}

	if (!PyObject_TypeCheck((PyObject *)buffer, &UniformBufferType)) {
		PyErr_SetString(ModuleError, "caoypwbf");
		return 0;
	}

	ModernGL::DeleteUniformBuffer(buffer->ubo);
	Py_RETURN_NONE;
}

PyObject * UpdateVertexBuffer(PyObject * self, PyObject * args, PyObject * kwargs) {
	int buffer;
	int offset;
	const void * data;
	int size;

	static const char * kwlist[] = {"buffer", "offset", "data", 0};

	if (!PyArg_ParseTupleAndKeywords(args, kwargs, "iiy#:UpdateVertexBuffer", (char **)kwlist, &buffer, &offset, &data, &size)) {
		PyErr_SetString(ModuleError, "mypkwlav");
		return 0;
	}

	ModernGL::UpdateVertexBuffer(buffer, offset, data, size);
	Py_RETURN_NONE;
}

PyObject * UpdateIndexBuffer(PyObject * self, PyObject * args, PyObject * kwargs) {
	int buffer;
	int offset;
	const void * data;
	int size;

	static const char * kwlist[] = {"buffer", "offset", "data", 0};

	if (!PyArg_ParseTupleAndKeywords(args, kwargs, "iiy#:UpdateIndexBuffer", (char **)kwlist, &buffer, &offset, &data, &size)) {
		PyErr_SetString(ModuleError, "qlpozdbg");
		return 0;
	}

	ModernGL::UpdateIndexBuffer(buffer, offset, data, size);
	Py_RETURN_NONE;
}

PyObject * UpdateUniformBuffer(PyObject * self, PyObject * args, PyObject * kwargs) {
	int buffer;
	int offset;
	const void * data;
	int size;

	static const char * kwlist[] = {"buffer", "offset", "data", 0};

	if (!PyArg_ParseTupleAndKeywords(args, kwargs, "iiy#:UpdateUniformBuffer", (char **)kwlist, &buffer, &offset, &data, &size)) {
		PyErr_SetString(ModuleError, "akzvcsmq");
		return 0;
	}

	ModernGL::UpdateUniformBuffer(buffer, offset, data, size);
	Py_RETURN_NONE;
}

PyObject * RenderTriangles(PyObject * self, PyObject * args, PyObject * kwargs) {
	VertexArray * vao;
	int count;
	int first = 0;
	int instances = 1;

	static const char * kwlist[] = {"vao", "count", "first", "instances", 0};

	if (!PyArg_ParseTupleAndKeywords(args, kwargs, "Oi|ii:RenderTriangles", (char **)kwlist, &vao, &count, &first, &instances)) {
		PyErr_SetString(ModuleError, "ecgrpvbf");
		return 0;
	}

	if (!PyObject_TypeCheck((PyObject *)vao, &VertexArrayType)) {
		PyErr_SetString(ModuleError, "caoypwbf");
		return 0;
	}

	ModernGL::RenderTriangles(vao->vao, count, first, instances);
	Py_RETURN_NONE;
}

PyObject * RenderTriangleStrip(PyObject * self, PyObject * args, PyObject * kwargs) {
	VertexArray * vao;
	int count;
	int first = 0;
	int instances = 1;

	static const char * kwlist[] = {"vao", "count", "first", "instances", 0};

	if (!PyArg_ParseTupleAndKeywords(args, kwargs, "Oi|ii:RenderTriangleStrip", (char **)kwlist, &vao, &count, &first, &instances)) {
		PyErr_SetString(ModuleError, "kpmfixzn");
		return 0;
	}

	if (!PyObject_TypeCheck((PyObject *)vao, &VertexArrayType)) {
		PyErr_SetString(ModuleError, "caoypwbf");
		return 0;
	}

	ModernGL::RenderTriangleStrip(vao->vao, count, first, instances);
	Py_RETURN_NONE;
}

PyObject * RenderTriangleFan(PyObject * self, PyObject * args, PyObject * kwargs) {
	VertexArray * vao;
	int count;
	int first = 0;
	int instances = 1;

	static const char * kwlist[] = {"vao", "count", "first", "instances", 0};

	if (!PyArg_ParseTupleAndKeywords(args, kwargs, "Oi|ii:RenderTriangleFan", (char **)kwlist, &vao, &count, &first, &instances)) {
		PyErr_SetString(ModuleError, "yiajmwnl");
		return 0;
	}

	if (!PyObject_TypeCheck((PyObject *)vao, &VertexArrayType)) {
		PyErr_SetString(ModuleError, "caoypwbf");
		return 0;
	}

	ModernGL::RenderTriangleFan(vao->vao, count, first, instances);
	Py_RETURN_NONE;
}

PyObject * RenderLines(PyObject * self, PyObject * args, PyObject * kwargs) {
	VertexArray * vao;
	int count;
	int first = 0;
	int instances = 1;

	static const char * kwlist[] = {"vao", "count", "first", "instances", 0};

	if (!PyArg_ParseTupleAndKeywords(args, kwargs, "Oi|ii:RenderLines", (char **)kwlist, &vao, &count, &first, &instances)) {
		PyErr_SetString(ModuleError, "invoulsq");
		return 0;
	}

	if (!PyObject_TypeCheck((PyObject *)vao, &VertexArrayType)) {
		PyErr_SetString(ModuleError, "caoypwbf");
		return 0;
	}

	ModernGL::RenderLines(vao->vao, count, first, instances);
	Py_RETURN_NONE;
}

PyObject * RenderLineStrip(PyObject * self, PyObject * args, PyObject * kwargs) {
	VertexArray * vao;
	int count;
	int first = 0;
	int instances = 1;

	static const char * kwlist[] = {"vao", "count", "first", "instances", 0};

	if (!PyArg_ParseTupleAndKeywords(args, kwargs, "Oi|ii:RenderLineStrip", (char **)kwlist, &vao, &count, &first, &instances)) {
		PyErr_SetString(ModuleError, "xloesbac");
		return 0;
	}

	if (!PyObject_TypeCheck((PyObject *)vao, &VertexArrayType)) {
		PyErr_SetString(ModuleError, "caoypwbf");
		return 0;
	}

	ModernGL::RenderLineStrip(vao->vao, count, first, instances);
	Py_RETURN_NONE;
}

PyObject * RenderLineLoop(PyObject * self, PyObject * args, PyObject * kwargs) {
	VertexArray * vao;
	int count;
	int first = 0;
	int instances = 1;

	static const char * kwlist[] = {"vao", "count", "first", "instances", 0};

	if (!PyArg_ParseTupleAndKeywords(args, kwargs, "Oi|ii:RenderLineLoop", (char **)kwlist, &vao, &count, &first, &instances)) {
		PyErr_SetString(ModuleError, "lcieazvy");
		return 0;
	}

	if (!PyObject_TypeCheck((PyObject *)vao, &VertexArrayType)) {
		PyErr_SetString(ModuleError, "caoypwbf");
		return 0;
	}

	ModernGL::RenderLineLoop(vao->vao, count, first, instances);
	Py_RETURN_NONE;
}

PyObject * RenderPoints(PyObject * self, PyObject * args, PyObject * kwargs) {
	VertexArray * vao;
	int count;
	int first = 0;
	int instances = 1;

	static const char * kwlist[] = {"vao", "count", "first", "instances", 0};

	if (!PyArg_ParseTupleAndKeywords(args, kwargs, "Oi|ii:RenderPoints", (char **)kwlist, &vao, &count, &first, &instances)) {
		PyErr_SetString(ModuleError, "qpkxbatg");
		return 0;
	}

	if (!PyObject_TypeCheck((PyObject *)vao, &VertexArrayType)) {
		PyErr_SetString(ModuleError, "caoypwbf");
		return 0;
	}

	ModernGL::RenderPoints(vao->vao, count, first, instances);
	Py_RETURN_NONE;
}

PyObject * RenderLineStripAdjacency(PyObject * self, PyObject * args, PyObject * kwargs) {
	VertexArray * vao;
	int count;
	int first = 0;
	int instances = 1;

	static const char * kwlist[] = {"vao", "count", "first", "instances", 0};

	if (!PyArg_ParseTupleAndKeywords(args, kwargs, "Oi|ii:RenderLineStripAdjacency", (char **)kwlist, &vao, &count, &first, &instances)) {
		PyErr_SetString(ModuleError, "eyljxcdl");
		return 0;
	}

	if (!PyObject_TypeCheck((PyObject *)vao, &VertexArrayType)) {
		PyErr_SetString(ModuleError, "caoypwbf");
		return 0;
	}

	ModernGL::RenderLineStripAdjacency(vao->vao, count, first, instances);
	Py_RETURN_NONE;
}

PyObject * RenderLinesAdjacency(PyObject * self, PyObject * args, PyObject * kwargs) {
	VertexArray * vao;
	int count;
	int first = 0;
	int instances = 1;

	static const char * kwlist[] = {"vao", "count", "first", "instances", 0};

	if (!PyArg_ParseTupleAndKeywords(args, kwargs, "Oi|ii:RenderLinesAdjacency", (char **)kwlist, &vao, &count, &first, &instances)) {
		PyErr_SetString(ModuleError, "rcghsiwd");
		return 0;
	}

	if (!PyObject_TypeCheck((PyObject *)vao, &VertexArrayType)) {
		PyErr_SetString(ModuleError, "caoypwbf");
		return 0;
	}

	ModernGL::RenderLinesAdjacency(vao->vao, count, first, instances);
	Py_RETURN_NONE;
}

PyObject * RenderTriangleStripAdjacency(PyObject * self, PyObject * args, PyObject * kwargs) {
	VertexArray * vao;
	int count;
	int first = 0;
	int instances = 1;

	static const char * kwlist[] = {"vao", "count", "first", "instances", 0};

	if (!PyArg_ParseTupleAndKeywords(args, kwargs, "Oi|ii:RenderTriangleStripAdjacency", (char **)kwlist, &vao, &count, &first, &instances)) {
		PyErr_SetString(ModuleError, "jbdnihco");
		return 0;
	}

	if (!PyObject_TypeCheck((PyObject *)vao, &VertexArrayType)) {
		PyErr_SetString(ModuleError, "caoypwbf");
		return 0;
	}

	ModernGL::RenderTriangleStripAdjacency(vao->vao, count, first, instances);
	Py_RETURN_NONE;
}

PyObject * RenderTrianglesAdjacency(PyObject * self, PyObject * args, PyObject * kwargs) {
	VertexArray * vao;
	int count;
	int first = 0;
	int instances = 1;

	static const char * kwlist[] = {"vao", "count", "first", "instances", 0};

	if (!PyArg_ParseTupleAndKeywords(args, kwargs, "Oi|ii:RenderTrianglesAdjacency", (char **)kwlist, &vao, &count, &first, &instances)) {
		PyErr_SetString(ModuleError, "swtnjvxk");
		return 0;
	}

	if (!PyObject_TypeCheck((PyObject *)vao, &VertexArrayType)) {
		PyErr_SetString(ModuleError, "caoypwbf");
		return 0;
	}

	ModernGL::RenderTrianglesAdjacency(vao->vao, count, first, instances);
	Py_RETURN_NONE;
}

PyObject * RenderIndexedTriangles(PyObject * self, PyObject * args, PyObject * kwargs) {
	VertexArray * vao;
	int count;
	int first = 0;
	int instances = 1;

	static const char * kwlist[] = {"vao", "count", "first", "instances", 0};

	if (!PyArg_ParseTupleAndKeywords(args, kwargs, "Oi|ii:RenderIndexedTriangles", (char **)kwlist, &vao, &count, &first, &instances)) {
		PyErr_SetString(ModuleError, "hcorzxjl");
		return 0;
	}

	if (!PyObject_TypeCheck((PyObject *)vao, &VertexArrayType)) {
		PyErr_SetString(ModuleError, "caoypwbf");
		return 0;
	}

	ModernGL::RenderIndexedTriangles(vao->vao, count, first, instances);
	Py_RETURN_NONE;
}

PyObject * RenderIndexedTriangleStrip(PyObject * self, PyObject * args, PyObject * kwargs) {
	VertexArray * vao;
	int count;
	int first = 0;
	int instances = 1;

	static const char * kwlist[] = {"vao", "count", "first", "instances", 0};

	if (!PyArg_ParseTupleAndKeywords(args, kwargs, "Oi|ii:RenderIndexedTriangleStrip", (char **)kwlist, &vao, &count, &first, &instances)) {
		PyErr_SetString(ModuleError, "clwgvaoj");
		return 0;
	}

	if (!PyObject_TypeCheck((PyObject *)vao, &VertexArrayType)) {
		PyErr_SetString(ModuleError, "caoypwbf");
		return 0;
	}

	ModernGL::RenderIndexedTriangleStrip(vao->vao, count, first, instances);
	Py_RETURN_NONE;
}

PyObject * RenderIndexedTriangleFan(PyObject * self, PyObject * args, PyObject * kwargs) {
	VertexArray * vao;
	int count;
	int first = 0;
	int instances = 1;

	static const char * kwlist[] = {"vao", "count", "first", "instances", 0};

	if (!PyArg_ParseTupleAndKeywords(args, kwargs, "Oi|ii:RenderIndexedTriangleFan", (char **)kwlist, &vao, &count, &first, &instances)) {
		PyErr_SetString(ModuleError, "yenpgwic");
		return 0;
	}

	if (!PyObject_TypeCheck((PyObject *)vao, &VertexArrayType)) {
		PyErr_SetString(ModuleError, "caoypwbf");
		return 0;
	}

	ModernGL::RenderIndexedTriangleFan(vao->vao, count, first, instances);
	Py_RETURN_NONE;
}

PyObject * RenderIndexedLines(PyObject * self, PyObject * args, PyObject * kwargs) {
	VertexArray * vao;
	int count;
	int first = 0;
	int instances = 1;

	static const char * kwlist[] = {"vao", "count", "first", "instances", 0};

	if (!PyArg_ParseTupleAndKeywords(args, kwargs, "Oi|ii:RenderIndexedLines", (char **)kwlist, &vao, &count, &first, &instances)) {
		PyErr_SetString(ModuleError, "qltoasyl");
		return 0;
	}

	if (!PyObject_TypeCheck((PyObject *)vao, &VertexArrayType)) {
		PyErr_SetString(ModuleError, "caoypwbf");
		return 0;
	}

	ModernGL::RenderIndexedLines(vao->vao, count, first, instances);
	Py_RETURN_NONE;
}

PyObject * RenderIndexedLineStrip(PyObject * self, PyObject * args, PyObject * kwargs) {
	VertexArray * vao;
	int count;
	int first = 0;
	int instances = 1;

	static const char * kwlist[] = {"vao", "count", "first", "instances", 0};

	if (!PyArg_ParseTupleAndKeywords(args, kwargs, "Oi|ii:RenderIndexedLineStrip", (char **)kwlist, &vao, &count, &first, &instances)) {
		PyErr_SetString(ModuleError, "pwxzmqre");
		return 0;
	}

	if (!PyObject_TypeCheck((PyObject *)vao, &VertexArrayType)) {
		PyErr_SetString(ModuleError, "caoypwbf");
		return 0;
	}

	ModernGL::RenderIndexedLineStrip(vao->vao, count, first, instances);
	Py_RETURN_NONE;
}

PyObject * RenderIndexedLineLoop(PyObject * self, PyObject * args, PyObject * kwargs) {
	VertexArray * vao;
	int count;
	int first = 0;
	int instances = 1;

	static const char * kwlist[] = {"vao", "count", "first", "instances", 0};

	if (!PyArg_ParseTupleAndKeywords(args, kwargs, "Oi|ii:RenderIndexedLineLoop", (char **)kwlist, &vao, &count, &first, &instances)) {
		PyErr_SetString(ModuleError, "tfinleuv");
		return 0;
	}

	if (!PyObject_TypeCheck((PyObject *)vao, &VertexArrayType)) {
		PyErr_SetString(ModuleError, "caoypwbf");
		return 0;
	}

	ModernGL::RenderIndexedLineLoop(vao->vao, count, first, instances);
	Py_RETURN_NONE;
}

PyObject * RenderIndexedPoints(PyObject * self, PyObject * args, PyObject * kwargs) {
	VertexArray * vao;
	int count;
	int first = 0;
	int instances = 1;

	static const char * kwlist[] = {"vao", "count", "first", "instances", 0};

	if (!PyArg_ParseTupleAndKeywords(args, kwargs, "Oi|ii:RenderIndexedPoints", (char **)kwlist, &vao, &count, &first, &instances)) {
		PyErr_SetString(ModuleError, "dzqutosc");
		return 0;
	}

	if (!PyObject_TypeCheck((PyObject *)vao, &VertexArrayType)) {
		PyErr_SetString(ModuleError, "caoypwbf");
		return 0;
	}

	ModernGL::RenderIndexedPoints(vao->vao, count, first, instances);
	Py_RETURN_NONE;
}

PyObject * RenderIndexedLineStripAdjacency(PyObject * self, PyObject * args, PyObject * kwargs) {
	VertexArray * vao;
	int count;
	int first = 0;
	int instances = 1;

	static const char * kwlist[] = {"vao", "count", "first", "instances", 0};

	if (!PyArg_ParseTupleAndKeywords(args, kwargs, "Oi|ii:RenderIndexedLineStripAdjacency", (char **)kwlist, &vao, &count, &first, &instances)) {
		PyErr_SetString(ModuleError, "xzcmaikw");
		return 0;
	}

	if (!PyObject_TypeCheck((PyObject *)vao, &VertexArrayType)) {
		PyErr_SetString(ModuleError, "caoypwbf");
		return 0;
	}

	ModernGL::RenderIndexedLineStripAdjacency(vao->vao, count, first, instances);
	Py_RETURN_NONE;
}

PyObject * RenderIndexedLinesAdjacency(PyObject * self, PyObject * args, PyObject * kwargs) {
	VertexArray * vao;
	int count;
	int first = 0;
	int instances = 1;

	static const char * kwlist[] = {"vao", "count", "first", "instances", 0};

	if (!PyArg_ParseTupleAndKeywords(args, kwargs, "Oi|ii:RenderIndexedLinesAdjacency", (char **)kwlist, &vao, &count, &first, &instances)) {
		PyErr_SetString(ModuleError, "xnlgisyz");
		return 0;
	}

	if (!PyObject_TypeCheck((PyObject *)vao, &VertexArrayType)) {
		PyErr_SetString(ModuleError, "caoypwbf");
		return 0;
	}

	ModernGL::RenderIndexedLinesAdjacency(vao->vao, count, first, instances);
	Py_RETURN_NONE;
}

PyObject * RenderIndexedTriangleStripAdjacency(PyObject * self, PyObject * args, PyObject * kwargs) {
	VertexArray * vao;
	int count;
	int first = 0;
	int instances = 1;

	static const char * kwlist[] = {"vao", "count", "first", "instances", 0};

	if (!PyArg_ParseTupleAndKeywords(args, kwargs, "Oi|ii:RenderIndexedTriangleStripAdjacency", (char **)kwlist, &vao, &count, &first, &instances)) {
		PyErr_SetString(ModuleError, "ecygoziv");
		return 0;
	}

	if (!PyObject_TypeCheck((PyObject *)vao, &VertexArrayType)) {
		PyErr_SetString(ModuleError, "caoypwbf");
		return 0;
	}

	ModernGL::RenderIndexedTriangleStripAdjacency(vao->vao, count, first, instances);
	Py_RETURN_NONE;
}

PyObject * RenderIndexedTrianglesAdjacency(PyObject * self, PyObject * args, PyObject * kwargs) {
	VertexArray * vao;
	int count;
	int first = 0;
	int instances = 1;

	static const char * kwlist[] = {"vao", "count", "first", "instances", 0};

	if (!PyArg_ParseTupleAndKeywords(args, kwargs, "Oi|ii:RenderIndexedTrianglesAdjacency", (char **)kwlist, &vao, &count, &first, &instances)) {
		PyErr_SetString(ModuleError, "hxodprlg");
		return 0;
	}

	if (!PyObject_TypeCheck((PyObject *)vao, &VertexArrayType)) {
		PyErr_SetString(ModuleError, "caoypwbf");
		return 0;
	}

	ModernGL::RenderIndexedTrianglesAdjacency(vao->vao, count, first, instances);
	Py_RETURN_NONE;
}

PyObject * NewFramebuffer(PyObject * self, PyObject * args, PyObject * kwargs) {
	int width = 0;
	int height = 0;

	static const char * kwlist[] = {"width", "height", 0};

	if (!PyArg_ParseTupleAndKeywords(args, kwargs, "|ii:NewFramebuffer", (char **)kwlist, &width, &height)) {
		PyErr_SetString(ModuleError, "mnkbvopc");
		return 0;
	}

	ModernGL::Framebuffer framebuffer = ModernGL::NewFramebuffer(width, height);
	return Py_BuildValue("iii", framebuffer.framebuffer, framebuffer.color, framebuffer.depth);
}

PyObject * DeleteFramebuffer(PyObject * self, PyObject * args) {
	int framebuffer;

	if (!PyArg_ParseTuple(args, "i:DeleteFramebuffer", &framebuffer)) {
		PyErr_SetString(ModuleError, "arvgifqk");
		return 0;
	}

	ModernGL::DeleteFramebuffer(framebuffer);
	Py_RETURN_NONE;
}

PyObject * UseFramebuffer(PyObject * self, PyObject * args) {
	int framebuffer;

	if (!PyArg_ParseTuple(args, "i:UseFramebuffer", &framebuffer)) {
		PyErr_SetString(ModuleError, "aklfjcve");
		return 0;
	}

	ModernGL::UseFramebuffer(framebuffer);
	Py_RETURN_NONE;
}

PyObject * GetDefaultFramebuffer(PyObject * self, PyObject * args) {
	if (!PyArg_ParseTuple(args, ":GetDefaultFramebuffer")) {
		PyErr_SetString(ModuleError, "gjcfoblz");
		return 0;
	}

	ModernGL::GetDefaultFramebuffer();
	Py_RETURN_NONE;
}

PyObject * UseDefaultFramebuffer(PyObject * self, PyObject * args) {
	if (!PyArg_ParseTuple(args, ":UseDefaultFramebuffer")) {
		PyErr_SetString(ModuleError, "cvxbjigr");
		return 0;
	}

	ModernGL::UseDefaultFramebuffer();
	Py_RETURN_NONE;
}

PyObject * ReadPixels(PyObject * self, PyObject * args, PyObject * kwargs) {
	int x;
	int y;
	int width;
	int height;
	int components = 3;

	static const char * kwlist[] = {"x", "y", "width", "height", "components", 0};

	if (!PyArg_ParseTupleAndKeywords(args, kwargs, "iiii|i:ReadPixels", (char **)kwlist, &x, &y, &width, &height, &components)) {
		PyErr_SetString(ModuleError, "iucebofd");
		return 0;
	}

	int size = height * ((width * components + 3) & ~3);
	unsigned char * pixels = ModernGL::ReadPixels(x, y, width, height, components);
	PyObject * data = PyBytes_FromStringAndSize((const char *)pixels, size);
	free(pixels);

	return data;
}

PyObject * ReadDepthPixels(PyObject * self, PyObject * args, PyObject * kwargs) {
	int x;
	int y;
	int width;
	int height;

	static const char * kwlist[] = {"x", "y", "width", "height", 0};

	if (!PyArg_ParseTupleAndKeywords(args, kwargs, "iiii:ReadDepthPixels", (char **)kwlist, &x, &y, &width, &height)) {
		PyErr_SetString(ModuleError, "hwoxlqtp");
		return 0;
	}

	int size = height * height * 4;
	float * pixels = ModernGL::ReadDepthPixels(x, y, width, height);
	PyObject * data = PyBytes_FromStringAndSize((const char *)pixels, size);
	free(pixels);

	return data;
}

PyObject * ReadPixel(PyObject * self, PyObject * args, PyObject * kwargs) {
	int x;
	int y;

	static const char * kwlist[] = {"x", "y", 0};

	if (!PyArg_ParseTupleAndKeywords(args, kwargs, "ii:ReadPixel", (char **)kwlist, &x, &y)) {
		PyErr_SetString(ModuleError, "aqklwzjm");
		return 0;
	}

	return PyLong_FromUnsignedLong(ModernGL::ReadPixel(x, y));
}

PyObject * ReadDepthPixel(PyObject * self, PyObject * args, PyObject * kwargs) {
	int x;
	int y;

	static const char * kwlist[] = {"x", "y", 0};

	if (!PyArg_ParseTupleAndKeywords(args, kwargs, "ii:ReadDepthPixel", (char **)kwlist, &x, &y)) {
		PyErr_SetString(ModuleError, "jmyulkio");
		return 0;
	}

	return PyFloat_FromDouble(ModernGL::ReadDepthPixel(x, y));
}

PyObject * UseTextureAsImage(PyObject * self, PyObject * args, PyObject * kwargs) {
	int texture;
	int binding = 0;
	int components = 3;

	static const char * kwlist[] = {"texture", "binding", "components", 0};

	if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i|ii:UseTextureAsImage", (char **)kwlist, &texture, &binding, &components)) {
		PyErr_SetString(ModuleError, "uyvpencs");
		return 0;
	}

	ModernGL::UseTextureAsImage(texture, binding, components);
	Py_RETURN_NONE;
}

PyObject * NewTessEvaluationShader(PyObject * self, PyObject * args) {
	const char * source;

	if (!PyArg_ParseTuple(args, "s:NewTessEvaluationShader", &source)) {
		PyErr_SetString(ModuleError, "mgblcrdv");
		return 0;
	}

	return PyLong_FromLong(ModernGL::NewTessEvaluationShader(source));
}

PyObject * NewTessControlShader(PyObject * self, PyObject * args) {
	const char * source;

	if (!PyArg_ParseTuple(args, "s:NewTessControlShader", &source)) {
		PyErr_SetString(ModuleError, "zibhluoy");
		return 0;
	}

	return PyLong_FromLong(ModernGL::NewTessControlShader(source));
}

PyObject * NewComputeShader(PyObject * self, PyObject * args) {
	const char * source;

	if (!PyArg_ParseTuple(args, "s:NewComputeShader", &source)) {
		PyErr_SetString(ModuleError, "gzcndblk");
		return 0;
	}

	return PyLong_FromLong(ModernGL::NewComputeShader(source));
}

PyObject * DeleteComputeShader(PyObject * self, PyObject * args) {
	int program;

	if (!PyArg_ParseTuple(args, "i:DeleteComputeShader", &program)) {
		PyErr_SetString(ModuleError, "fagrulke");
		return 0;
	}

	ModernGL::DeleteComputeShader(program);
	Py_RETURN_NONE;
}

PyObject * RunComputeShader(PyObject * self, PyObject * args, PyObject * kwargs) {
	int program;
	int x = 1;
	int y = 1;
	int z = 1;

	static const char * kwlist[] = {"program", "x", "y", "z", 0};

	if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i|iii:RunComputeShader", (char **)kwlist, &program, &x, &y, &z)) {
		PyErr_SetString(ModuleError, "binlkwlv");
		return 0;
	}

	ModernGL::RunComputeShader(program, x, y, z);
	Py_RETURN_NONE;
}

PyObject * NewStorageBuffer(PyObject * self, PyObject * args) {
	const void * data;
	int size;

	if (!PyArg_ParseTuple(args, "y#:NewStorageBuffer", &data, &size)) {
		PyErr_SetString(ModuleError, "bqxjvkll");
		return 0;
	}

	return PyLong_FromLong(ModernGL::NewStorageBuffer(data, size));
}

PyObject * NewDynamicStorageBuffer(PyObject * self, PyObject * args) {
	const void * data;
	int size;

	if (!PyArg_ParseTuple(args, "y#:NewDynamicStorageBuffer", &data, &size)) {
		PyErr_SetString(ModuleError, "fugqsblx");
		return 0;
	}

	return PyLong_FromLong(ModernGL::NewDynamicStorageBuffer(data, size));
}

PyObject * UpdateStorageBuffer(PyObject * self, PyObject * args, PyObject * kwargs) {
	int buffer;
	int offset;
	const void * data;
	int size;

	static const char * kwlist[] = {"buffer", "offset", "data", 0};

	if (!PyArg_ParseTupleAndKeywords(args, kwargs, "iiy#:UpdateStorageBuffer", (char **)kwlist, &buffer, &offset, &data, &size)) {
		PyErr_SetString(ModuleError, "upgqxyha");
		return 0;
	}

	ModernGL::UpdateStorageBuffer(buffer, offset, data, size);
	Py_RETURN_NONE;
}

PyObject * UseStorageBuffer(PyObject * self, PyObject * args, PyObject * kwargs) {
	int buffer;
	int binding = 0;

	static const char * kwlist[] = {"buffer", "binding", 0};

	if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i|i:UseStorageBuffer", (char **)kwlist, &buffer, &binding)) {
		PyErr_SetString(ModuleError, "vowsaubd");
		return 0;
	}

	ModernGL::UseStorageBuffer(buffer, binding);
	Py_RETURN_NONE;
}

PyObject * ReadStorageBuffer(PyObject * self, PyObject * args, PyObject * kwargs) {
	int buffer;
	int offset;
	int size;

	static const char * kwlist[] = {"buffer", "offset", "size", 0};

	if (!PyArg_ParseTupleAndKeywords(args, kwargs, "iii:ReadStorageBuffer", (char **)kwlist, &buffer, &offset, &size)) {
		PyErr_SetString(ModuleError, "omjpsgqz");
		return 0;
	}

	void * content = ModernGL::ReadStorageBuffer(buffer, offset, size);
	if (!content) {
		PyErr_SetString(ModuleError, "yrhzkblw");
		return 0;
	}
	
	PyObject * data = PyBytes_FromStringAndSize((const char *)content, size);
	free(content);

	return data;
}

PyObject * Dummy(PyObject * self, PyObject * args) {
	PyErr_SetString(ModuleError, "Module not initialized.\n\nCall InitializeModernGL() first.\n\n");
	return 0;
}

PyObject * DummyExtension(PyObject * self, PyObject * args) {
	if (initialized) {
		PyErr_SetString(ModuleError, "Extension not initialized.\n\nCall ExtensionActive() to test the full extension support.\n\n");
	} else {
		PyErr_SetString(ModuleError, "Module not initialized.\n\nCall InitializeModernGL() first.\n\n");
	}
	return 0;
}

static PyMethodDef methods[] = {
	{
		"InitializeModernGL",
		InitializeModernGL,
		METH_VARARGS,
		"Initialize the ModernGL module inside a valid OpenGL context.\n"
		"A valid OpenGL context must exists before the function call.\n"

		"\n"
		"Parameters:\n"
		"\tNone\n"

		"\n"
		"Returns:\n"
		"\tokey (bool) True on success, False on failure.\n"
		"\n"
	},
	{
		"ExtensionActive",
		ExtensionActive,
		METH_VARARGS,
		"Check for full ModernGL support.\n"
		"The initialization of the extensions are not affected by this method.\n"

		"\n"
		"Parameters:\n"
		"\tNone\n"

		"\n"
		"Returns:\n"
		"\tactive (bool) True on supported extensions, False otherwise.\n"
		"\n"
	},
	{
		"GetError",
		GetError,
		METH_VARARGS,
		"Get the error when Initialization failed.\n"

		"\n"
		"Parameters:\n"
		"\tNone\n"

		"\n"
		"Returns:\n"
		"\terror (str) The reason, why the InitializeModernGL failed.\n"
		"\n"
	},

	{
		"GetInfo",
		(PyCFunction)Dummy, // GetInfo,
		METH_VARARGS,
		"Get information about the OpenGL context.\n"

		"\n"
		"Parameters:\n"
		"\tNone\n"

		"\n"
		"Returns:\n"
		"\tmajor (int) The major OpenGL version.\n"
		"\tminor (int) The minor OpenGL version.\n"
		"\tsamples (int) The samples supported by the default framebuffer.\n"
		"\tvendor (int) The vendor.\n"
		"\trenderer (int) The renderer.\n"
		"\n"
	},
	{
		"Viewport",
		(PyCFunction)Dummy, // Viewport,
		METH_VARARGS | METH_KEYWORDS,
		"Set the viewport for rendering.\n"

		"\n"
		"Parameters:\n"
		"\tx (int) Position of the viewport.\n"
		"\ty (int) Position of the viewport.\n"
		"\twidth (int) Width of the viewport.\n"
		"\theight (int) Height of the viewport.\n"

		"\n"
		"Returns:\n"
		"\tNone\n"
		"\n"
	},
	{
		"Clear",
		(PyCFunction)Dummy, // Clear,
		METH_VARARGS | METH_KEYWORDS,
		"Clear the viewport with the specified colors.\n"
		"Also clears the depth attachments.\n"

		"\n"
		"Parameters:\n"
		"\tr (int) Clear value for the red channel. By default is 0\n"
		"\tg (int) Clear value for the green channel. By default is 0\n"
		"\tb (int) Clear value for the blue channel. By default is 0\n"
		"\ta (int) Clear value for the alpha channel. By default is 255\n"

		"\n"
		"Returns:\n"
		"\tNone\n"
		"\n"
	},
	{
		"PointSize",
		(PyCFunction)Dummy, // PointSize,
		METH_VARARGS,
		"Set the size of the point primitive.\n"

		"\n"
		"Parameters:\n"
		"\tsize (float) Size of the point.\n"

		"\n"
		"Returns:\n"
		"\tNone\n"
		"\n"
	},
	{
		"LineSize",
		(PyCFunction)Dummy, // LineSize,
		METH_VARARGS,
		"Set the with of the line primitive.\n"

		"\n"
		"Parameters:\n"
		"\tsize (float) Width of the line.\n"

		"\n"
		"Returns:\n"
		"\tNone\n"
		"\n"
	},
	{
		"EnableOnly",
		(PyCFunction)Dummy, // EnableOnly,
		METH_VARARGS,
		"Enables only the specified flags.\n"
		"The enable flags are: ENABLE_NOTHING, ENABLE_BLEND, ENABLE_DEPTH_TEST, ENABLE_CULL_FACE and ENABLE_MULTISAMPLE.\n"

		"\n"
		"Parameters:\n"
		"\tflags (int) A combination of the enable flags using bitwise OR operator.\n"

		"\n"
		"Returns:\n"
		"\tNone\n"
		"\n"
	},
	{
		"EnableBlend",
		(PyCFunction)Dummy, // EnableBlend,
		METH_VARARGS,
		"Enable blending.\n"

		"\n"
		"Parameters:\n"
		"\tNone\n"

		"\n"
		"Returns:\n"
		"\tNone\n"
		"\n"
	},
	{
		"DisableBlend",
		(PyCFunction)Dummy, // DisableBlend,
		METH_VARARGS,
		"Disable blending.\n"

		"\n"
		"Parameters:\n"
		"\tNone\n"

		"\n"
		"Returns:\n"
		"\tNone\n"
		"\n"
	},
	{
		"EnableCullFace",
		(PyCFunction)Dummy, // EnableCullFace,
		METH_VARARGS,
		"Enable face culling.\n"

		"\n"
		"Parameters:\n"
		"\tNone\n"

		"\n"
		"Returns:\n"
		"\tNone\n"
		"\n"
	},
	{
		"DisableCullFace",
		(PyCFunction)Dummy, // DisableCullFace,
		METH_VARARGS,
		"Disable face culling.\n"

		"\n"
		"Parameters:\n"
		"\tNone\n"

		"\n"
		"Returns:\n"
		"\tNone\n"
		"\n"
	},
	{
		"EnableDepthTest",
		(PyCFunction)Dummy, // EnableDepthTest,
		METH_VARARGS,
		"Enable depth testing.\n"

		"\n"
		"Parameters:\n"
		"\tNone\n"

		"\n"
		"Returns:\n"
		"\tNone\n"
		"\n"
	},
	{
		"DisableDepthTest",
		(PyCFunction)Dummy, // DisableDepthTest,
		METH_VARARGS,
		"Disable depth testing.\n"

		"\n"
		"Parameters:\n"
		"\tNone\n"

		"\n"
		"Returns:\n"
		"\tNone\n"
		"\n"
	},
	{
		"EnableMultisample",
		(PyCFunction)Dummy, // EnableMultisample,
		METH_VARARGS,
		"Enable multisampling.\n"

		"\n"
		"Parameters:\n"
		"\tNone\n"

		"\n"
		"Returns:\n"
		"\tNone\n"
		"\n"
	},
	{
		"DisableMultisample",
		(PyCFunction)Dummy, // DisableMultisample,
		METH_VARARGS,
		"Disable multisampling.\n"

		"\n"
		"Parameters:\n"
		"\tNone\n"

		"\n"
		"Returns:\n"
		"\tNone\n"
		"\n"
	},
	{
		"NewVertexShader",
		(PyCFunction)Dummy, // NewVertexShader,
		METH_VARARGS,
		""

		"\n"
		"Parameters:\n"
		"\tsource (str) Source code in GLSL.\n"

		"\n"
		"Returns:\n"
		"\tshader (int) The index of the new shader object.\n"
		"\n"
	},
	{
		"NewFragmentShader",
		(PyCFunction)Dummy, // NewFragmentShader,
		METH_VARARGS,
		""

		"\n"
		"Parameters:\n"
		"\tsource (str) Source code in GLSL.\n"

		"\n"
		"Returns:\n"
		"\tshader (int) The index of the new shader object.\n"
		"\n"
	},
	{
		"NewGeometryShader",
		(PyCFunction)Dummy, // NewGeometryShader,
		METH_VARARGS,
		""

		"\n"
		"Parameters:\n"
		"\tsource (str) Source code in GLSL.\n"

		"\n"
		"Returns:\n"
		"\tshader (int) The index of the new shader object.\n"
		"\n"
	},
	{
		"DeleteShader",
		(PyCFunction)Dummy, // DeleteShader,
		METH_VARARGS,
		"Delete shader object created by the NewFragmentShader, the NewGeometryShader, the NewTessControlShader, the NewTessEvaluationShader or the NewVertexShader.\n"

		"\n"
		"Parameters:\n"
		"\tshader (int) Index of a shader object.\n"

		"\n"
		"Returns:\n"
		"\tNone\n"
		"\n"
	},
	{
		"NewProgram",
		(PyCFunction)Dummy, // NewProgram,
		METH_VARARGS,
		""

		"\n"
		"Parameters:\n"
		"\tshaders (list of ints) List containing shader indices.\n"

		"\n"
		"Returns:\n"
		"\tprogram (int) The index of the new program object.\n"
		"\n"
	},
	{
		"DeleteProgram",
		(PyCFunction)Dummy, // DeleteProgram,
		METH_VARARGS,
		""

		"\n"
		"Parameters:\n"
		"\tprogram (int) Index of a program object returned by the NewProgram function.\n"

		"\n"
		"Returns:\n"
		"\tNone\n"
		"\n"
	},
	{
		"UseProgram",
		(PyCFunction)Dummy, // UseProgram,
		METH_VARARGS,
		""

		"\n"
		"Parameters:\n"
		"\tprogram (int) Index of a program object returned by the NewProgram function.\n"

		"\n"
		"Returns:\n"
		"\tNone\n"
		"\n"
	},
	{
		"UseDefaultProgram",
		(PyCFunction)Dummy, // UseDefaultProgram,
		METH_VARARGS,
		""

		"\n"
		"Parameters:\n"
		"\tNone\n"

		"\n"
		"Returns:\n"
		"\tNone\n"
		"\n"
	},
	{
		"CompilerLog",
		(PyCFunction)Dummy, // CompilerLog,
		METH_VARARGS,
		"Get the compiler log for the following methods:\n"
		"NewFragmentShader\n"
		"NewGeometryShader\n"
		"NewVertexShader\n"
		"NewProgram\n"
		"NewTessEvaluationShader\n"
		"NewTessControlShader\n"
		"NewComputeShader\n"
		""

		"\n"
		"Parameters:\n"
		"\tNone\n"

		"\n"
		"Returns:\n"
		"\tlog (str) The GLSL compiler log.\n"
		"\n"
	},
	{
		"GetAttributeLocation",
		(PyCFunction)Dummy, // GetAttributeLocation,
		METH_VARARGS | METH_KEYWORDS,
		""

		"\n"
		"Parameters:\n"
		"\tprogram (int) Index of a program object returned by the NewProgram function.\n"
		"\tname (str) Name of the attribute.\n"

		"\n"
		"Returns:\n"
		"\tlocation (int) The location of the attribute.\n"
		"\n"
	},
	{
		"GetUniformLocation",
		(PyCFunction)Dummy, // GetUniformLocation,
		METH_VARARGS | METH_KEYWORDS,
		""

		"\n"
		"Parameters:\n"
		"\tprogram (int) Index of a program object returned by the NewProgram function.\n"
		"\tname (str) Name of the uniform.\n"

		"\n"
		"Returns:\n"
		"\tlocation (int) The location of the uniform.\n"
		"\n"
	},
	{
		"GetUniformBlockLocation",
		(PyCFunction)Dummy, // GetUniformBlockLocation,
		METH_VARARGS | METH_KEYWORDS,
		""

		"\n"
		"Parameters:\n"
		"\tprogram (int) Index of a program object returned by the NewProgram function.\n"
		"\tname (str) Name of the uniform block.\n"

		"\n"
		"Returns:\n"
		"\tlocation (int) The location of the uniform block.\n"
		"\n"
	},
	{
		"Uniform1f",
		(PyCFunction)Dummy, // Uniform1f,
		METH_VARARGS,
		"Set the value of the uniform.\n"
		"The value must have the type of `float` in the shader.\n"
		"The location of the uniform can be queried by the UniformLocation method.\n"


		"\n"
		"Parameters:\n"
		"\tlocation (int) Location of the uniform returned by the UniformLocation.\n"
		"\tv0 (float) Value to set.\n"

		"\n"
		"Returns:\n"
		"\tNone\n"
		"\n"
	},
	{
		"Uniform2f",
		(PyCFunction)Dummy, // Uniform2f,
		METH_VARARGS,
		"Set the value of the uniform.\n"
		"The value must have the type of `vec2` in the shader.\n"
		"The location of the uniform can be queried by the UniformLocation method.\n"


		"\n"
		"Parameters:\n"
		"\tlocation (int) Location of the uniform returned by the UniformLocation.\n"
		"\tv0 (float) Value to set.\n"
		"\tv1 (float) Value to set.\n"

		"\n"
		"Returns:\n"
		"\tNone\n"
		"\n"
	},
	{
		"Uniform3f",
		(PyCFunction)Dummy, // Uniform3f,
		METH_VARARGS,
		"Set the value of the uniform.\n"
		"The value must have the type of `vec3` in the shader.\n"
		"The location of the uniform can be queried by the UniformLocation method.\n"


		"\n"
		"Parameters:\n"
		"\tlocation (int) Location of the uniform returned by the UniformLocation.\n"
		"\tv0 (float) Value to set.\n"
		"\tv1 (float) Value to set.\n"
		"\tv2 (float) Value to set.\n"

		"\n"
		"Returns:\n"
		"\tNone\n"
		"\n"
	},
	{
		"Uniform4f",
		(PyCFunction)Dummy, // Uniform4f,
		METH_VARARGS,
		"Set the value of the uniform.\n"
		"The value must have the type of `vec4` in the shader.\n"
		"The location of the uniform can be queried by the UniformLocation method.\n"


		"\n"
		"Parameters:\n"
		"\tlocation (int) Location of the uniform returned by the UniformLocation.\n"
		"\tv0 (float) Value to set.\n"
		"\tv1 (float) Value to set.\n"
		"\tv2 (float) Value to set.\n"
		"\tv3 (float) Value to set.\n"

		"\n"
		"Returns:\n"
		"\tNone\n"
		"\n"
	},
	{
		"Uniform1i",
		(PyCFunction)Dummy, // Uniform1i,
		METH_VARARGS,
		"Set the value of the uniform.\n"
		"The value must have the type of `int` in the shader.\n"
		"The location of the uniform can be queried by the UniformLocation method.\n"


		"\n"
		"Parameters:\n"
		"\tlocation (int) Location of the uniform returned by the UniformLocation.\n"
		"\tv0 (int) Value to set.\n"


		"\n"
		"Returns:\n"
		"\tNone\n"
		"\n"
	},
	{
		"Uniform2i",
		(PyCFunction)Dummy, // Uniform2i,
		METH_VARARGS,
		"Set the value of the uniform.\n"
		"The value must have the type of `ivec2` in the shader.\n"
		"The location of the uniform can be queried by the UniformLocation method.\n"


		"\n"
		"Parameters:\n"
		"\tlocation (int) Location of the uniform returned by the UniformLocation.\n"
		"\tv0 (int) Value to set.\n"
		"\tv1 (int) Value to set.\n"

		"\n"
		"Returns:\n"
		"\tNone\n"
		"\n"
	},
	{
		"Uniform3i",
		(PyCFunction)Dummy, // Uniform3i,
		METH_VARARGS,
		"Set the value of the uniform.\n"
		"The value must have the type of `ivec3` in the shader.\n"
		"The location of the uniform can be queried by the UniformLocation method.\n"


		"\n"
		"Parameters:\n"
		"\tlocation (int) Location of the uniform returned by the UniformLocation.\n"
		"\tv0 (int) Value to set.\n"
		"\tv1 (int) Value to set.\n"
		"\tv2 (int) Value to set.\n"

		"\n"
		"Returns:\n"
		"\tNone\n"
		"\n"
	},
	{
		"Uniform4i",
		(PyCFunction)Dummy, // Uniform4i,
		METH_VARARGS,
		"Set the value of the uniform.\n"
		"The value must have the type of `ivec4` in the shader.\n"
		"The location of the uniform can be queried by the UniformLocation method.\n"


		"\n"
		"Parameters:\n"
		"\tlocation (int) Location of the uniform returned by the UniformLocation.\n"
		"\tv0 (int) Value to set.\n"
		"\tv1 (int) Value to set.\n"
		"\tv2 (int) Value to set.\n"
		"\tv3 (int) Value to set.\n"

		"\n"
		"Returns:\n"
		"\tNone\n"
		"\n"
	},
	{
		"UniformMatrix",
		(PyCFunction)Dummy, // UniformMatrix,
		METH_VARARGS,
		""

		"\n"
		"Parameters:\n"
		"\tlocation (int) Location of the uniform returned by the UniformLocation.\n"
		"\tmatrix (list of floats) List containing 4x4=16 float values.\n"

		"\n"
		"Returns:\n"
		"\tNone\n"
		"\n"
	},
	{
		"UniformTransposeMatrix",
		(PyCFunction)Dummy, // UniformTransposeMatrix,
		METH_VARARGS,
		""

		"\n"
		"Parameters:\n"
		"\tlocation (int) Location of the uniform returned by the UniformLocation.\n"
		"\tmatrix (list of floats) List containing 4x4=16 float values.\n"

		"\n"
		"Returns:\n"
		"\tNone\n"
		"\n"
	},
	{
		"UseUniformBlock",
		(PyCFunction)Dummy, // UseUniformBlock,
		METH_VARARGS | METH_KEYWORDS,
		""

		"\n"
		"Parameters:\n"
		"\tlocation (int) Location of the uniform returned by the UniformLocation.\n"
		"\tubo (int) Index of a uniform buffer returned by a NewUniformBuffer.\n"

		"\n"
		"Returns:\n"
		"\tNone\n"
		"\n"
	},
	{
		"NewTexture",
		(PyCFunction)Dummy, // NewTexture,
		METH_VARARGS | METH_KEYWORDS,
		""

		"\n"
		"Parameters:\n"
		"\twidth (int) Width of the texture.\n"
		"\theight (int) Height of the texture.\n"
		"\tpixels (bytes) Pixels stored in bytes.\n"
		"\tcomponents (int) By default is 3\n"

		"\n"
		"Returns:\n"
		"\ttexture (int) The index of the new texture object.\n"
		"\n"
	},
	{
		"DeleteTexture",
		(PyCFunction)Dummy, // DeleteTexture,
		METH_VARARGS,
		""

		"\n"
		"Parameters:\n"
		"\ttexture (int) Index of a texture returned by the NewTexture function.\n"

		"\n"
		"Returns:\n"
		"\tNone\n"
		"\n"
	},
	{
		"UpdateTexture",
		(PyCFunction)Dummy, // UpdateTexture,
		METH_VARARGS | METH_KEYWORDS,
		""

		"\n"
		"Parameters:\n"
		"\ttexture (int) Index of a texture returned by the NewTexture function.\n"
		"\tx (int) Offset of the new texture part.\n"
		"\ty (int) Offset of the new texture part.\n"
		"\twidth (int) Width of the texture.\n"
		"\theight (int) Height of the texture.\n"
		"\tpixels (bytes) Pixels stored in bytes.\n"
		"\tcomponents (int) By default is 3\n"

		"\n"
		"Returns:\n"
		"\tNone\n"
		"\n"
	},
	{
		"UseTexture",
		(PyCFunction)Dummy, // UseTexture,
		METH_VARARGS,
		""

		"\n"
		"Parameters:\n"
		"\ttexture (int) Index of a texture returned by the NewTexture function.\n"
		"\tlocation (int) Location of the texture. By default is 0\n"

		"\n"
		"Returns:\n"
		"\tNone\n"
		"\n"
	},
	{
		"SetTexturePixelated",
		(PyCFunction)Dummy, // SetTexturePixelated,
		METH_VARARGS,
		"Set texture filter to nearest.\n"

		"\n"
		"Parameters:\n"
		"\ttexture (int) Index of a texture returned by the NewTexture function.\n"

		"\n"
		"Returns:\n"
		"\tNone\n"
		"\n"
	},
	{
		"SetTextureFiltered",
		(PyCFunction)Dummy, // SetTextureFiltered,
		METH_VARARGS,
		"Set texture filter to linear.\n"

		"\n"
		"Parameters:\n"
		"\ttexture (int) Index of a texture returned by the NewTexture function.\n"

		"\n"
		"Returns:\n"
		"\tNone\n"
		"\n"
	},
	{
		"SetTextureMipmapped",
		(PyCFunction)Dummy, // SetTextureMipmapped,
		METH_VARARGS,
		"Set texture filter to mipmap linear.\n"

		"\n"
		"Parameters:\n"
		"\ttexture (int) Index of a texture returned by the NewTexture function.\n"

		"\n"
		"Returns:\n"
		"\tNone\n"
		"\n"
	},
	{
		"BuildMipmap",
		(PyCFunction)Dummy, // BuildMipmap,
		METH_VARARGS | METH_KEYWORDS,
		"Generate the mipmaps for the texture.\n"

		"\n"
		"Parameters:\n"
		"\ttexture (int) Index of a texture returned by the NewTexture function.\n"
		"\tbase (int) Base mipmap level to build.\n"
		"\tmax (int) Maximum mipmap level to build.\n"

		"\n"
		"Returns:\n"
		"\tNone\n"
		"\n"
	},
	{
		"NewVertexArray",
		(PyCFunction)Dummy, // NewVertexArray,
		METH_VARARGS,
		"The foreach int or float attribute an index of a vertex buffer object and the location of a vertex attribute must be specified.\n"

		"\n"
		"Parameters:\n"
		"\tformat (str) Format of the vertex array attrubites. ([1-4][if])+\n"
		"\tattribs (list of int pairs) List of vertex buffer object and vertex location pairs.\n"
		"\tibo (int) Index of an index buffer object. By default is 0\n"

		"\n"
		"Returns:\n"
		"\tvao (int) The index of the new vertex array object.\n"
		"\n"
	},
	{
		"DeleteVertexArray",
		(PyCFunction)Dummy, // DeleteVertexArray,
		METH_VARARGS,
		""
		"\n"
		"Parameters:\n"
		"\tNone\n"

		"\n"
		"Returns:\n"
		"\tNone\n"
		"\n"
	},
	{
		"EnableAttribute",
		(PyCFunction)Dummy, // EnableAttribute,
		METH_VARARGS | METH_KEYWORDS,
		"Enable an attribute in the vertex array object.\n"

		"\n"
		"Parameters:\n"
		"\tvao (int) The index of a vertex array object.\n"
		"\tattrib (int) The location of the vertex attribute returned by the GetAttributeLocation function.\n"

		"\n"
		"Returns:\n"
		"\tNone\n"
		"\n"
	},
	{
		"DisableAttribute",
		(PyCFunction)Dummy, // DisableAttribute,
		METH_VARARGS | METH_KEYWORDS,
		"Disable an attribute in the vertex array object.\n"

		"\n"
		"Parameters:\n"
		"\tvao (int) The index of a vertex array object.\n"
		"\tattrib (int) The location of the vertex attribute returned by the GetAttributeLocation function.\n"

		"\n"
		"Returns:\n"
		"\tNone\n"
		"\n"
	},
	{
		"EnableAttributes",
		(PyCFunction)Dummy, // EnableAttributes,
		METH_VARARGS | METH_KEYWORDS,
		"Enable attributes in the vertex array object.\n"

		"\n"
		"Parameters:\n"
		"\tvao (int) The index of a vertex array object.\n"
		"\tattribs (list of ints) The locations of the vertex attributes returned by the GetAttributeLocation function.\n"

		"\n"
		"Returns:\n"
		"\tNone\n"
		"\n"
	},
	{
		"DisableAttributes",
		(PyCFunction)Dummy, // DisableAttributes,
		METH_VARARGS | METH_KEYWORDS,
		"Disable attributes in the vertex array object.\n"

		"\n"
		"Parameters:\n"
		"\tvao (int) The index of a vertex array object.\n"
		"\tattribs (list of ints) The locations of the vertex attributes returned by the GetAttributeLocation function.\n"

		"\n"
		"Returns:\n"
		"\tNone\n"
		"\n"
	},
	{
		"NewVertexBuffer",
		(PyCFunction)Dummy, // NewVertexBuffer,
		METH_VARARGS,
		""

		"\n"
		"Parameters:\n"
		"\tdata (bytes) The content of the buffer.\n"

		"\n"
		"Returns:\n"
		"\tvbo (int) The index of the new vertex buffer object.\n"
		"\n"
	},
	{
		"NewIndexBuffer",
		(PyCFunction)Dummy, // NewIndexBuffer,
		METH_VARARGS,
		""

		"\n"
		"Parameters:\n"
		"\tdata (bytes) The content of the buffer.\n"

		"\n"
		"Returns:\n"
		"\tibo (int) The index of the new index buffer object.\n"
		"\n"
	},
	{
		"NewUniformBuffer",
		(PyCFunction)Dummy, // NewUniformBuffer,
		METH_VARARGS,
		""

		"\n"
		"Parameters:\n"
		"\tdata (bytes) The content of the buffer.\n"

		"\n"
		"Returns:\n"
		"\tubo (int) The index of the new uniform buffer object.\n"
		"\n"
	},
	{
		"NewDynamicVertexBuffer",
		(PyCFunction)Dummy, // NewDynamicVertexBuffer,
		METH_VARARGS,
		""

		"\n"
		"Parameters:\n"
		"\tdata (bytes) The content of the buffer.\n"

		"\n"
		"Returns:\n"
		"\tvbo (int) The index of the new vertex buffer object.\n"
		"\n"
	},
	{
		"NewDynamicIndexBuffer",
		(PyCFunction)Dummy, // NewDynamicIndexBuffer,
		METH_VARARGS,
		""

		"\n"
		"Parameters:\n"
		"\tdata (bytes) The content of the buffer.\n"

		"\n"
		"Returns:\n"
		"\tibo (int) The index of the new index buffer object.\n"
		"\n"
	},
	{
		"NewDynamicUniformBuffer",
		(PyCFunction)Dummy, // NewDynamicUniformBuffer,
		METH_VARARGS,
		""

		"\n"
		"Parameters:\n"
		"\tdata (bytes) The content of the buffer.\n"

		"\n"
		"Returns:\n"
		"\tubo (int) The index of the new uniform buffer object.\n"
		"\n"
	},
	{
		"DeleteVertexBuffer",
		(PyCFunction)Dummy, // DeleteVertexBuffer,
		METH_VARARGS,
		""

		"\n"
		"Parameters:\n"
		"\tbuffer (int) The index of any buffer object except the framebuffer object.\n"

		"\n"
		"Returns:\n"
		"\tNone\n"
		"\n"
	},
	{
		"DeleteIndexBuffer",
		(PyCFunction)Dummy, // DeleteIndexBuffer,
		METH_VARARGS,
		""

		"\n"
		"Parameters:\n"
		"\tbuffer (int) The index of any buffer object except the framebuffer object.\n"

		"\n"
		"Returns:\n"
		"\tNone\n"
		"\n"
	},
	{
		"DeleteUniformBuffer",
		(PyCFunction)Dummy, // DeleteUniformBuffer,
		METH_VARARGS,
		""

		"\n"
		"Parameters:\n"
		"\tbuffer (int) The index of any buffer object except the framebuffer object.\n"

		"\n"
		"Returns:\n"
		"\tNone\n"
		"\n"
	},
	{
		"UpdateVertexBuffer",
		(PyCFunction)Dummy, // UpdateVertexBuffer,
		METH_VARARGS | METH_KEYWORDS,
		""

		"\n"
		"Parameters:\n"
		"\tbuffer (int) The index of a vertex buffer object except the framebuffer object.\n"
		"\toffset (int) The offset of the data in the buffer to write.\n"
		"\tdata (bytes) The content of the data to write to the buffer.\n"

		"\n"
		"Returns:\n"
		"\tNone\n"
		"\n"
	},
	{
		"UpdateIndexBuffer",
		(PyCFunction)Dummy, // UpdateIndexBuffer,
		METH_VARARGS | METH_KEYWORDS,
		""

		"\n"
		"Parameters:\n"
		"\tbuffer (int) The index of an index buffer object except the framebuffer object.\n"
		"\toffset (int) The offset of the data in the buffer to write.\n"
		"\tdata (bytes) The content of the data to write to the buffer.\n"

		"\n"
		"Returns:\n"
		"\tNone\n"
		"\n"
	},
	{
		"UpdateUniformBuffer",
		(PyCFunction)Dummy, // UpdateUniformBuffer,
		METH_VARARGS | METH_KEYWORDS,
		""

		"\n"
		"Parameters:\n"
		"\tbuffer (int) The index of a uniform buffer object except the framebuffer object.\n"
		"\toffset (int) The offset of the data in the buffer to write.\n"
		"\tdata (bytes) The content of the data to write to the buffer.\n"

		"\n"
		"Returns:\n"
		"\tNone\n"
		"\n"
	},
	{
		"RenderTriangles",
		(PyCFunction)Dummy, // RenderTriangles,
		METH_VARARGS | METH_KEYWORDS,

		"\n"
		"Parameters:\n"
		"\tvao (int) The index of a vertex array object that will be used during the rendering.\n"
		"\tcount (int) Number of vertices to render.\n"
		"\tfirst (int) Index of the first vertex. By default is 0\n"
		"\tinstances (int) Number of instances. By default is 1\n"

		"\n"
		"Returns:\n"
		"\tNone\n"
		"\n"
	},
	{
		"RenderTriangleStrip",
		(PyCFunction)Dummy, // RenderTriangleStrip,
		METH_VARARGS | METH_KEYWORDS,

		"\n"
		"Parameters:\n"
		"\tvao (int) The index of a vertex array object that will be used during the rendering.\n"
		"\tcount (int) Number of vertices to render.\n"
		"\tfirst (int) Index of the first vertex. By default is 0\n"
		"\tinstances (int) Number of instances. By default is 1\n"

		"\n"
		"Returns:\n"
		"\tNone\n"
		"\n"
	},
	{
		"RenderTriangleFan",
		(PyCFunction)Dummy, // RenderTriangleFan,
		METH_VARARGS | METH_KEYWORDS,

		"\n"
		"Parameters:\n"
		"\tvao (int) The index of a vertex array object that will be used during the rendering.\n"
		"\tcount (int) Number of vertices to render.\n"
		"\tfirst (int) Index of the first vertex. By default is 0\n"
		"\tinstances (int) Number of instances. By default is 1\n"

		"\n"
		"Returns:\n"
		"\tNone\n"
		"\n"
	},
	{
		"RenderLines",
		(PyCFunction)Dummy, // RenderLines,
		METH_VARARGS | METH_KEYWORDS,

		"\n"
		"Parameters:\n"
		"\tvao (int) The index of a vertex array object that will be used during the rendering.\n"
		"\tcount (int) Number of vertices to render.\n"
		"\tfirst (int) Index of the first vertex. By default is 0\n"
		"\tinstances (int) Number of instances. By default is 1\n"

		"\n"
		"Returns:\n"
		"\tNone\n"
		"\n"
	},
	{
		"RenderLineStrip",
		(PyCFunction)Dummy, // RenderLineStrip,
		METH_VARARGS | METH_KEYWORDS,

		"\n"
		"Parameters:\n"
		"\tvao (int) The index of a vertex array object that will be used during the rendering.\n"
		"\tcount (int) Number of vertices to render.\n"
		"\tfirst (int) Index of the first vertex. By default is 0\n"
		"\tinstances (int) Number of instances. By default is 1\n"

		"\n"
		"Returns:\n"
		"\tNone\n"
		"\n"
	},
	{
		"RenderLineLoop",
		(PyCFunction)Dummy, // RenderLineLoop,
		METH_VARARGS | METH_KEYWORDS,

		"\n"
		"Parameters:\n"
		"\tvao (int) The index of a vertex array object that will be used during the rendering.\n"
		"\tcount (int) Number of vertices to render.\n"
		"\tfirst (int) Index of the first vertex. By default is 0\n"
		"\tinstances (int) Number of instances. By default is 1\n"

		"\n"
		"Returns:\n"
		"\tNone\n"
		"\n"
	},
	{
		"RenderPoints",
		(PyCFunction)Dummy, // RenderPoints,
		METH_VARARGS | METH_KEYWORDS,

		"\n"
		"Parameters:\n"
		"\tvao (int) The index of a vertex array object that will be used during the rendering.\n"
		"\tcount (int) Number of vertices to render.\n"
		"\tfirst (int) Index of the first vertex. By default is 0\n"
		"\tinstances (int) Number of instances. By default is 1\n"

		"\n"
		"Returns:\n"
		"\tNone\n"
		"\n"
	},
	{
		"RenderLineStripAdjacency",
		(PyCFunction)Dummy, // RenderLineStripAdjacency,
		METH_VARARGS | METH_KEYWORDS,

		"\n"
		"Parameters:\n"
		"\tvao (int) The index of a vertex array object that will be used during the rendering.\n"
		"\tcount (int) Number of vertices to render.\n"
		"\tfirst (int) Index of the first vertex. By default is 0\n"
		"\tinstances (int) Number of instances. By default is 1\n"

		"\n"
		"Returns:\n"
		"\tNone\n"
		"\n"
	},
	{
		"RenderLinesAdjacency",
		(PyCFunction)Dummy, // RenderLinesAdjacency,
		METH_VARARGS | METH_KEYWORDS,

		"\n"
		"Parameters:\n"
		"\tvao (int) The index of a vertex array object that will be used during the rendering.\n"
		"\tcount (int) Number of vertices to render.\n"
		"\tfirst (int) Index of the first vertex. By default is 0\n"
		"\tinstances (int) Number of instances. By default is 1\n"

		"\n"
		"Returns:\n"
		"\tNone\n"
		"\n"
	},
	{
		"RenderTriangleStripAdjacency",
		(PyCFunction)Dummy, // RenderTriangleStripAdjacency,
		METH_VARARGS | METH_KEYWORDS,

		"\n"
		"Parameters:\n"
		"\tvao (int) The index of a vertex array object that will be used during the rendering.\n"
		"\tcount (int) Number of vertices to render.\n"
		"\tfirst (int) Index of the first vertex. By default is 0\n"
		"\tinstances (int) Number of instances. By default is 1\n"

		"\n"
		"Returns:\n"
		"\tNone\n"
		"\n"
	},
	{
		"RenderTrianglesAdjacency",
		(PyCFunction)Dummy, // RenderTrianglesAdjacency,
		METH_VARARGS | METH_KEYWORDS,

		"\n"
		"Parameters:\n"
		"\tvao (int) The index of a vertex array object that will be used during the rendering.\n"
		"\tcount (int) Number of vertices to render.\n"
		"\tfirst (int) Index of the first vertex. By default is 0\n"
		"\tinstances (int) Number of instances. By default is 1\n"

		"\n"
		"Returns:\n"
		"\tNone\n"
		"\n"
	},
	{
		"RenderIndexedTriangles",
		(PyCFunction)Dummy, // RenderIndexedTriangles,
		METH_VARARGS | METH_KEYWORDS,

		"\n"
		"Parameters:\n"
		"\tvao (int) The index of a vertex array object that will be used during the rendering.\n"
		"\tcount (int) Number of vertices to render.\n"
		"\tfirst (int) Index of the first vertex. By default is 0\n"
		"\tinstances (int) Number of instances. By default is 1\n"

		"\n"
		"Returns:\n"
		"\tNone\n"
		"\n"
	},
	{
		"RenderIndexedTriangleStrip",
		(PyCFunction)Dummy, // RenderIndexedTriangleStrip,
		METH_VARARGS | METH_KEYWORDS,

		"\n"
		"Parameters:\n"
		"\tvao (int) The index of a vertex array object that will be used during the rendering.\n"
		"\tcount (int) Number of vertices to render.\n"
		"\tfirst (int) Index of the first vertex. By default is 0\n"
		"\tinstances (int) Number of instances. By default is 1\n"

		"\n"
		"Returns:\n"
		"\tNone\n"
		"\n"
	},
	{
		"RenderIndexedTriangleFan",
		(PyCFunction)Dummy, // RenderIndexedTriangleFan,
		METH_VARARGS | METH_KEYWORDS,

		"\n"
		"Parameters:\n"
		"\tvao (int) The index of a vertex array object that will be used during the rendering.\n"
		"\tcount (int) Number of vertices to render.\n"
		"\tfirst (int) Index of the first vertex. By default is 0\n"
		"\tinstances (int) Number of instances. By default is 1\n"

		"\n"
		"Returns:\n"
		"\tNone\n"
		"\n"
	},
	{
		"RenderIndexedLines",
		(PyCFunction)Dummy, // RenderIndexedLines,
		METH_VARARGS | METH_KEYWORDS,

		"\n"
		"Parameters:\n"
		"\tvao (int) The index of a vertex array object that will be used during the rendering.\n"
		"\tcount (int) Number of vertices to render.\n"
		"\tfirst (int) Index of the first vertex. By default is 0\n"
		"\tinstances (int) Number of instances. By default is 1\n"

		"\n"
		"Returns:\n"
		"\tNone\n"
		"\n"
	},
	{
		"RenderIndexedLineStrip",
		(PyCFunction)Dummy, // RenderIndexedLineStrip,
		METH_VARARGS | METH_KEYWORDS,

		"\n"
		"Parameters:\n"
		"\tvao (int) The index of a vertex array object that will be used during the rendering.\n"
		"\tcount (int) Number of vertices to render.\n"
		"\tfirst (int) Index of the first vertex. By default is 0\n"
		"\tinstances (int) Number of instances. By default is 1\n"

		"\n"
		"Returns:\n"
		"\tNone\n"
		"\n"
	},
	{
		"RenderIndexedLineLoop",
		(PyCFunction)Dummy, // RenderIndexedLineLoop,
		METH_VARARGS | METH_KEYWORDS,

		"\n"
		"Parameters:\n"
		"\tvao (int) The index of a vertex array object that will be used during the rendering.\n"
		"\tcount (int) Number of vertices to render.\n"
		"\tfirst (int) Index of the first vertex. By default is 0\n"
		"\tinstances (int) Number of instances. By default is 1\n"

		"\n"
		"Returns:\n"
		"\tNone\n"
		"\n"
	},
	{
		"RenderIndexedPoints",
		(PyCFunction)Dummy, // RenderIndexedPoints,
		METH_VARARGS | METH_KEYWORDS,

		"\n"
		"Parameters:\n"
		"\tvao (int) The index of a vertex array object that will be used during the rendering.\n"
		"\tcount (int) Number of vertices to render.\n"
		"\tfirst (int) Index of the first vertex. By default is 0\n"
		"\tinstances (int) Number of instances. By default is 1\n"

		"\n"
		"Returns:\n"
		"\tNone\n"
		"\n"
	},
	{
		"RenderIndexedLineStripAdjacency",
		(PyCFunction)Dummy, // RenderIndexedLineStripAdjacency,
		METH_VARARGS | METH_KEYWORDS,

		"\n"
		"Parameters:\n"
		"\tvao (int) The index of a vertex array object that will be used during the rendering.\n"
		"\tcount (int) Number of vertices to render.\n"
		"\tfirst (int) Index of the first vertex. By default is 0\n"
		"\tinstances (int) Number of instances. By default is 1\n"

		"\n"
		"Returns:\n"
		"\tNone\n"
		"\n"
	},
	{
		"RenderIndexedLinesAdjacency",
		(PyCFunction)Dummy, // RenderIndexedLinesAdjacency,
		METH_VARARGS | METH_KEYWORDS,

		"\n"
		"Parameters:\n"
		"\tvao (int) The index of a vertex array object that will be used during the rendering.\n"
		"\tcount (int) Number of vertices to render.\n"
		"\tfirst (int) Index of the first vertex. By default is 0\n"
		"\tinstances (int) Number of instances. By default is 1\n"

		"\n"
		"Returns:\n"
		"\tNone\n"
		"\n"
	},
	{
		"RenderIndexedTriangleStripAdjacency",
		(PyCFunction)Dummy, // RenderIndexedTriangleStripAdjacency,
		METH_VARARGS | METH_KEYWORDS,

		"\n"
		"Parameters:\n"
		"\tvao (int) The index of a vertex array object that will be used during the rendering.\n"
		"\tcount (int) Number of vertices to render.\n"
		"\tfirst (int) Index of the first vertex. By default is 0\n"
		"\tinstances (int) Number of instances. By default is 1\n"

		"\n"
		"Returns:\n"
		"\tNone\n"
		"\n"
	},
	{
		"RenderIndexedTrianglesAdjacency",
		(PyCFunction)Dummy, // RenderIndexedTrianglesAdjacency,
		METH_VARARGS | METH_KEYWORDS,

		"\n"
		"Parameters:\n"
		"\tvao (int) The index of a vertex array object that will be used during the rendering.\n"
		"\tcount (int) Number of vertices to render.\n"
		"\tfirst (int) Index of the first vertex. By default is 0\n"
		"\tinstances (int) Number of instances. By default is 1\n"

		"\n"
		"Returns:\n"
		"\tNone\n"
		"\n"
	},
	{
		"NewFramebuffer",
		(PyCFunction)Dummy, // NewFramebuffer,
		METH_VARARGS | METH_KEYWORDS,
		"Creates a framebuffer with two texture attachments. (color and depth)\n"
		"The color attachment have RGBA format, 8bit for each channel.\n"
		"The depth texture contains float values.\n"
		""

		"\n"
		"Parameters:\n"
		"\twidth (int) Width of the framebuffer. By default is 0\n"
		"\theight (int) Height of the framebuffer. By default is 0\n"

		"\n"
		"Returns:\n"
		"\tfbo (int) The index of the new framebuffer object.\n"
		"\tcolor (int) The index of the color attachment texture object.\n"
		"\tdepth (int) The index of the depth attachment texture object.\n"
		"\n"
	},
	{
		"DeleteFramebuffer",
		(PyCFunction)Dummy, // DeleteFramebuffer,
		METH_VARARGS,

		"\n"
		"Parameters:\n"
		"\tframebuffer (int) Index of the framebuffer returned by the NewFramebuffer.\n"

		"\n"
		"Returns:\n"
		"\tNone\n"
		"\n"
	},
	{
		"UseFramebuffer",
		(PyCFunction)Dummy, // UseFramebuffer,
		METH_VARARGS,
		""

		"\n"
		"Parameters:\n"
		"\tframebuffer (int) Index of the framebuffer returned by the NewFramebuffer.\n"

		"\n"
		"Returns:\n"
		"\tNone\n"
		"\n"
	},
	{
		"GetDefaultFramebuffer",
		(PyCFunction)Dummy, // GetDefaultFramebuffer,
		METH_VARARGS,
		""

		"\n"
		"Parameters:\n"
		"\tNone\n"

		"\n"
		"Returns:\n"
		"\tNone\n"
		"\n"
	},
	{
		"UseDefaultFramebuffer",
		(PyCFunction)Dummy, // UseDefaultFramebuffer,
		METH_VARARGS,
		""

		"\n"
		"Parameters:\n"
		"\tNone\n"

		"\n"
		"Returns:\n"
		"\tNone\n"
		"\n"
	},
	
	{
		"ReadPixels",
		(PyCFunction)Dummy, // ReadPixels,
		METH_VARARGS | METH_KEYWORDS,
		""

		"\n"
		"Parameters:\n"
		"\tx (int) Offset of the image to read.\n"
		"\ty (int) Offset of the image to read.\n"
		"\twidth (int) Width of the image to read.\n"
		"\theight (int) Height of the image to read.\n"
		"\tcomponents (int) By default is 3\n"

		"\n"
		"Returns:\n"
		"\tpixels (bytes) The color channels selected by components from the active framebuffer.\n"
		"\n"
	},
	{
		"ReadDepthPixels",
		(PyCFunction)Dummy, // ReadDepthPixels,
		METH_VARARGS | METH_KEYWORDS,
		""

		"\n"
		"Parameters:\n"
		"\tx (int) Offset of the image to read.\n"
		"\ty (int) Offset of the image to read.\n"
		"\twidth (int) Width of the image to read.\n"
		"\theight (int) Height of the image to read.\n"

		"\n"
		"Returns:\n"
		"\tpixels (bytes) The depth channel from the active framebuffer.\n"
		"\n"
	},
	{
		"ReadPixel",
		(PyCFunction)Dummy, // ReadPixel,
		METH_VARARGS | METH_KEYWORDS,
		""

		"\n"
		"Parameters:\n"
		"\tx (int) Offset of the pixel to read.\n"
		"\ty (int) Offset of the pixel to read.\n"

		"\n"
		"Returns:\n"
		"\tpixels (int) The rgba value at (x, y) from the active framebuffer.\n"
		"\n"
	},
	{
		"ReadDepthPixel",
		(PyCFunction)Dummy, // ReadDepthPixel,
		METH_VARARGS | METH_KEYWORDS,
		""

		"\n"
		"Parameters:\n"
		"\tx (int) Offset of the pixel to read.\n"
		"\ty (int) Offset of the pixel to read.\n"

		"\n"
		"Returns:\n"
		"\tpixels (float) The depth value at (x, y) from the active framebuffer.\n"
		"\n"
	},
	{
		"UseTextureAsImage",
		(PyCFunction)DummyExtension, // UseTextureAsImage,
		METH_VARARGS | METH_KEYWORDS,
		"To use image2D instead of sampler2D.\n"


		"\n"
		"Parameters:\n"
		"\ttexture (int) .\n"
		"\tbinding (int) Image binding specified by the layout in GLSL. By default is 0\n"

		"\n"
		"Returns:\n"
		"\tNone\n"
		"\n"
	},
	{
		"NewTessEvaluationShader",
		(PyCFunction)DummyExtension, // NewTessEvaluationShader,
		METH_VARARGS,
		""

		"\n"
		"Parameters:\n"
		"\tsource (str) Source code in GLSL.\n"

		"\n"
		"Returns:\n"
		"\tshader (int) The index of the new shader object.\n"
		"\n"
	},
	{
		"NewTessControlShader",
		(PyCFunction)DummyExtension, // NewTessControlShader,
		METH_VARARGS,
		""

		"\n"
		"Parameters:\n"
		"\tsource (str) Source code in GLSL.\n"

		"\n"
		"Returns:\n"
		"\tshader (int) The index of the new shader object.\n"
		"\n"
	},
	{
		"NewComputeShader",
		(PyCFunction)DummyExtension, // NewComputeShader,
		METH_VARARGS,
		"Compiles and links a compute shader from source.\n"

		"\n"
		"Parameters:\n"
		"\tsource (str) Source code in GLSL.\n"

		"\n"
		"Returns:\n"
		"\tprogram (int) The index of the new program object.\n"
		"\n"
	},
	{
		"DeleteComputeShader",
		(PyCFunction)DummyExtension, // DeleteComputeShader,
		METH_VARARGS,
		"Compute shader is a standalone shader program. NOT part of the rendering pipeline.\n"
		"Equivalent to the DeleteProgram.\n"

		"\n"
		"Parameters:\n"
		"\tprogram (int) The index of a program object returned by the NewComputeShader function.\n"

		"\n"
		"Returns:\n"
		"\tNone\n"
		"\n"
	},
	{
		"RunComputeShader",
		(PyCFunction)DummyExtension, // RunComputeShader,
		METH_VARARGS | METH_KEYWORDS,
		"Run the compute shader.\n"

		"\n"
		"Parameters:\n"
		"\tprogram (int) The index of a program object returned by the NewComputeShader function.\n"
		"\tx (int) The x group size of the workers. By default is 1\n"
		"\ty (int) The y group size of the workers. By default is 1\n"
		"\tz (int) The z group size of the workers. By default is 1\n"

		"\n"
		"Returns:\n"
		"\tNone\n"
		"\n"
	},
	{
		"NewStorageBuffer",
		(PyCFunction)DummyExtension, // NewStorageBuffer,
		METH_VARARGS,
		""

		"\n"
		"Parameters:\n"
		"\tdata (bytes) The content of the buffer.\n"

		"\n"
		"Returns:\n"
		"\tssbo (int) The index of the new shader storage buffer object.\n"
		"\n"
	},
	{
		"NewDynamicStorageBuffer",
		(PyCFunction)DummyExtension, // NewDynamicStorageBuffer,
		METH_VARARGS,
		""

		"\n"
		"Parameters:\n"
		"\tdata (bytes) The content of the buffer.\n"

		"\n"
		"Returns:\n"
		"\tssbo (int) The index of the new shader storage buffer object.\n"
		"\n"
	},
	{
		"UseStorageBuffer",
		(PyCFunction)DummyExtension, // UseStorageBuffer,
		METH_VARARGS | METH_KEYWORDS,
		""

		"\n"
		"Parameters:\n"
		"\tssbo (int) The index of a shader storage buffer object returned by the NewStorageBuffer.\n"
		"\tbinding (int) Buffer binding specified by the layout in GLSL. By default is 0\n"

		"\n"
		"Returns:\n"
		"\tNone\n"
		"\n"
	},
	{
		"UpdateStorageBuffer",
		(PyCFunction)DummyExtension, // UpdateStorageBuffer,
		METH_VARARGS | METH_KEYWORDS,
		""

		"\n"
		"Parameters:\n"
		"\tssbo (int) The index of a shader storage buffer object returned by the NewStorageBuffer.\n"
		"\toffset (int) The offset of the data in the buffer to update.\n"
		"\tdata (bytes) The content of the data to write to the buffer.\n"

		"\n"
		"Returns:\n"
		"\tNone\n"
		"\n"
	},
	{
		"ReadStorageBuffer",
		(PyCFunction)DummyExtension, // ReadStorageBuffer,
		METH_VARARGS | METH_KEYWORDS,
		""

		"\n"
		"Parameters:\n"
		"\tssbo (int) The index of a shader storage buffer object returned by the NewStorageBuffer.\n"
		"\toffset (int) The offset of the data in the buffer to read.\n"
		"\tsize (int) The size of the data to read from the buffer.\n"

		"\n"
		"Returns:\n"
		"\tdata (bytes) The Content of the buffer.\n"
		"\n"
	},

	// Better than nothing font

	// {"DebugFontColor", DebugFontColor, METH_VARARGS, 0},
	// {"DebugFontAlight", DebugFontAlight, METH_VARARGS, 0},
	// {"DebugFontPrint", DebugFontPrint, METH_VARARGS, 0},
	{0, 0, 0, 0},
};

void LoadImplementation() {
	PyCFunction implementation[] = {
		(PyCFunction)InitializeModernGL,
		(PyCFunction)ExtensionActive,
		(PyCFunction)GetError,
		(PyCFunction)GetInfo,
		(PyCFunction)Viewport,
		(PyCFunction)Clear,
		(PyCFunction)PointSize,
		(PyCFunction)LineSize,
		(PyCFunction)EnableOnly,
		(PyCFunction)EnableBlend,
		(PyCFunction)DisableBlend,
		(PyCFunction)EnableCullFace,
		(PyCFunction)DisableCullFace,
		(PyCFunction)EnableDepthTest,
		(PyCFunction)DisableDepthTest,
		(PyCFunction)EnableMultisample,
		(PyCFunction)DisableMultisample,
		(PyCFunction)NewVertexShader,
		(PyCFunction)NewFragmentShader,
		(PyCFunction)NewGeometryShader,
		(PyCFunction)DeleteShader,
		(PyCFunction)NewProgram,
		(PyCFunction)DeleteProgram,
		(PyCFunction)UseProgram,
		(PyCFunction)UseDefaultProgram,
		(PyCFunction)CompilerLog,
		(PyCFunction)GetAttributeLocation,
		(PyCFunction)GetUniformLocation,
		(PyCFunction)GetUniformBlockLocation,
		(PyCFunction)Uniform1f,
		(PyCFunction)Uniform2f,
		(PyCFunction)Uniform3f,
		(PyCFunction)Uniform4f,
		(PyCFunction)Uniform1i,
		(PyCFunction)Uniform2i,
		(PyCFunction)Uniform3i,
		(PyCFunction)Uniform4i,
		(PyCFunction)UniformMatrix,
		(PyCFunction)UniformTransposeMatrix,
		(PyCFunction)UseUniformBlock,
		(PyCFunction)NewTexture,
		(PyCFunction)DeleteTexture,
		(PyCFunction)UpdateTexture,
		(PyCFunction)UseTexture,
		(PyCFunction)SetTexturePixelated,
		(PyCFunction)SetTextureFiltered,
		(PyCFunction)SetTextureMipmapped,
		(PyCFunction)BuildMipmap,
		(PyCFunction)NewVertexArray,
		(PyCFunction)DeleteVertexArray,
		(PyCFunction)EnableAttribute,
		(PyCFunction)DisableAttribute,
		(PyCFunction)EnableAttributes,
		(PyCFunction)DisableAttributes,
		(PyCFunction)NewVertexBuffer,
		(PyCFunction)NewIndexBuffer,
		(PyCFunction)NewUniformBuffer,
		(PyCFunction)NewDynamicVertexBuffer,
		(PyCFunction)NewDynamicIndexBuffer,
		(PyCFunction)NewDynamicUniformBuffer,
		(PyCFunction)DeleteVertexBuffer,
		(PyCFunction)DeleteIndexBuffer,
		(PyCFunction)DeleteUniformBuffer,
		(PyCFunction)UpdateVertexBuffer,
		(PyCFunction)UpdateIndexBuffer,
		(PyCFunction)UpdateUniformBuffer,
		(PyCFunction)RenderTriangles,
		(PyCFunction)RenderTriangleStrip,
		(PyCFunction)RenderTriangleFan,
		(PyCFunction)RenderLines,
		(PyCFunction)RenderLineStrip,
		(PyCFunction)RenderLineLoop,
		(PyCFunction)RenderPoints,
		(PyCFunction)RenderLineStripAdjacency,
		(PyCFunction)RenderLinesAdjacency,
		(PyCFunction)RenderTriangleStripAdjacency,
		(PyCFunction)RenderTrianglesAdjacency,
		(PyCFunction)RenderIndexedTriangles,
		(PyCFunction)RenderIndexedTriangleStrip,
		(PyCFunction)RenderIndexedTriangleFan,
		(PyCFunction)RenderIndexedLines,
		(PyCFunction)RenderIndexedLineStrip,
		(PyCFunction)RenderIndexedLineLoop,
		(PyCFunction)RenderIndexedPoints,
		(PyCFunction)RenderIndexedLineStripAdjacency,
		(PyCFunction)RenderIndexedLinesAdjacency,
		(PyCFunction)RenderIndexedTriangleStripAdjacency,
		(PyCFunction)RenderIndexedTrianglesAdjacency,
		(PyCFunction)NewFramebuffer,
		(PyCFunction)DeleteFramebuffer,
		(PyCFunction)UseFramebuffer,
		(PyCFunction)GetDefaultFramebuffer,
		(PyCFunction)UseDefaultFramebuffer,
		(PyCFunction)ReadPixels,
		(PyCFunction)ReadDepthPixels,
		(PyCFunction)ReadPixel,
		(PyCFunction)ReadDepthPixel,
		(PyCFunction)UseTextureAsImage,
		(PyCFunction)NewTessEvaluationShader,
		(PyCFunction)NewTessControlShader,
		(PyCFunction)NewComputeShader,
		(PyCFunction)DeleteComputeShader,
		(PyCFunction)RunComputeShader,
		(PyCFunction)NewStorageBuffer,
		(PyCFunction)NewDynamicStorageBuffer,
		(PyCFunction)UseStorageBuffer,
		(PyCFunction)UpdateStorageBuffer,
		(PyCFunction)ReadStorageBuffer,
	};

	bool extensionSupport = ModernGL::ExtensionActive();
	int count = sizeof(implementation) / sizeof(implementation[0]);
	for (int i = 0; i < count; ++i) {
		if (methods[i].ml_meth == Dummy || extensionSupport) {
			methods[i].ml_meth = implementation[i];
		}
	}
}

PyObject * InitializeModernGL(PyObject * self, PyObject * args) {
	if (initialized) {
		Py_RETURN_TRUE;
	}

	if (!PyArg_ParseTuple(args, ":InitializeModernGL")) {
		PyErr_SetString(ModuleError, "ioladjtq");
		return 0;
	}
	
	if (ModernGL::InitializeModernGL()) {
		initialized = true;
		LoadImplementation();
		Py_RETURN_TRUE;
	} else {
		Py_RETURN_FALSE;
	}
}

bool ModuleReady() {
	if (PyType_Ready(&FramebufferType) < 0) {
		return false;
	}

	if (PyType_Ready(&VertexArrayType) < 0) {
		return false;
	}

	if (PyType_Ready(&VertexBufferType) < 0) {
		return false;
	}

	if (PyType_Ready(&IndexBufferType) < 0) {
		return false;
	}

	if (PyType_Ready(&UniformBufferType) < 0) {
		return false;
	}

	if (PyType_Ready(&StorageBufferType) < 0) {
		return false;
	}

	if (PyType_Ready(&TextureType) < 0) {
		return false;
	}

	if (PyType_Ready(&ShaderType) < 0) {
		return false;
	}

	if (PyType_Ready(&ProgramType) < 0) {
		return false;
	}

	if (PyType_Ready(&AttributeLocationType) < 0) {
		return false;
	}

	if (PyType_Ready(&UniformLocationType) < 0) {
		return false;
	}

	if (PyType_Ready(&UniformBlockLocationType) < 0) {
		return false;
	}

	return true;
}

PyObject * InitModule(PyObject * module) {
	if (!module) {
		return module;
	}
	
	Py_INCREF(&FramebufferType);
	Py_INCREF(&VertexArrayType);
	Py_INCREF(&VertexBufferType);
	Py_INCREF(&IndexBufferType);
	Py_INCREF(&UniformBufferType);
	Py_INCREF(&StorageBufferType);
	Py_INCREF(&TextureType);
	Py_INCREF(&ShaderType);
	Py_INCREF(&ProgramType);
	Py_INCREF(&AttributeLocationType);
	Py_INCREF(&UniformLocationType);
	Py_INCREF(&UniformBlockLocationType);

	PyModule_AddObject(module, "Framebuffer", (PyObject *)&FramebufferType);
	PyModule_AddObject(module, "VertexArray", (PyObject *)&VertexArrayType);
	PyModule_AddObject(module, "VertexBuffer", (PyObject *)&VertexBufferType);
	PyModule_AddObject(module, "IndexBuffer", (PyObject *)&IndexBufferType);
	PyModule_AddObject(module, "UniformBuffer", (PyObject *)&UniformBufferType);
	PyModule_AddObject(module, "StorageBuffer", (PyObject *)&StorageBufferType);
	PyModule_AddObject(module, "Texture", (PyObject *)&TextureType);
	PyModule_AddObject(module, "Shader", (PyObject *)&ShaderType);
	PyModule_AddObject(module, "Program", (PyObject *)&ProgramType);
	PyModule_AddObject(module, "AttributeLocation", (PyObject *)&AttributeLocationType);
	PyModule_AddObject(module, "UniformLocation", (PyObject *)&UniformLocationType);
	PyModule_AddObject(module, "UniformBlockLocation", (PyObject *)&UniformBlockLocationType);

	ModuleError = PyErr_NewException("ModernGL.Error", 0, 0);
	Py_INCREF(ModuleError);

	PyModule_AddObject(module, "Error", ModuleError);

	PyModule_AddIntConstant(module, "ENABLE_NOTHING", 0x00);
	PyModule_AddIntConstant(module, "ENABLE_BLEND", 0x01);
	PyModule_AddIntConstant(module, "ENABLE_CULL_FACE", 0x02);
	PyModule_AddIntConstant(module, "ENABLE_DEPTH_TEST", 0x04);
	PyModule_AddIntConstant(module, "ENABLE_MULTISAMPLE", 0x08);

	PyModule_AddStringConstant(module, "VERSION", "2.0.12");
	
	PyModule_AddStringConstant(module, "__AUTHOR_NAME__", "Szabolcs Dombi");
	PyModule_AddStringConstant(module, "__AUTHOR_EMAIL__", "cprogrammer1994@gmail.com");

	return module;
}

#if PY_MAJOR_VERSION >= 3

static struct PyModuleDef moduledef = {PyModuleDef_HEAD_INIT, "ModernGL", 0, -1, methods, 0, 0, 0, 0};

extern "C" {
	PyObject * PyInit_ModernGL();
}

PyObject * PyInit_ModernGL() {
	if (!ModuleReady()) {
		PyErr_SetString(ModuleError, "cdzvgkhl");
		return 0;
	}
	PyObject * module = PyModule_Create(&moduledef);
	return InitModule(module);
}

#else

extern "C" {
	PyObject * initModernGL();
}

PyObject * initModernGL() {
	if (!ModuleReady()) {
		PyErr_SetString(ModuleError, "elbfngom");
		return 0;
	}
	PyObject * module = Py_InitModule("ModernGL", methods);
	return InitModule(module);
}

#endif
