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
float g_viewportX = 0.0f;
float g_viewportY = 0.0f;
float g_viewportWidth = 0.0f;
float g_viewportHeight = 0.0f;
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

void PerspectiveCamera::setTranslate(const glm::vec3 &translate)
{
	m_translate = translate;
	updateMatrix();
}

void PerspectiveCamera::setRotate(const glm::vec3 &rotate)
{
	m_rotate = rotate;
	updateMatrix();
}

void PerspectiveCamera::setScale(const glm::vec3 &scale)
{
	m_scale = scale;
	updateMatrix();
}

const glm::vec3 &PerspectiveCamera::getTranslate() const
{
	return m_translate;
}

const glm::vec3 &PerspectiveCamera::getRotate() const
{
	return m_rotate;
}

const glm::vec3 &PerspectiveCamera::getScale() const
{
	return m_scale;
}

void PerspectiveCamera::setFov(float fov)
{
	m_fov = fov;
	updateMatrix();
}

void PerspectiveCamera::setAspect(float aspect)
{
	if (std::isnan(aspect))	return;
	if (aspect == m_aspect) return;
	m_aspect = aspect;
	updateMatrix();
}

void PerspectiveCamera::setNearPlane(float nearPlane)
{
	m_nearPlane = nearPlane;
	updateMatrix();
}

void PerspectiveCamera::setFarPlane(float farPlane)
{
	m_farPlane = farPlane;
	updateMatrix();
}

float PerspectiveCamera::getFov() const
{
	return m_fov;
}

float PerspectiveCamera::getAspect() const
{
	return m_aspect;
}

float PerspectiveCamera::getNearPlane() const
{
	return m_nearPlane;
}

float PerspectiveCamera::getFarPlane() const
{
	return m_farPlane;
}

const glm::mat4 &PerspectiveCamera::getViewProjectionMatrix() const
{
	return m_viewProjectionMatrix;
}

void PerspectiveCamera::updateMatrix()
{
	auto translateMatrix = glm::translate(glm::mat4x4(1.0f), m_translate);
	//旋转	HPB{朝向，仰俯，侧倾}，或者YPR ： yaw(航向) pitch(仰俯) roll(滚转)，分别对应YXZ轴旋转
	auto rotateMatrix = glm::yawPitchRoll(m_rotate.y, m_rotate.x, m_rotate.z);
	auto scaleMatrix = glm::scale(glm::mat4x4(1.0f), m_scale);

	auto viewMatrix = translateMatrix * rotateMatrix * scaleMatrix;

	m_viewProjectionMatrix = glm::perspective(glm::radians(m_fov), m_aspect, m_nearPlane, m_farPlane) * viewMatrix;
}

OrthographicCamera::OrthographicCamera()
	: m_matrix(1.0f)
{}

void OrthographicCamera::resize(float width, float height)
{
	m_matrix = glm::ortho(0.0f, width, height, 0.0f, -1000.0f, 1000.0f);
}

const glm::mat4 &OrthographicCamera::getViewProjectionMatrix() const
{
	return m_matrix;
}

ref<OrthographicCamera> nb::sharedCamera2D()
{
	static auto sharedCamera = createRef<OrthographicCamera>();
	return sharedCamera;
}

/**************************************
*	着色器相关
***************************************/

/* color shader code begin */
constexpr char color_vs[] = R"(
attribute vec3 nbPos;
uniform mat4 nbM;
uniform mat4 nbVP;
void main()
{
	gl_Position = nbVP * nbM * vec4(nbPos, 1.0);
}
)";
constexpr char color_fs[] = R"(
precision mediump float;
uniform vec4 color;
void main()
{
	gl_FragColor = color;
}
)";
/* base shader code end */

/* base shader code begin */
constexpr char base_vs[] = R"(
attribute vec4 nbPos;
attribute vec4 nbColor;
attribute vec2 nbTexCoord;
attribute float nbTexIndex;
attribute float nbOpacity;
uniform mat4 nbVP;
varying vec4 vColor;
varying vec2 vTexCoord;
varying float vTexIndex;
varying float vOpacity;
void main()
{
	vColor = nbColor;
	vTexCoord = nbTexCoord;
	vTexIndex = nbTexIndex;
	vOpacity = nbOpacity;
	gl_Position = nbVP * nbPos;
}
)";

