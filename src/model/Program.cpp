#include "newbrush/model/Program.h"
#include <GLES2/gl2.h>
#include "newbrush/model/Log.h"

using namespace nb;

static const std::string emptyStr;

Program::Program()
	: m_programHandle(0)
{
	m_vertexShader = std::make_shared<Shader>(ShaderTypeE::Vertex);
	m_fragmentShader = std::make_shared<Shader>(ShaderTypeE::Fragment);
	m_programHandle = glCreateProgram();
	if (m_programHandle == 0)
	{
		nbThrowException(std::runtime_error, "glCreateProgram fail, glGetError[%d]", glGetError());
	}
}

Program::~Program()
{
	if(m_programHandle != 0)
	{
		glDeleteProgram(m_programHandle);
	}
}

void Program::setVertexShaderSource(const std::string & source)
{
	m_vertexShader->setSource(source);
}

const std::string & Program::vertexShaderSource() const
{
	return m_vertexShader->source();
}

void Program::setFragmentShaderSource(const std::string & source)
{
	m_fragmentShader->setSource(source);
}

const std::string & Program::fragmentShaderSource() const
{
	return m_fragmentShader->source();
}

void Program::compileLink()
{
	m_vertexShader->compile();
	m_fragmentShader->compile();

	glAttachShader(m_programHandle, m_vertexShader->handle());
	glAttachShader(m_programHandle, m_fragmentShader->handle());
	glLinkProgram(m_programHandle);
	int nLinkStatus;
	glGetProgramiv(m_programHandle, GL_LINK_STATUS, &nLinkStatus);
	if(nLinkStatus == 0)
	{
		GLint nLogLen;
		glGetProgramiv(m_programHandle, GL_INFO_LOG_LENGTH, &nLogLen);

		char *pLog = new char[nLogLen];
		glGetProgramInfoLog(m_programHandle, nLogLen, nullptr, pLog);
		std::string sLog = pLog;
		delete []pLog;
		nbThrowException(std::runtime_error, "program link fail, reason: %s", sLog.data());
	}
}

int Program::getAttributeLocation(const char *name) const
{
	return glGetAttribLocation(m_programHandle, name);
}

int Program::getUniformLocation(const char *name) const
{
	auto ret = glGetUniformLocation(m_programHandle, name);
	return ret;
}

void Program::bindAttributeLocation(unsigned int location, const char *name)
{
	glBindAttribLocation(m_programHandle, location, name);
}

void Program::use()
{
	glUseProgram(m_programHandle);
}

void Program::disuse()
{
	glUseProgram(0);
}

void Program::vertexAttribute(int location, float v)
{
	glVertexAttrib1f(location, v);
}

void Program::vertexAttribute(int location, const glm::vec2 &vec)
{
	glVertexAttrib2f(location, vec.x, vec.y);
}

void Program::vertexAttribute(int location, const glm::vec3 &vec)
{
	glVertexAttrib3f(location, vec.x, vec.y, vec.z);
}

void Program::vertexAttribute(int location, const glm::vec4 &vec)
{
	glVertexAttrib4f(location, vec.x, vec.y, vec.z, vec.w);
}

void Program::vertexAttributePointer(int location, int dimension, int stride, const void *data)
{
	glEnableVertexAttribArray(location);
	glVertexAttribPointer(location, dimension, GL_FLOAT, GL_FALSE, stride, data);
}

void Program::uniform(int location, bool v)
{
	glUniform1f(location, v);
}

void Program::uniform(int location, float v)
{
	glUniform1f(location, v);
}

void Program::uniform(int location, const std::vector<float> &v)
{
	glUniform1fv(location, (GLsizei)v.size(), v.empty() ? nullptr : v.data());
}

void Program::uniform(int location, const glm::vec2 &vec)
{
	glUniform2f(location, vec.x, vec.y);
}

