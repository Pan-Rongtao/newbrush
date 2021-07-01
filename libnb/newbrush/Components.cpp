#include "newbrush/Components.h"
#include "newbrush/Log.h"
#include "simdjson/simdjson.h"
#include "stb/stb_image_write.h"
#include <regex>

using namespace nb;
using namespace simdjson;

/**************************************
*	OpenGL函数相关
***************************************/
static float g_viewportX = 0.0f;
static float g_viewportY = 0.0f;
static float g_viewportWidth = 0.0f;
static float g_viewportHeight = 0.0f;
void GLUtils::viewport(float x, float y, float width, float height)
{
	glViewport((int)x, (int)y, (int)width, (int)height);
	g_viewportX = x;
	g_viewportY = y;
	g_viewportWidth = width;
	g_viewportHeight = height;
}

void GLUtils::getViewport(float &x, float &y, float &width, float &height)
{
	x = g_viewportX;
	y = g_viewportY;
	width = g_viewportWidth;
	height = g_viewportHeight;
}
/**************************************
*	变换相关
***************************************/
static const glm::mat4 g_sIdentityMat4(1.0f);
Transform::Transform(const glm::vec3 &translate, const glm::vec3 &rotation, const glm::vec3 &scale)
	: m_translate(translate)
	, m_rotate(rotation)
	, m_scale(scale)
	, m_rotateCenter(0.0f)
	, m_scaleCenter(0.0f)
{
	updateMatrix();
}

//转换为平移、旋转、缩放。注意，转换后的缩放vec可能和C4D等编辑器中显示的符号相反，
//欧拉角也和C4D等编辑器上的数值不一致。不必在意，因为C4D使用的是左手定则，
//只要最后相乘计算得到的矩阵=value就可以了
void Transform::setValue(const glm::mat4x4 & value)
{
	glm::vec3 skew;
	glm::quat orientation;
	glm::vec4 perspective;
	//分解为scale、orientation四元素和position
	glm::decompose(value, m_scale, orientation, m_translate, skew, perspective);

	//四元素转旋转矩阵
	auto rMatrix = glm::mat4_cast(orientation);

	//旋转矩阵提取欧拉角
	glm::extractEulerAngleYXZ(rMatrix, m_rotate.y, m_rotate.x, m_rotate.z);
	m_matrix = value;
}

void Transform::updateMatrix()
{
	auto translateMatrix = glm::translate(g_sIdentityMat4, m_translate);
	//旋转	HPB{朝向，仰俯，侧倾}，或者YPR ： yaw(航向) pitch(仰俯) roll(滚转)，分别对应YXZ轴旋转
	auto rotateMatrix = glm::yawPitchRoll(m_rotate.y, m_rotate.x, m_rotate.z);
	auto scaleMatrix = glm::scale(g_sIdentityMat4, m_scale);
	m_matrix = translateMatrix * rotateMatrix * scaleMatrix;
}

glm::mat4x4 TranslateTransform2D::value()
{ 
	return glm::translate(g_sIdentityMat4, glm::vec3(m_x, m_y, 0.0f));
}

glm::mat4x4 RotateTransform2D::value()
{
	auto matrix = glm::translate(g_sIdentityMat4, glm::vec3(m_centerX, m_centerY, 0.0f));
	matrix = glm::rotate(matrix, glm::radians(m_angle), glm::vec3(0.0f, 0.0f, 1.0f));
	matrix = glm::translate(matrix, glm::vec3(-m_centerX, -m_centerY, 0.0f));
	return matrix;
}

glm::mat4x4 ScaleTransform2D::value()
{
	auto matrix = glm::translate(g_sIdentityMat4, glm::vec3(m_centerX * (1 - m_scaleX), m_centerY * (1 - m_scaleY), 0.0f));
	matrix = glm::scale(matrix, glm::vec3(m_scaleX, m_scaleY, 1.0f));
	return matrix;
}

glm::mat4x4 TransformGroup2D::value()
{
	glm::mat4x4 matrix = g_sIdentityMat4;
	for (size_t i = 0; i < m_children.size(); i++)
	{
		matrix = m_children[i]->value() * matrix;
	}
	return matrix;
}

/**************************************
*	摄像头相关
***************************************/
PerspectiveCamera::PerspectiveCamera()
	: m_translate(0.0f, 0.0f, -10.0f)
	, m_rotate(0.0)
	, m_scale(1.0)
	, m_fov(45.0f)
	, m_aspect(1.7777777f)
	, m_nearPlane(0.3f)
	, m_farPlane(1000.0f)
{
	updateMatrix();
}

void PerspectiveCamera::updateMatrix()
{
	auto translateMatrix = glm::translate(g_sIdentityMat4, m_translate);
	//旋转	HPB{朝向，仰俯，侧倾}，或者YPR ： yaw(航向) pitch(仰俯) roll(滚转)，分别对应YXZ轴旋转
	auto rotateMatrix = glm::yawPitchRoll(m_rotate.y, m_rotate.x, m_rotate.z);
	auto scaleMatrix = glm::scale(g_sIdentityMat4, m_scale);

	auto viewMatrix = translateMatrix * rotateMatrix * scaleMatrix;

	m_viewProjectionMatrix = glm::perspective(glm::radians(m_fov), m_aspect, m_nearPlane, m_farPlane) * viewMatrix;
}