constexpr char base_fs[] = R"(
precision mediump float;
varying vec4 vColor;
varying vec2 vTexCoord;
varying float vTexIndex;
varying float vOpacity;
uniform sampler2D samplers[16];	//android中最高支持16
void main()
{
	int index = int(vTexIndex);
	gl_FragColor = texture2D(samplers[index], vTexCoord) * vColor;
	gl_FragColor.a = gl_FragColor.a * vOpacity;
}
)";

/* base shader code end */

/* linear shader code begin */
constexpr char linear_vs[] = R"(
attribute vec3 nbPos;
uniform mat4 nbM;
uniform mat4 nbVP;
void main()
{
	gl_Position = nbVP * nbM * vec4(nbPos, 1.0);
}
)";
constexpr char linear_fs[] = R"(
precision mediump float;
uniform int size;
uniform vec4 colors[100];
uniform float offsets[100];
uniform float lenght;
uniform bool vertical;
void main()
{
	float n;
	if(vertical)
		n = gl_FragCoord.y / lenght;
	else
		n = gl_FragCoord.x / lenght;
	vec4 color = mix(colors[0], colors[1], smoothstep(offsets[0], offsets[1], n));
	//for(int i = 2; i < 3; ++i)
	//	color = mix(color, colors[i], smoothstep(offsets[i-1], offsets[i], n));
	gl_FragColor = color;
}
)";
/* linear shader code end */

/* phong shader code begin */
constexpr char phong_vs[] = R"(
attribute vec3 nbPos;
attribute vec2 nbTexCoord;
attribute vec3 nbNormal;
attribute vec4 nbBoneIndexs;
attribute vec4 nbBoneWeights;
uniform mat4 nbM;
uniform mat4 nbVP;
uniform mat4 modelMat;
uniform bool hasBones;
uniform mat4 bonesMats[60];	//有些驱动无法支持到100
varying vec2 vTexCoord;
varying vec3 vNormal;
varying vec3 vFragPos;
void main()
{
	mat4 meshMat = mat4(1.0);
	if(hasBones)
	{
		meshMat = bonesMats[int(nbBoneIndexs[0])] * nbBoneWeights[0];
		meshMat += bonesMats[int(nbBoneIndexs[1])] * nbBoneWeights[1];
		meshMat += bonesMats[int(nbBoneIndexs[2])] * nbBoneWeights[2];
		meshMat += bonesMats[int(nbBoneIndexs[3])] * nbBoneWeights[3];
	}
	else
	{
		meshMat = nbM;
	}
	mat4 mat = modelMat * meshMat;
	vTexCoord = nbTexCoord;
	vFragPos = vec3(mat * vec4(nbPos, 1.0));
	vNormal = mat3(mat) * nbNormal;
	gl_Position = nbVP * mat * vec4(nbPos, 1.0);
}
)";
constexpr char phong_fs[] = R"(
precision mediump float;
struct Material
{
	vec3 ambientColor;
	vec3 diffuseColor;
	vec3 specularColor;
	vec3 emissionColor;
	float shininess;
	sampler2D diffuse_sampler;
	sampler2D specular_sampler;
	sampler2D emission_sampler;
};
struct Light
{
	vec3 position;
	vec3 ambientColor;
	vec3 diffuseColor;
	vec3 specularColor;
};
varying vec2 vTexCoord;
varying vec3 vNormal;
varying vec3 vFragPos;
uniform vec3 viewPos;
uniform Material material;
uniform Light light;
uniform bool hasTexture;
uniform float opacity;
void main()
{
	vec3 _ambient, _diffuse, _specular;
	float _alpha = 0.0;
	if(!hasTexture)
	{
		_ambient = material.ambientColor;
		_diffuse = material.diffuseColor;
		_specular = material.specularColor;
		_alpha = opacity;
	}
	else
	{
		vec4 diffuseRgba = texture2D(material.diffuse_sampler, vTexCoord);
		_ambient = _diffuse = diffuseRgba.rgb;
		_specular = texture2D(material.specular_sampler, vTexCoord).rgb;
		_alpha = diffuseRgba.a;
	}
	//ambient
	vec3 ambient = light.ambientColor * _ambient;
	//diffuse
	vec3 norm = normalize(vNormal);
	vec3 lightDir = normalize(light.position - vFragPos);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = light.diffuseColor * diff * _diffuse;
	//specular
	vec3 viewDir = normalize(-viewPos + vFragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	vec3 specular = light.specularColor * spec * _specular;
	//emissive
	vec3 emission = material.emissionColor * texture2D(material.emission_sampler, vTexCoord).rgb;
	vec3 result = ambient + diffuse /*+ specular*/ + emission;
	gl_FragColor = vec4(result, 1.0);
}
)";
/* phong shader code end */