void Program::uniform(int location, const std::vector<glm::vec2> &v)
{
	glUniform2fv(location, (GLsizei)v.size(), v.empty() ? nullptr : glm::value_ptr(v[0]));
}

void Program::uniform(int location, const glm::vec3 &vec)
{
	glUniform3f(location, vec.x, vec.y, vec.z);
}

void Program::uniform(int location, const std::vector<glm::vec3> &v)
{
	glUniform3fv(location, (GLsizei)v.size(), v.empty() ? nullptr : glm::value_ptr(v[0]));
}

void Program::uniform(int location, const glm::vec4 &vec)
{
	glUniform4f(location, vec.x, vec.y, vec.z, vec.w);
}

void Program::uniform(int location, const std::vector<glm::vec4> &v)
{
	glUniform4fv(location, (GLsizei)v.size(), v.empty() ? nullptr : glm::value_ptr(v[0]));
}

void Program::uniform(int location, int v)
{
	glUniform1i(location, v);
}

void Program::uniform(int location, const std::vector<int> &v)
{
	glUniform1iv(location, (GLsizei)v.size(), v.empty() ? nullptr : v.data());
}

void Program::uniform(int location, const glm::ivec2 &vec)
{
	glUniform2i(location, vec.x, vec.y);
}

void Program::uniform(int location, const std::vector<glm::ivec2> &v)
{
	glUniform2iv(location, (GLsizei)v.size(), v.empty() ? nullptr : glm::value_ptr(v[0]));
}

void Program::uniform(int location, const glm::ivec3 &vec)
{
	glUniform3i(location, vec.x, vec.y, vec.z);
}

void Program::uniform(int location, const std::vector<glm::ivec3> &v)
{
	glUniform3iv(location, (GLsizei)v.size(), v.empty() ? nullptr : glm::value_ptr(v[0]));
}

void Program::uniform(int location, const glm::ivec4 &vec)
{
	glUniform4i(location, vec.x, vec.y, vec.z, vec.w);
}

void Program::uniform(int location, const std::vector<glm::ivec4> &v)
{
	glUniform4iv(location, (GLsizei)v.size(), v.empty() ? nullptr : glm::value_ptr(v[0]));
}

void Program::uniform(int location, const glm::mat2x2 &matrix)
{
	glUniformMatrix2fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
}

void Program::uniform(int location, const std::vector<glm::mat2x2> &v)
{
	glUniformMatrix2fv(location, (GLsizei)v.size(), GL_FALSE, v.empty() ? nullptr : glm::value_ptr(v[0]));
}

void Program::uniform(int location, const glm::mat3x3 &matrix)
{
	glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
}

void Program::uniform(int location, const std::vector<glm::mat3x3> &v)
{
	glUniformMatrix3fv(location, (GLsizei)v.size(), GL_FALSE, v.empty() ? nullptr : glm::value_ptr(v[0]));
}

void Program::uniform(int location, const glm::mat4x4 &matrix)
{
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
}

void Program::uniform(int location, const std::vector<glm::mat4x4> &v)
{
	glUniformMatrix4fv(location, (GLsizei)v.size(), GL_FALSE, v.empty() ? nullptr : glm::value_ptr(v[0]));
}