/**************************************
*	着色器相关
***************************************/
Shader::~Shader()
{
	glDeleteProgram(m_programHandle);
}

void Shader::compileLink(const std::string & vsSource, const std::string & fsSource)
{
	auto checkCompileState = [](uint32_t shaderHandle)->std::string
	{
		std::string ret;
		GLint status;
		glGetShaderiv(shaderHandle, GL_COMPILE_STATUS, &status);
		if (!status)
		{
			GLint nLogLen;
			glGetShaderiv(shaderHandle, GL_INFO_LOG_LENGTH, &nLogLen);
			char *pLog = new char[nLogLen];
			glGetShaderInfoLog(shaderHandle, nLogLen, nullptr, pLog);
			ret = pLog;
			delete[]pLog;
		}
		return ret;
	};

	glDeleteProgram(m_programHandle);
	auto vertexHandle = glCreateShader(GL_VERTEX_SHADER);
	auto fragmentHandle = glCreateShader(GL_FRAGMENT_SHADER);
	m_programHandle = glCreateProgram();
	nbThrowExceptionIf((!vertexHandle || !fragmentHandle || !m_programHandle), std::runtime_error, "create shader fail, glGetError[%d]", glGetError());

	//必须在link之前绑定
	bindAttributeLocation(0, "position");
	bindAttributeLocation(1, "color");
	bindAttributeLocation(2, "uv");
	bindAttributeLocation(3, "normal");
	//for bones
	bindAttributeLocation(6, "boneIndexs");
	bindAttributeLocation(7, "boneWeights");
	//for renderer2D
	bindAttributeLocation(8, "texIndex");
	bindAttributeLocation(9, "opacity");

	const char *pVertexSource = vsSource.data();
	glShaderSource(vertexHandle, 1, &pVertexSource, NULL);
	glCompileShader(vertexHandle);
	auto vsFailReason = checkCompileState(vertexHandle);
	nbThrowExceptionIf(!vsFailReason.empty(), std::runtime_error, "compile fail, reason: %s\n\n%s", vsFailReason.data(), pVertexSource);

	const char *pFragmentSource = fsSource.data();
	glShaderSource(fragmentHandle, 1, &pFragmentSource, NULL);
	glCompileShader(fragmentHandle);
	auto fgFailReason = checkCompileState(fragmentHandle);
	nbThrowExceptionIf(!fgFailReason.empty(), std::runtime_error, "compile fail, reason: %s\n\n%s", fgFailReason.data(), pFragmentSource);

	glAttachShader(m_programHandle, vertexHandle);
	glAttachShader(m_programHandle, fragmentHandle);
	glLinkProgram(m_programHandle);

	int nLinkStatus;
	glGetProgramiv(m_programHandle, GL_LINK_STATUS, &nLinkStatus);
	if (nLinkStatus == 0)
	{
		GLint nLogLen;
		glGetProgramiv(m_programHandle, GL_INFO_LOG_LENGTH, &nLogLen);
		char *pLog = new char[nLogLen];
		glGetProgramInfoLog(m_programHandle, nLogLen, nullptr, pLog);
		nbThrowException(std::runtime_error, "link fail, reason: %s\n\n%s", pLog, pFragmentSource);
		glDeleteProgram(m_programHandle);
		delete[]pLog;
	}
	glDeleteShader(vertexHandle);
	glDeleteShader(fragmentHandle);
}

int Shader::getAttributeLocation(const char *name) const
{
	return glGetAttribLocation(m_programHandle, name);
}

int Shader::getUniformLocation(const char *name) const
{
	return glGetUniformLocation(m_programHandle, name);
}

void Shader::bindAttributeLocation(uint32_t location, const char *name)
{
	glBindAttribLocation(m_programHandle, location, name);
}

void Shader::use()
{
	glUseProgram(m_programHandle);
}

void Shader::disuse()
{
	glUseProgram(0);
}

void Shader::vertexAttribute(int location, float v)
{
	glVertexAttrib1f(location, v);
}

void Shader::vertexAttribute(int location, const glm::vec2 &vec)
{
	glVertexAttrib2f(location, vec.x, vec.y);
}

void Shader::vertexAttribute(int location, const glm::vec3 &vec)
{
	glVertexAttrib3f(location, vec.x, vec.y, vec.z);
}

void Shader::vertexAttribute(int location, const glm::vec4 &vec)
{
	glVertexAttrib4f(location, vec.x, vec.y, vec.z, vec.w);
}

void Shader::vertexAttributePointer(int location, int dimension, int stride, const void *data)
{
	glEnableVertexAttribArray(location);
	glVertexAttribPointer(location, dimension, GL_FLOAT, GL_FALSE, stride, data);
}

void Shader::setBool(const char *name, bool v)
{
	glUniform1f(getUniformLocation(name), v);
}

