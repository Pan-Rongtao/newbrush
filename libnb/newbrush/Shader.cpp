#include "newbrush/Shader.h"
#include "newbrush/Log.h"
#include "newbrush/GLUnit.h"
#include "glm/ext.hpp"

using namespace nb;

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
uniform mat4 nbM;
uniform mat4 nbVP;
varying vec2 vTexCoord;
varying vec3 vNormal;
varying vec3 vFragPos;
void main()
{
	vFragPos = vec3(nbM * vec4(nbPos, 1.0));
	vNormal = mat3(nbM) * nbNormal;
	vTexCoord = nbTexCoord;
	gl_Position = nbVP * nbM * vec4(nbPos, 1.0);
}
)";
constexpr char phong_fs[] = R"(
precision mediump float;
struct Material
{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float shininess;
	sampler2D diffuse_sampler;
	sampler2D specular_sampler;
};
struct Light
{
	vec3 position;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
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
		_ambient = material.ambient;
		_diffuse = material.diffuse;
		_specular = material.specular;
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
	vec3 ambient = light.ambient * _ambient;
	//diffuse 
	vec3 norm = normalize(vNormal);
	vec3 lightDir = normalize(light.position - vFragPos);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = light.diffuse * diff * _diffuse;
	//specular
	vec3 viewDir = normalize(-viewPos + vFragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	vec3 specular = light.specular * spec * _specular;
	vec3 result = ambient + diffuse + specular;
	gl_FragColor = vec4(result, _alpha);
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
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
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
		baseColor = vec4(material.diffuse, 1.0);
	}
	vec3 color = baseColor.rgb;
	if(hasCubemap)
	{
		color *= material.ambient;
		color += material.specular;
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
		nbThrowException(std::runtime_error, "link fail, reason: %s", pLog);
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