void Program::uniformVar(int location, const var & v)
{
	if (v.is_type<int>())							uniform(location, v.get_value<int>());
	else if (v.is_type<unsigned int>())				uniform(location, (int)v.get_value<unsigned int>());
	else if (v.is_type<short>())					uniform(location, (int)v.get_value<short>());
	else if (v.is_type<unsigned short>())			uniform(location, (int)v.get_value<unsigned short>());
	else if (v.is_type<long>())						uniform(location, (int)v.get_value<long>());
	else if (v.is_type<unsigned long>())			uniform(location, (int)v.get_value<unsigned long>());
	else if (v.is_type<float>())					uniform(location, v.get_value<float>());
	else if (v.is_type<double>())					uniform(location, (float)v.get_value<double>());
	else if (v.is_type<glm::vec2>())				uniform(location, v.get_value<glm::vec2>());
	else if (v.is_type<glm::vec3>())				uniform(location, v.get_value<glm::vec3>());
	else if (v.is_type<glm::vec4>())				uniform(location, v.get_value<glm::vec4>());
	else if (v.is_type<glm::mat2x2>())				uniform(location, v.get_value<glm::mat2x2>());
	else if (v.is_type<glm::mat3x3>())				uniform(location, v.get_value<glm::mat3x3>());
	else if (v.is_type<glm::mat4x4>())				uniform(location, v.get_value<glm::mat4x4>());
	else if (v.is_type<glm::ivec2>())				uniform(location, v.get_value<glm::ivec2>());
	else if (v.is_type<glm::ivec3>())				uniform(location, v.get_value<glm::ivec3>());
	else if (v.is_type<glm::ivec4>())				uniform(location, v.get_value<glm::ivec4>());
	else if (v.is_type<std::vector<int>>())			uniform(location, v.get_value<std::vector<int>>());
	else if (v.is_type<std::vector<float>>())		uniform(location, v.get_value<std::vector<float>>());
	else if (v.is_type<std::vector<glm::vec2>>())	uniform(location, v.get_value<std::vector<glm::vec2>>());
	else if (v.is_type<std::vector<glm::vec3>>())	uniform(location, v.get_value<std::vector<glm::vec3>>());
	else if (v.is_type<std::vector<glm::vec4>>())	uniform(location, v.get_value<std::vector<glm::vec4>>());
	else if (v.is_type<std::vector<glm::mat2x2>>())	uniform(location, v.get_value<std::vector<glm::mat2x2>>());
	else if (v.is_type<std::vector<glm::mat3x3>>())	uniform(location, v.get_value<std::vector<glm::mat3x3>>());
	else if (v.is_type<std::vector<glm::mat4x4>>())	uniform(location, v.get_value<std::vector<glm::mat4x4>>());
	else if (v.is_type<std::vector<glm::ivec2>>())	uniform(location, v.get_value<std::vector<glm::ivec2>>());
	else if (v.is_type<std::vector<glm::ivec3>>())	uniform(location, v.get_value<std::vector<glm::ivec3>>());
	else if (v.is_type<std::vector<glm::ivec4>>())	uniform(location, v.get_value<std::vector<glm::ivec4>>());
	else if (v.is_type<bool>())						uniform(location, v.get_value<bool>());
	else											Log::warn("[{}] is not a supported type for glsl uniform.", v.get_type().get_name().data());
}

////////////////programs

ProgramPtr Programs::primitive()
{
	static ProgramPtr p;
	if (p)	return p;

	constexpr char vs[] = R"(
		attribute vec4 nbPos;
		uniform mat4 nbMvp;
		void main()
		{
			gl_Position = nbMvp * nbPos;
		};
	)";
	constexpr char fs[] = R"(
		uniform vec4 color;
		void main()
		{
			gl_FragColor = color;
		};
	)";
	p = compileBindLink(vs, fs);
	return p;
}

ProgramPtr Programs::gradientPrimitive()
{
	static ProgramPtr p;
	if (p)	return p;

	constexpr char vs[] = R"(
		attribute vec4 nbPos;
		uniform mat4 nbMvp;
		void main()
		{
			gl_Position = nbMvp * nbPos;
		};
	)";
	constexpr char fs[] = R"(
		uniform int size;
		uniform vec4 colors[100];
		uniform float offsets[100];
		void main()
		{
			vec2 u_resolution = vec2(400, 400);
			float y = gl_FragCoord.y / u_resolution.y;
			vec4 color = mix(colors[0], colors[1], smoothstep(offsets[0], offsets[1], y));
			for(int i = 2; i < size; ++i)
				color = mix(color, colors[i], smoothstep(offsets[i-1], offsets[i], y));
			gl_FragColor = color;
		};
	)";
	p = compileBindLink(vs, fs);
	return p;
}