void Shader::setFloat(const char *name, float v)
{
	glUniform1f(getUniformLocation(name), v);
}

void Shader::setFloatArray(const char *name, const std::vector<float> &v)
{
	glUniform1fv(getUniformLocation(name), (GLsizei)v.size(), v.empty() ? nullptr : v.data());
}

void Shader::setFloat2(const char *name, const glm::vec2 &v)
{
	glUniform2f(getUniformLocation(name), v.x, v.y);
}

void Shader::setFloat2Array(const char *name, const std::vector<glm::vec2> &v)
{
	glUniform2fv(getUniformLocation(name), (GLsizei)v.size(), v.empty() ? nullptr : glm::value_ptr(v[0]));
}

void Shader::setFloat3(const char *name, const glm::vec3 &v)
{
	glUniform3f(getUniformLocation(name), v.x, v.y, v.z);
}

void Shader::setFloat3Array(const char *name, const std::vector<glm::vec3> &v)
{
	glUniform3fv(getUniformLocation(name), (GLsizei)v.size(), v.empty() ? nullptr : glm::value_ptr(v[0]));
}

void Shader::setFloat4(const char *name, const glm::vec4 &v)
{
	glUniform4f(getUniformLocation(name), v.x, v.y, v.z, v.w);
}

void Shader::setFloat4Array(const char *name, const std::vector<glm::vec4> &v)
{
	glUniform4fv(getUniformLocation(name), (GLsizei)v.size(), v.empty() ? nullptr : glm::value_ptr(v[0]));
}

void Shader::setInt(const char *name, int v)
{
	glUniform1i(getUniformLocation(name), v);
}

void Shader::setIntArray(const char *name, const std::vector<int> &v)
{
	glUniform1iv(getUniformLocation(name), (GLsizei)v.size(), v.empty() ? nullptr : v.data());
}

void Shader::setIntArray(const char *name, int * v, int count)
{
	glUniform1iv(getUniformLocation(name), count, v);
}

void Shader::setInt2(const char *name, const glm::ivec2 &vec)
{
	glUniform2i(getUniformLocation(name), vec.x, vec.y);
}

void Shader::setInt2Array(const char *name, const std::vector<glm::ivec2> &v)
{
	glUniform2iv(getUniformLocation(name), (GLsizei)v.size(), v.empty() ? nullptr : glm::value_ptr(v[0]));
}

void Shader::setInt3(const char *name, const glm::ivec3 &vec)
{
	glUniform3i(getUniformLocation(name), vec.x, vec.y, vec.z);
}

void Shader::setInt3Array(const char *name, const std::vector<glm::ivec3> &v)
{
	glUniform3iv(getUniformLocation(name), (GLsizei)v.size(), v.empty() ? nullptr : glm::value_ptr(v[0]));
}

void Shader::setInt4(const char *name, const glm::ivec4 &vec)
{
	glUniform4i(getUniformLocation(name), vec.x, vec.y, vec.z, vec.w);
}

void Shader::setInt4Array(const char *name, const std::vector<glm::ivec4> &v)
{
	glUniform4iv(getUniformLocation(name), (GLsizei)v.size(), v.empty() ? nullptr : glm::value_ptr(v[0]));
}

void Shader::setMat2(const char *name, const glm::mat2 &v)
{
	glUniformMatrix2fv(getUniformLocation(name), 1, GL_FALSE, glm::value_ptr(v));
}

void Shader::setMat2Array(const char *name, const std::vector<glm::mat2> &v)
{
	glUniformMatrix2fv(getUniformLocation(name), (GLsizei)v.size(), GL_FALSE, v.empty() ? nullptr : glm::value_ptr(v[0]));
}

void Shader::setMat3(const char *name, const glm::mat3 &v)
{
	glUniformMatrix3fv(getUniformLocation(name), 1, GL_FALSE, glm::value_ptr(v));
}

void Shader::setMat3Array(const char *name, const std::vector<glm::mat3> &v)
{
	glUniformMatrix3fv(getUniformLocation(name), (GLsizei)v.size(), GL_FALSE, v.empty() ? nullptr : glm::value_ptr(v[0]));
}

void Shader::setMat4(const char *name, const glm::mat4 &v)
{
	glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, glm::value_ptr(v));
}

void Shader::setMat4Array(const char *name, const std::vector<glm::mat4> &v)
{
	glUniformMatrix4fv(getUniformLocation(name), (GLsizei)v.size(), GL_FALSE, v.empty() ? nullptr : glm::value_ptr(v[0]));
}

static std::unordered_map<std::string, ref<Shader>> g_shaders;
void ShaderLibrary::initSystemShader()
{
	static bool systemShaderInit = false;
	if (!systemShaderInit)
	{
		systemShaderInit = true;
		auto vs =
#include "shader/2d.vs"
			;
		auto fs =
#include "shader/2d.fs"
			;
		get("shader_2d", vs, fs);
	}
}

ref<Shader> ShaderLibrary::get(const std::string & name, const std::string & vsSource, const std::string & fsSource)
{
	initSystemShader();
	auto iter = g_shaders.find(name);
	if (iter == g_shaders.end())
	{
		ref<Shader> shader(new Shader());
		shader->compileLink(vsSource, fsSource);
		iter = g_shaders.insert({name, shader}).first;
	}
	return iter->second;
}