/* skybox shader code begin */
constexpr char skybox_vs[] = R"(
attribute vec4 nbPos;
uniform mat4 nbM;
uniform mat4 nbVP;
varying vec3 vTexCoord;
void main()
{
	vTexCoord = nbPos.xyz;
	gl_Position = (nbVP * nbM * nbPos).xyww;
}
)";
constexpr char skybox_fs[] = R"(
precision mediump float;
uniform samplerCube sampler;
varying vec3 vTexCoord;
void main()
{
	gl_FragColor = textureCube(sampler, vTexCoord);
}
)";
/* skybox shader code end */

/* cubePhong shader code begin */
constexpr char cubePhong_vs[] = R"(
attribute vec3 nbPos;
attribute vec2 nbTexCoord;
attribute vec3 nbNormal;
uniform mat4 nbM;
uniform mat4 nbV;
uniform mat4 nbP;
varying vec2 vTexCoord;
varying vec3 vNormal;
varying vec3 vFragPos;
void main()
{
	vFragPos = vec3(nbM * vec4(nbPos, 1.0));
	vNormal = mat3(nbM) * nbNormal;
	vTexCoord = nbTexCoord;
	gl_Position = nbP * nbV * nbM * vec4(nbPos, 1.0);
}
)";
constexpr char cubePhong_fs[] = R"(
precision mediump float;
struct Material
{
	vec3 ambientColor;
	vec3 diffuseColor;
	vec3 specularColor;
	sampler2D diffuse_sampler;
	samplerCube cube_sampler;
	vec3 cubemapColor;
};
varying vec2 vTexCoord;
varying vec3 vNormal;
varying vec3 vFragPos;
uniform vec3 viewPos;
uniform Material material;
uniform bool hasTextures;
uniform bool hasCubemap;
	
void main()
{
	vec4 baseColor = vec4(0.0);
	if(hasTextures)
	{
		baseColor = texture2D(material.diffuse_sampler, vTexCoord).rgba;
	}
	else
	{
		baseColor = vec4(material.diffuseColor, 1.0);
	}
	vec3 color = baseColor.rgb;
	if(hasCubemap)
	{
		color *= material.ambientColor;
		color += material.specularColor;
		vec3 I = normalize(vFragPos - viewPos);
		vec3 R = reflect(I, normalize(vNormal));
		color += textureCube(material.cube_sampler, R).rgb * material.cubemapColor;
	}
	gl_FragColor = vec4(color, baseColor.a);
}
)";
/* cubePhong shader code end */

Shader::Shader()
	: m_programHandle(0)
{
}

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
	bindAttributeLocation(0, "nbPos");
	bindAttributeLocation(1, "nbColor");
	bindAttributeLocation(2, "nbTexCoord");
	bindAttributeLocation(3, "nbNormal");
	//for renderer2D
	bindAttributeLocation(4, "nbTexIndex");
	bindAttributeLocation(5, "nbOpacity");
	//for bones
	bindAttributeLocation(6, "nbBoneIndexs");
	bindAttributeLocation(7, "nbBoneWeights");

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