ProgramPtr Programs::image()
{
	static ProgramPtr p;
	if (p)	return p;

	constexpr char vs[] = R"(
		attribute vec4 nbPos;
		attribute vec2 nbTexCoord;
		uniform mat4 nbMvp;
		varying vec2 vTexCoord;
		void main()
		{
			vTexCoord = nbTexCoord;
			gl_Position = nbMvp * nbPos;
		};
	)";
	constexpr char fs[] = R"(
		uniform sampler2D sampler;
		varying vec2 vTexCoord;
		void main()
		{
			gl_FragColor = texture2D(sampler, vTexCoord);
		};
	)";
	p = compileBindLink(vs, fs);
	return p;
}

ProgramPtr Programs::phong()
{
	static ProgramPtr p;
	if (p)	return p;

	constexpr char vs[] = R"(
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
			vFragPos = vec3(nbM * vec4(nbPos, 1.0f));
			vNormal = mat3(nbM) * nbNormal;
			vTexCoord = nbTexCoord;
			gl_Position = nbP * nbV * nbM * vec4(nbPos, 1.0f);
		};
	)";
	constexpr char fs[] = R"(
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
		void main()
		{
			vec3 _ambient, _diffuse, _specular;
			if(!hasTexture)
			{
				_ambient = material.ambient;
				_diffuse = material.diffuse;
				_specular = material.specular;
			}
			else
			{
				_ambient = texture2D(material.diffuse_sampler, vTexCoord).rgb;
				_diffuse = texture2D(material.diffuse_sampler, vTexCoord).rgb;
				_specular = texture2D(material.specular_sampler, vTexCoord).rgb;
			}
			//ambient
			vec3 ambient = light.ambient * _ambient;
			//diffuse 
			vec3 norm = normalize(vNormal);
			vec3 lightDir = normalize(light.position - vFragPos);
			float diff = max(dot(norm, lightDir), 0.0);
			vec3 diffuse = light.diffuse * diff * _diffuse;
			//specular
			vec3 viewDir = normalize(viewPos - vFragPos);
			vec3 reflectDir = reflect(-lightDir, norm);
			float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
			vec3 specular = light.specular * spec * _specular;
			vec3 result = ambient + diffuse + specular;
			gl_FragColor = vec4(result, 1.0);
		};
	)";
	p = compileBindLink(vs, fs);
	return p;
}

ProgramPtr Programs::cube()
{
	static ProgramPtr p;
	if (p)	return p;

	constexpr char vs[] = R"(
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
			vFragPos = vec3(nbM * vec4(nbPos, 1.0f));
			vNormal = mat3(nbM) * nbNormal;
			vTexCoord = nbTexCoord;
			gl_Position = nbP * nbV * nbM * vec4(nbPos, 1.0f);
		};
	)";
	constexpr char fs[] = R"(
		struct Material
		{
			vec3 ambient;
			vec3 diffuse;
			vec3 specular;
			sampler2D diffuse_sampler;
			samplerCube cube_sampler;
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
				color += textureCube(material.cube_sampler, R).rgb;
			}
		}
	)";
	p = compileBindLink(vs, fs);
	return p;
}

ProgramPtr Programs::compileBindLink(const std::string &vs, const std::string &fs)
{
	auto p = std::make_shared<Program>();
	p->setVertexShaderSource(vs);
	p->setFragmentShaderSource(fs);
	//必须在link之前绑定
	p->bindAttributeLocation(Program::nbPositionLocation, Program::nbPositionLocationStr);
	p->bindAttributeLocation(Program::nbColorLocation, Program::nbColorLocationStr);
	p->bindAttributeLocation(Program::nbTexCoordLocaltion, Program::nbTexCoordLocaltionStr);
	p->bindAttributeLocation(Program::nbNormalLocation, Program::nbNormalLocationStr);
	p->compileLink();
	return p;
}