ref<Shader> ShaderLibrary::get(const std::string & name)
{
	initSystemShader();
	auto iter = g_shaders.find(name);
	return iter == g_shaders.end() ? nullptr : iter->second;
}

ref<Shader> ShaderLibrary::getFromFile(const std::string & name, const std::string & filePath)
{
	return nullptr;
}

/**************************************
*	纹理相关
***************************************/

void glFormatAndType(int bmChannels, int &glFormat, int &glType)
{
	switch (bmChannels)
	{
	case 1:	glFormat = GL_RED;	glType = GL_UNSIGNED_BYTE;			break;
	case 2:	glFormat = GL_RGB;	glType = GL_UNSIGNED_SHORT_5_6_5;	break;
	case 3:	glFormat = GL_RGB;	glType = GL_UNSIGNED_BYTE;			break;
	case 4:	glFormat = GL_RGBA;	glType = GL_UNSIGNED_BYTE;			break;
	default:														break;
	}
}

Texture::Texture()
	: m_samplerUnit(0)
{
	glGenTextures(1, &m_handle);
	auto err = glGetError();
	nbThrowExceptionIf(err == 1282, std::logic_error, "glGenTextures fail, err=%d", err);
}

Texture::~Texture()
{
	glDeleteTextures(1, &m_handle);
}

void Texture::active()
{
	glActiveTexture(GL_TEXTURE0 + m_samplerUnit);
}

////////////////////
void initTextureParams(Texture *tex)
{
	tex->bind();
	tex->setWrappingS(TextureWrappingE::Repeat);
	tex->setWrappingT(TextureWrappingE::Repeat);
	tex->setMagnifyFilter(TextureFilterE::Point);
	tex->setNarrowFilter(TextureFilterE::Point);
	tex->unbind();
}

Texture2D::Texture2D()
	: m_width(0.0f)
	, m_height(0.0f)
	, m_channels(0)
{
	initTextureParams(this);
}

Texture2D::Texture2D(const std::string & path)
	: m_width(0.0f)
	, m_height(0.0f)
	, m_channels(0)
{
	initTextureParams(this);
	update(path);
}

void Texture2D::bind()
{
	glBindTexture(GL_TEXTURE_2D, m_handle);
}

void Texture2D::unbind()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture2D::setWrappingS(TextureWrappingE wrapping)
{
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, (int)(wrapping));
}

void Texture2D::setWrappingT(TextureWrappingE wrapping)
{
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, (int)(wrapping));
}

TextureWrappingE Texture2D::wrappingS() const
{
	int v = 0;
	glGetTexParameteriv(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, &v);
	return (TextureWrappingE)v;
}

TextureWrappingE Texture2D::wrappingT() const
{
	int v = 0;
	glGetTexParameteriv(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, &v);
	return (TextureWrappingE)v;
}

void Texture2D::setMagnifyFilter(TextureFilterE filter)
{
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, (int)(filter));
}

void Texture2D::setNarrowFilter(TextureFilterE filter)
{
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, (int)(filter));
}

TextureFilterE Texture2D::magnifyFilter() const
{
	int v = 0;
	glGetTexParameteriv(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, &v);
	return (TextureFilterE)v;
}

TextureFilterE Texture2D::narrowFilter() const
{
	int v = 0;
	glGetTexParameteriv(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, &v);
	return (TextureFilterE)v;
}

void Texture2D::update(const std::string & path)
{
	auto bm = createRef<Bitmap>(path);
	if (!bm->isValid())
		Log::warn("path '{}' is invalid.", path);
	else
		update(bm);
}

void Texture2D::update(ref<Bitmap> bm)
{
	int glFormat = 0, glType = 0;
	glFormatAndType(bm->channels(), glFormat, glType);
	if (glFormat != 0)
	{
		bind();
		glTexImage2D(GL_TEXTURE_2D, 0, glFormat, bm->width(), bm->height(), 0, glFormat, glType, bm->data());
		unbind();
	}
	m_width = (float)bm->width();
	m_height = (float)bm->height();
	m_channels = bm->channels();
}

void Texture2D::genMipmap()
{
	glGenerateMipmap(GL_TEXTURE_2D);
}

bool Texture2D::save(const std::string & path, uint32_t quality)
{
	GLubyte* data = new GLubyte[(int)(m_width * m_height * m_channels)];
	int glFormat = 0, glType = 0;
	glFormatAndType(m_channels, glFormat, glType);

	GLuint fbo;
	glGenFramebuffers(1, &fbo);
	glBindFramebuffer(GL_FRAMEBUFFER, fbo);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_handle, 0);
	glReadPixels(0, 0, (int)m_width, (int)m_height, glFormat, glType, data);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glDeleteFramebuffers(1, &fbo);

	return Bitmap::save(path, data, (int)m_width, (int)m_height, m_channels, quality);
}

/////////////////
TextureCubemap::TextureCubemap()
{
	initTextureParams(this);
}