uint32_t Shader::id()
{
	return m_programHandle;
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
ref<Shader> ShaderLibrary::add(const std::string & name, const std::string & vsSource, const std::string & fsSource)
{
	if (exists(name))
	{
		nbThrowException(std::logic_error, "%s is already exists.", name.data());
		return nullptr;
	}
	else
	{
		ref<Shader> shader(new Shader());
		shader->compileLink(vsSource, fsSource);
		g_shaders[name] = shader;
		return shader;
	}

}

ref<Shader> ShaderLibrary::addFromFile(const std::string & name, const std::string & filePath)
{
	return nullptr;
}

bool ShaderLibrary::exists(const std::string & name)
{
	return g_shaders.find(name) != g_shaders.end();
}

ref<Shader> ShaderLibrary::get(const std::string & name)
{
	initSystemShader();

	auto iter = g_shaders.find(name);
	return g_shaders.find(name) == g_shaders.end() ? nullptr : iter->second;
}

void ShaderLibrary::initSystemShader()
{
	static bool systemShaderInit = false;
	if (!systemShaderInit)
	{
		add("system_2d", base_vs, base_fs);
		add("system_color", color_vs, color_fs);
		add("system_linear", linear_vs, linear_fs);
		add("system_phong", phong_vs, phong_fs);
		add("system_skybox", skybox_vs, skybox_fs);
		add("system_cubePhong", cubePhong_vs, cubePhong_fs);
		systemShaderInit = true;
	}
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

unsigned Texture::id() const
{
	return m_handle;
}

void Texture::setSamplerUnit(unsigned unit)
{
	m_samplerUnit = unit;
}

unsigned Texture::samplerUnit()
{
	return m_samplerUnit;
}

void Texture::activeAndBind()
{
	active();
	bind();
}

void Texture::active()
{
	glActiveTexture(GL_TEXTURE0 + m_samplerUnit);
}

////////////////////
Texture2D::Texture2D()
{
	bind();
	setWrappingS(TextureWrappingE::Repeat);
	setWrappingT(TextureWrappingE::Repeat);
	setMagnifyFilter(TextureFilterE::Point);
	setNarrowFilter(TextureFilterE::Point);
	unbind();
}

Texture2D::Texture2D(const std::string & path)
{
	bind();
	setWrappingS(TextureWrappingE::Repeat);
	setWrappingT(TextureWrappingE::Repeat);
	setMagnifyFilter(TextureFilterE::Point);
	setNarrowFilter(TextureFilterE::Point);
	unbind();
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

int32_t Texture2D::getChannels() const
{
	return m_channels;
}

bool Texture2D::isValid() const
{
	return m_channels != 0;
}

float Texture2D::width() const
{
	return m_width;
}

float Texture2D::height() const
{
	return m_height;
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
	bind();
	setWrappingS(TextureWrappingE::Repeat);
	setWrappingT(TextureWrappingE::Repeat);
	setMagnifyFilter(TextureFilterE::Point);
	setNarrowFilter(TextureFilterE::Point);
	unbind();
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
	return TextureFilterE();
}

TextureFilterE TextureCubemap::narrowFilter() const
{
	return TextureFilterE();
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
	auto spriteSourceW = spriteSourceSize["w"].get_int64().first;
	auto spriteSourceH = spriteSourceSize["h"].get_int64().first;
	auto sourceW = sourceSize["w"].get_int64().first;
	auto sourceH = sourceSize["h"].get_int64().first;

	TextureFrame texFrame;
	texFrame.offset = { (float)frameX, (float)frameY };
	texFrame.size = { (float)spriteSourceW, (float)spriteSourceH };
	texFrame.trimmedSize = { (float)spriteSourceX, (float)spriteSourceY };
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
		texFrame.texture = shared_from_this();// m_texture;
		m_frames.insert({ key, texFrame });
	}
}

const TextureFrame &TextureAtlas::getFrame(const std::string & frameName)
{
	auto iter = m_frames.find(frameName);
	return iter == m_frames.end() ? g_sInvalidFrame : iter->second;
}

std::map<std::string, ref<Texture>> g_textures;
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
{
}

void Light::uploadUniform(ref<Shader> shader) const
{
	if (!shader) return;

	shader->setFloat3("light.ambientColor", glm::vec3(ambient.rf(), ambient.gf(), ambient.bf()));
	shader->setFloat3("light.diffuseColor", glm::vec3(diffuse.rf(), diffuse.gf(), diffuse.bf()));
	shader->setFloat3("light.specularColor", glm::vec3(specular.rf(), specular.gf(), specular.bf()));
}

void DirectionalLight::uploadUniform(ref<Shader> shader) const
{
	if (!shader) return;

	Light::uploadUniform(shader);
	shader->setFloat3("light.direction", direction);
}

void PointLightBase::uploadUniform(ref<Shader> shader) const
{
	if (!shader) return;

	Light::uploadUniform(shader);
	shader->setFloat3("light.position", position);
	shader->setFloat("light.constantAttenuation", constantAttenuation);
	shader->setFloat("light.linearAttenuation", linearAttenuation);
	shader->setFloat("light.quadraticAttenuation", quadraticAttenuation);
}

void SpotLight::uploadUniform(ref<Shader> shader) const
{
	if (!shader) return;

	PointLightBase::uploadUniform(shader);
	shader->setFloat3("light.direction", direction);
	shader->setFloat("light.innerConeAngle", innerConeAngle);
	shader->setFloat("light.outerConeAngle", outerConeAngle);
}

/**************************************
*	材质相关
***************************************/
Material::Material(ref<Shader> _shader)
	: shader(_shader)
{}

////////////////
SolidColorMaterial::SolidColorMaterial()
	: SolidColorMaterial(Colors::black)
{}

SolidColorMaterial::SolidColorMaterial(const Color &_color)
	: Material(ShaderLibrary::get("system_color"))
	, color(_color)
{}

void SolidColorMaterial::uploadUniform(ref<Camera> camera)
{
	if (!shader)
		return;

	shader->setFloat4("color", glm::vec4(color.rf(), color.gf(), color.bf(), color.af()));
}

LinearGrandientMaterial::LinearGrandientMaterial()
	: LinearGrandientMaterial(800.0f, {})
{}

LinearGrandientMaterial::LinearGrandientMaterial(float _lenght, const std::vector<GradientStop> &_grandients)
	: Material(ShaderLibrary::get("system_linear"))
	, lenght(_lenght)
	, grandients(_grandients)
	, vertical(true)
{}

void LinearGrandientMaterial::uploadUniform(ref<Camera> camera)
{
	if (!shader || grandients.empty())	return;

	std::vector<glm::vec4> colors;
	std::vector<float> offsets;
	for (auto const &one : grandients)
	{
		colors.push_back(glm::vec4(one.color.rf(), one.color.gf(), one.color.bf(), one.color.af()));
		offsets.push_back(one.offset);
	}

	shader->setFloat("lenght", lenght);
	shader->setInt("size", grandients.size());
	shader->setFloatArray("offsets", offsets);
	shader->setFloat4Array("colors", colors);
	shader->setBool("vertical", vertical);
}

PhongMaterial::PhongMaterial()
	: Material(ShaderLibrary::get("system_phong"))
	, shineness(32.0f)
	, opacity(1.0f)
{}

void PhongMaterial::uploadUniform(ref<Camera> camera)
{
	if (!shader)
		return;

	auto cm = as<PerspectiveCamera>(camera);
	if (cm)
		shader->setFloat3("viewPos", cm->getTranslate());

	if (emissionMapping) emissionMapping->activeAndBind();
	if (diffuseMapping)
	{
		diffuseMapping->activeAndBind();
		if (specularMapping) specularMapping->activeAndBind();
	}
	else
	{
		shader->setFloat3("material.ambientColor", { ambientColor.rf(), ambientColor.gf(), ambientColor.bf() });
		shader->setFloat3("material.diffuseColor", { diffuseColor.rf(), diffuseColor.gf(), diffuseColor.bf() });
		shader->setFloat3("material.specularColor", { specularColor.rf(), specularColor.gf(), specularColor.bf() });
		shader->setFloat3("material.emissionColor", { emissionColor.rf(), emissionColor.gf(), emissionColor.bf() });
		shader->setFloat("opacity", opacity);
	}

	shader->setBool("hasTexture", diffuseMapping || specularMapping || emissionMapping);
	shader->setFloat("material.shininess", shineness);
}

SkyBoxMaterial::SkyBoxMaterial()
	: SkyBoxMaterial(nullptr)
{}

SkyBoxMaterial::SkyBoxMaterial(ref<Texture> _cubeMapping)
	: Material(ShaderLibrary::get("system_skybox"))
	, cubeMapping(_cubeMapping)
{}

void SkyBoxMaterial::uploadUniform(ref<Camera> camera)
{
	if (!shader)
		return;

	if (cubeMapping)
		cubeMapping->activeAndBind();
}

CubemapMaterial::CubemapMaterial()
	: Material(ShaderLibrary::get("system_cubePhong"))
	, ambient(Color(128, 128, 128))
	, diffuse(Color(0, 0, 0))
	, specular(Color(0, 0, 0))
	, cubeMapColor(Color(255, 255, 255))
{}

void CubemapMaterial::uploadUniform(ref<Camera> camera)
{
	if (!shader)
		return;

	auto cm = as<PerspectiveCamera>(camera);
	if (cm)
		shader->setFloat3("viewPos", cm->getTranslate());
	if (diffuseMapping)
	{
		shader->setBool("hasTextures", true);
		diffuseMapping->activeAndBind();
	}
	else
	{
		shader->setBool("hasTextures", false);
	}

	if (cubeMapping)
	{
		shader->setBool("hasCubemap", true);
		cubeMapping->activeAndBind();
	}
	else
	{
		shader->setBool("hasCubemap", false);
	}
	shader->setFloat3("material.ambientColor", { ambient.rf(), ambient.gf(), ambient.bf() });
	shader->setFloat3("material.diffuseColor", { diffuse.rf(), diffuse.gf(), diffuse.bf() });
	shader->setFloat3("material.specularColor", { specular.rf(), specular.gf(), specular.bf() });
	shader->setFloat3("material.cubemapColor", { cubeMapColor.rf(), cubeMapColor.gf(), cubeMapColor.bf() });
}