void TextureCubemap::bind()
{
	glBindTexture(GL_TEXTURE_CUBE_MAP, m_handle);
}

void TextureCubemap::unbind()
{
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}

void TextureCubemap::setWrappingS(TextureWrappingE wrapping)
{
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, (int)(wrapping));
}

void TextureCubemap::setWrappingT(TextureWrappingE wrapping)
{
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, (int)(wrapping));
}

TextureWrappingE TextureCubemap::wrappingS() const
{
	int v = 0;
	glGetTexParameteriv(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, &v);
	return (TextureWrappingE)v;
}

TextureWrappingE TextureCubemap::wrappingT() const
{
	int v = 0;
	glGetTexParameteriv(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, &v);
	return (TextureWrappingE)v;
}

void TextureCubemap::setMagnifyFilter(TextureFilterE filter)
{
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, (int)(filter));
}

void TextureCubemap::setNarrowFilter(TextureFilterE filter)
{
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, (int)(filter));
}

TextureFilterE TextureCubemap::magnifyFilter() const
{
	int v = 0;
	glGetTexParameteriv(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, &v);
	return (TextureFilterE)v;
}

TextureFilterE TextureCubemap::narrowFilter() const
{
	int v = 0;
	glGetTexParameteriv(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, &v);
	return (TextureFilterE)v;
}

void TextureCubemap::update(const std::string & top, const std::string & bottom, const std::string & left, const std::string & right, const std::string & front, const std::string & back)
{
	auto updateOne = [](const std::string &path, int index)
	{
		Bitmap bm(path);
		int glFormat = 0, glType = 0;
		glFormatAndType(bm.channels(), glFormat, glType);
		if (glFormat != 0)
		{
			glTexImage2D(index, 0, glFormat, bm.width(), bm.height(), 0, glFormat, glType, bm.data());
		}
	};

	bind();
	updateOne(right, GL_TEXTURE_CUBE_MAP_POSITIVE_X);
	updateOne(left, GL_TEXTURE_CUBE_MAP_NEGATIVE_X);
	updateOne(top, GL_TEXTURE_CUBE_MAP_POSITIVE_Y);
	updateOne(bottom, GL_TEXTURE_CUBE_MAP_NEGATIVE_Y);
	updateOne(back, GL_TEXTURE_CUBE_MAP_POSITIVE_Z);
	updateOne(front, GL_TEXTURE_CUBE_MAP_NEGATIVE_Z);
	unbind();
}

TextureFrame::TextureFrame()
{}

TextureFrame::TextureFrame(ref<Texture2D> _texture)
	: TextureFrame(_texture, Rect(0.0f, 0.0f, _texture ? _texture->width() : 0.0f, _texture ? _texture->height() : 0.0f))
{}

TextureFrame::TextureFrame(ref<Texture2D> _texture, const Rect & rc)
{
	auto w = _texture ? _texture->width() : 0.0f;
	auto h = _texture ? _texture->height() : 0.0f;
	texture = _texture;
	frame = { rc.x(), rc.y(), rc.width(), rc.height() };
	sourceSize = { frame.z, frame.w };
	pinch = { 0.0f, 0.0f };
	rotated = false;
}

namespace nb
{
	class NB_API TextureAtlas : public Texture2D, public std::enable_shared_from_this<TextureAtlas>
	{
	public:
		void load(const std::string &imagePath, const std::string &cfgPath);
		const TextureFrame &getFrame(const std::string &frameName);

	private:
		TextureFrame parseOneFrame(const dom::object &frameObj);
		std::map<std::string, TextureFrame> m_frames;
	};
}

static TextureFrame g_sInvalidFrame{ 0 };
TextureFrame TextureAtlas::parseOneFrame(const dom::object &frameObj)
{
	auto trimmed = frameObj["trimmed"].get_bool().first;
	auto rotated = frameObj["rotated"].get_bool().first;
	auto frame = frameObj["frame"].get_object().first;
	auto spriteSourceSize = frameObj["spriteSourceSize"].get_object().first;
	auto sourceSize = frameObj["sourceSize"].get_object().first;
	auto frameX = frame["x"].get_int64().first;
	auto frameY = frame["y"].get_int64().first;
	auto frameW = frame["w"].get_int64().first;
	auto frameH = frame["h"].get_int64().first;
	auto spriteSourceX = spriteSourceSize["x"].get_int64().first;
	auto spriteSourceY = spriteSourceSize["y"].get_int64().first;
//	auto spriteSourceW = spriteSourceSize["w"].get_int64().first;
//	auto spriteSourceH = spriteSourceSize["h"].get_int64().first;
	auto sourceW = sourceSize["w"].get_int64().first;
	auto sourceH = sourceSize["h"].get_int64().first;

	TextureFrame texFrame;
	texFrame.frame = { frameX, frameY, frameW, frameH };
	texFrame.sourceSize = { sourceW, sourceH };
	texFrame.pinch = { spriteSourceX, spriteSourceY };
	texFrame.rotated = { rotated };
	return texFrame;
}

void TextureAtlas::load(const std::string &imagePath, const std::string & cfgPath)
{
	update(imagePath);

	dom::parser parser;
	auto result = parser.load(cfgPath);
	nbThrowExceptionIf(result.second, std::runtime_error, "parsing[%s] fail, error=[%d], error_message=[%s]",
		cfgPath.data(), result.second, error_message(result.second));

	auto frames = parser.doc.root()["frames"].get_object().first;
	for (auto const &f : frames)
	{
		std::string key = f.key.data();
		TextureFrame texFrame = parseOneFrame(f.value.get_object().first);
		texFrame.texture = shared_from_this();
		m_frames.insert({ key, texFrame });
	}
}

const TextureFrame &TextureAtlas::getFrame(const std::string & frameName)
{
	auto iter = m_frames.find(frameName);
	return iter == m_frames.end() ? g_sInvalidFrame : iter->second;
}

static std::map<std::string, ref<Texture>> g_textures;
ref<Texture2D> TextureLibrary::addTexture2D(const std::string & name, const std::string & imagePath)
{
	auto iter = g_textures.find(name);
	if (iter != g_textures.end())
	{
		nbThrowException(std::logic_error, "[%s] is already exists.", name.data());
		return nullptr;
	}
	else
	{
		auto tex = createRef<Texture2D>(imagePath);
		g_textures[name] = tex;
		return tex;
	}

}

void TextureLibrary::addTextureAtlas(const std::string &name, const std::string & imagePath, const std::string & cfgPath)
{
	auto iter = g_textures.find(name);
	nbThrowExceptionIf(iter != g_textures.end(), std::logic_error, "[%s] is already exists.", name.data());

	auto texAtlases = createRef<TextureAtlas>();
	texAtlases->load(imagePath, cfgPath);
	g_textures[name] = texAtlases;
}

ref<TextureCubemap> TextureLibrary::addTextureCubemap(const std::string &name, const std::string & top, const std::string & bottom, const std::string & left, const std::string & right, const std::string & front, const std::string & back)
{
	auto iter = g_textures.find(name);
	if (iter != g_textures.end())
	{
		nbThrowException(std::logic_error, "[%s] is already exists.", name.data());
		return nullptr;
	}
	else
	{
		auto texCubemap = createRef<TextureCubemap>();
		texCubemap->update(top, bottom, left, right, front, back);
		g_textures[name] = texCubemap;
		return texCubemap;
	}
}

ref<Texture2D> TextureLibrary::getTexture2D(const std::string & name)
{
	auto iter = g_textures.find(name);
	return iter == g_textures.end() ? nullptr : as<Texture2D>(iter->second);
}

const TextureFrame &TextureLibrary::getFrameFromTextureAtlas(const std::string &name, const std::string &frameName)
{
	auto iter = g_textures.find(name);
	if (iter == g_textures.end())
	{
		return g_sInvalidFrame;
	}
	else
	{
		auto texAtlas = as<TextureAtlas>(iter->second);
		return texAtlas ? texAtlas->getFrame(frameName) : g_sInvalidFrame;
	}
}

ref<TextureCubemap> TextureLibrary::getTextureCubemap(const std::string & name)
{
	auto iter = g_textures.find(name);
	return iter == g_textures.end() ? nullptr : as<TextureCubemap>(iter->second);
}

/**************************************
*	灯光相关
***************************************/
Light::Light()
	: ambient(127, 127, 127)
	, diffuse(5, 5, 5)
	, specular(127, 127, 127)
{}

void Light::uploadUniform(ref<Shader> shader) const
{
	if (!shader) return;

	shader->setFloat3("u_light.ambientColor", glm::vec3(ambient.rf(), ambient.gf(), ambient.bf()));
	shader->setFloat3("u_light.diffuseColor", glm::vec3(diffuse.rf(), diffuse.gf(), diffuse.bf()));
	shader->setFloat3("u_light.specularColor", glm::vec3(specular.rf(), specular.gf(), specular.bf()));
}

void DirectionalLight::uploadUniform(ref<Shader> shader) const
{
	if (!shader) return;

	Light::uploadUniform(shader);
	shader->setFloat3("u_light.direction", direction);
}

void PointLightBase::uploadUniform(ref<Shader> shader) const
{
	if (!shader) return;

	Light::uploadUniform(shader);
	shader->setFloat3("u_light.position", position);
	shader->setFloat("u_light.constantAttenuation", constantAttenuation);
	shader->setFloat("u_light.linearAttenuation", linearAttenuation);
	shader->setFloat("u_light.quadraticAttenuation", quadraticAttenuation);
}

void SpotLight::uploadUniform(ref<Shader> shader) const
{
	if (!shader) return;

	PointLightBase::uploadUniform(shader);
	shader->setFloat3("u_light.direction", direction);
	shader->setFloat("u_light.innerConeAngle", innerConeAngle);
	shader->setFloat("u_light.outerConeAngle", outerConeAngle);
}

/**************************************
*	材质相关
***************************************/
Material::Material(ref<Shader> _shader)
	: shader(_shader)
{}

FlatMaterial::FlatMaterial(const Color &_color)
	: color(_color)
{
	auto *vs =
#include "shader/Flat.vs"
		;
	auto *fs =
#include "shader/Flat.fs"
		;
	shader = ShaderLibrary::get("shader_color", vs, fs);
}

void FlatMaterial::uploadUniform(ref<Camera> camera)
{
	if (!shader) return;

	shader->setFloat4("u_flatColor", glm::vec4(color.rf(), color.gf(), color.bf(), color.af()));
}

LinearGrandientMaterial::LinearGrandientMaterial()
	: horizontal(true)
{
	auto *vs =
#include "shader/LinearGradient.vs"
		;
	auto *fs =
#include "shader/LinearGradient.fs"
		;
	shader = ShaderLibrary::get("shader_linearGradient", vs, fs);
}

void LinearGrandientMaterial::uploadUniform(ref<Camera> camera)
{
	nbThrowExceptionIf(gradientStops.size() > 10, std::out_of_range, "gradientStops'size[%d] is out of range[0, 10]", (int)gradientStops.size());
	if (!shader || gradientStops.empty())	return;

	float x, y, w, h;
	GLUtils::getViewport(x, y, w, h);

	std::vector<glm::vec4> colors;
	std::vector<float> offsets;
	for (auto const &one : gradientStops)
	{
		colors.push_back(glm::vec4(one.color.rf(), one.color.gf(), one.color.bf(), one.color.af()));
		auto offsetForViewport = horizontal ? (box.x + one.offset * box.z) / w : 1.0f - (box.y + one.offset * box.w) / h;
		offsets.push_back(offsetForViewport);
	}

	shader->setFloat2("u_resolution", glm::vec2(w, h));
	shader->setFloatArray("u_offsets", offsets);
	shader->setFloat4Array("u_colors", colors);
	shader->setInt("u_gradientCount", offsets.size());
	shader->setBool("u_horizontal", horizontal);
}

PhongMaterial::PhongMaterial()
	: shineness(32.0f)
	, opacity(1.0f)
{
	auto *vs =
#include "shader/Phong.vs"
		;
	auto *fs =
#include "shader/Phong.fs"
		;
	shader = ShaderLibrary::get("shader_phong", vs, fs);
}

void PhongMaterial::uploadUniform(ref<Camera> camera)
{
	if (!shader)
		return;

	auto cm = as<PerspectiveCamera>(camera);
	if (cm)
		shader->setFloat3("u_cameraPosition", cm->getTranslate());

	if (emissionMapping) emissionMapping->activeAndBind();
	if (diffuseMapping)
	{
		diffuseMapping->activeAndBind();
		if (specularMapping) specularMapping->activeAndBind();
	}
	else
	{
		shader->setFloat3("u_material.ambientColor", { ambientColor.rf(), ambientColor.gf(), ambientColor.bf() });
		shader->setFloat3("u_material.diffuseColor", { diffuseColor.rf(), diffuseColor.gf(), diffuseColor.bf() });
		shader->setFloat3("u_material.specularColor", { specularColor.rf(), specularColor.gf(), specularColor.bf() });
		shader->setFloat3("u_material.emissionColor", { emissionColor.rf(), emissionColor.gf(), emissionColor.bf() });
		shader->setFloat("u_opacity", opacity);
	}

	shader->setBool("u_hasTexture", diffuseMapping || specularMapping || emissionMapping);
	shader->setFloat("u_material.shininess", shineness);
}

SkyBoxMaterial::SkyBoxMaterial()
	: SkyBoxMaterial(nullptr)
{}

SkyBoxMaterial::SkyBoxMaterial(ref<Texture> _cubeMapping)
	: cubeMapping(_cubeMapping)
{
	auto *vs =
#include "shader/SkyBox.vs"
		;
	auto *fs =
#include "shader/SkyBox.fs"
		;
	shader = ShaderLibrary::get("shader_skybox", vs, fs);
}

void SkyBoxMaterial::uploadUniform(ref<Camera> camera)
{
	if (!shader)
		return;

	if (cubeMapping)
		cubeMapping->activeAndBind();
}

CubemapMaterial::CubemapMaterial()
	: ambient(Color(128, 128, 128))
	, diffuse(Color(0, 0, 0))
	, specular(Color(0, 0, 0))
	, cubeMapColor(Color(255, 255, 255))
{
	auto *vs =
#include "shader/Reflect.vs"
		;
	auto *fs =
#include "shader/Reflect.fs"
		;
	shader = ShaderLibrary::get("shader_reflect", vs, fs);
}

void CubemapMaterial::uploadUniform(ref<Camera> camera)
{
	if (!shader)
		return;

	auto cm = as<PerspectiveCamera>(camera);
	if (cm)
		shader->setFloat3("u_cameraPosition", cm->getTranslate());
	if (diffuseMapping)
	{
		shader->setBool("u_hasTexture", true);
		diffuseMapping->activeAndBind();
	}
	else
	{
		shader->setBool("u_hasTexture", false);
	}

	if (cubeMapping)
	{
		shader->setBool("u_hasCubemap", true);
		cubeMapping->activeAndBind();
	}
	else
	{
		shader->setBool("u_hasCubemap", false);
	}
	shader->setFloat3("u_material.ambientColor", { ambient.rf(), ambient.gf(), ambient.bf() });
	shader->setFloat3("u_material.diffuseColor", { diffuse.rf(), diffuse.gf(), diffuse.bf() });
	shader->setFloat3("u_material.specularColor", { specular.rf(), specular.gf(), specular.bf() });
	shader->setFloat3("u_material.cubemapColor", { cubeMapColor.rf(), cubeMapColor.gf(), cubeMapColor.bf() });
}

/**************************************
*	面片相关
***************************************/
bool Vertex::addBone(float boneIndex, float boneWeight)
{
	auto arrSize = nbArraySize(boneIndexs);
	for (auto i = 0u; i != arrSize; ++i)
	{
		if (boneWeights[i] == 0.0f)
		{
			boneIndexs[i] = boneIndex;
			boneWeights[i] = boneWeight;
			return true;
		}
	}
	return false;
}

Mesh::Mesh(const std::vector<Vertex> &vertexs, const std::vector<uint16_t> &indices, ref<Material> materia)
	: material(materia)
	, vao(0)
	, vbo(0)
	, ebo(0)
	, hasBone(false)
	, renderAble(true)
{
	setup(vertexs, indices);
}

Mesh::~Mesh()
{
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);
	glDeleteBuffers(1, &ebo);
}

void Mesh::draw(const glm::mat4 &matrix, ref<Camera> camera, const std::vector<ref<Light>>& lights, int mode) const
{
	if (!renderAble || !material || !material->shader)
		return;

	auto shader = material->shader;
	shader->use();

	//计算后的mvp，以及分开的m/v/p
	auto const &m = matrix;
	auto const &vp = camera->getViewProjectionMatrix();

	shader->setMat4("u_modelMatrix", m);
	shader->setMat4("u_viewProjectionMatrix", vp);
	shader->setBool("u_hasBones", hasBone);

	//材质更新uniforms
	material->uploadUniform(camera);

	//灯光更新uniforms
	for (auto const &light : lights)
	{
		if (light) light->uploadUniform(shader);
	}

	glBindVertexArray(vao);
	glDrawElements(mode, indicesSize, GL_UNSIGNED_SHORT, 0);
	glBindVertexArray(0);

	shader->disuse();
}

void Mesh::setup(const std::vector<Vertex>& vertexs, const std::vector<uint16_t>& indices)
{
	if (vertexs.empty() || indices.empty())
		return;

	//vao begin
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	//vbo
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertexs.size(), &vertexs[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, color));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));

	glEnableVertexAttribArray(6);
	glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, boneIndexs));
	glEnableVertexAttribArray(7);
	glVertexAttribPointer(7, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, boneWeights));

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	//ebo
	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(int16_t), &indices[0], GL_STATIC_DRAW);

	//end vao
	glBindVertexArray(0);

	indicesSize = indices.size();
}

/**************************************
*	Timer相关
***************************************/
static bool m_onDispatching = false;					//标记正在dispatch期间
static std::set<Timer *> m_timerRemovedOnDispatching;	//记录在dispatch期间调用stop()/remove()的timer
static std::multimap<uint64_t, Timer *> m_tickSequence;//tick队列
bool Timer::isActive() const
{
	return std::find_if(m_tickSequence.begin(), m_tickSequence.end(), [this](const std::pair<uint64_t, Timer *> &p) { return (p.second == this); }) 
		!= m_tickSequence.end();
}

void Timer::driveInLoop()
{
	uint64_t currentTick = nb::getMilliseconds();
	for (auto iter = m_tickSequence.begin(); iter != m_tickSequence.end(); )
	{
		//大于等于表示到点的timer，发送事件并移除此timer，
		//小于代表后面的都未到点，全部忽略
		if (currentTick >= iter->first)
		{
			Timer *timer = iter->second;
			m_onDispatching = true;			//标记以使记录在dispatch期间调用stop()/remove()的timer，供是否重新add该timer提供判断依据
			timer->Tick.invoke({ timer });
			m_onDispatching = false;
			iter = remove(timer);
			// 假如timer是单次触发模式，或者在dispatch期间已经被stop，不再将此timer重新加入到队列中
			if (!timer->isSingleShot() && m_timerRemovedOnDispatching.find(timer) == m_timerRemovedOnDispatching.end())
			{
				add(timer);
			}
			m_timerRemovedOnDispatching.clear();
		}
		else
		{
			break;
		}
	}
}

void Timer::add(Timer * timer)
{
	m_tickSequence.insert({ nb::getMilliseconds() + timer->interval(), timer });
}

std::multimap<uint64_t, Timer *>::iterator Timer::remove(Timer *timer)
{
	for (auto iter = m_tickSequence.begin(); iter != m_tickSequence.end(); ++iter)
	{
		if (iter->second == timer)
		{
			if (m_onDispatching)
			{
				m_timerRemovedOnDispatching.insert(timer);
			}
			return m_tickSequence.erase(iter);
		}
	}
	return m_tickSequence.end();
}
