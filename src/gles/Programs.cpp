#include "gles/Programs.h"
#include "gles/Shader.h"

using namespace nb::gl;

std::shared_ptr<PrimitiveProgram> PrimitiveProgram::instance()
{
	static std::shared_ptr<PrimitiveProgram> p;
	if (!p)
		p = std::make_shared<PrimitiveProgram>();
	return p;
}

PrimitiveProgram::PrimitiveProgram()
{
	std::shared_ptr<VertexShader> verShader = std::make_shared<VertexShader>
	("\
		attribute	vec4	nb_Position;\
		attribute	vec4	nb_Color;\
		attribute	vec2	nb_TextCoord;\
		uniform		mat4	nb_Mvp;\
		varying		vec4	vary_color;\
		varying		vec2	vary_textureCoord;\
		\
		void main()\
		{\
			vary_color = nb_Color;\
			vary_textureCoord = nb_TextCoord;\
			gl_Position = nb_Mvp * nb_Position;\
		}\
	");
	std::shared_ptr<FragmentShader> fragShader = std::make_shared<FragmentShader>
	("\
		uniform		bool		unif_colorMode;\
		varying		vec4		vary_color;\
		varying		vec2		vary_textureCoord;\
		uniform		sampler2D	unif_sampler;\
		\
		void main()\
		{\
			if(unif_colorMode)\
				gl_FragColor = vary_color;\
			else\
				gl_FragColor = texture2D(unif_sampler, vary_textureCoord);\
		}\
	");
	verShader->compile();
	fragShader->compile();
	setVertexShader(verShader);
	setFragmentShader(fragShader);
	//必须在link之前绑定
	bindAttributeLocation(Program::positionLocation, "nb_Position");
	bindAttributeLocation(Program::colorLocation, "nb_Color");
	bindAttributeLocation(Program::texCoordLocaltion, "nb_TextCoord");
	bindAttributeLocation(Program::normalLocation, "nb_Normal");
	link();
}

std::shared_ptr<PhongProgram> PhongProgram::instance()
{
	static std::shared_ptr<PhongProgram> p;
	if (!p)
		p = std::make_shared<PhongProgram>();
	return p;
}

PhongProgram::PhongProgram()
{
	std::shared_ptr<VertexShader> verShader = std::make_shared<VertexShader>
		("\
		attribute	vec4	nb_Position;\
		attribute	vec2	nb_TextCoord;\
		attribute	vec3	nb_Normal;\
		uniform		mat4	nb_Mvp;\
		uniform		mat4	nb_M;\
		uniform		mat4	nb_V;\
		uniform		mat4	nb_P;\
		\
		varying		vec2	vTextureCoord;\
		varying		vec3	vNormal;\
		varying		vec3	vFragPos;\
		\
		void main()\
		{\
			gl_Position = nb_Mvp * nb_Position;\
			vTextureCoord = nb_TextCoord;\
			vNormal = mat3(nb_M)*nb_Normal;\
			vFragPos = vec3(nb_M * nb_Position);\
		}\
	");
	std::shared_ptr<FragmentShader> fragShader = std::make_shared<FragmentShader>
		("\
		struct Material {\
			sampler2D base;\
			float	shininess;\
		};\
		struct Light {\
			vec3	direction;\
			vec3	ambient;\
			vec3	diffuse;\
			vec3	specular;\
		};\
		varying		vec2	vTextureCoord;\
		varying		vec3	vNormal;\
		varying		vec3	vFragPos;\
		\
		uniform		vec3	viewPos;\
		uniform		Material	material;\
		uniform		Light	light;\
		\
		void main()\
		{\
			vec3 ambient = light.ambient;\
			\
			vec3 norm = normalize(vNormal);\
			vec3 lightDir = normalize(light.direction);\
			float diffFactor = max(dot(norm, lightDir), 0.0);\
			vec3 diffuse = light.diffuse * diffFactor;\
			\
			vec3 viewDir = normalize(viewPos - vFragPos);\
			vec3 reflectDir = normalize(reflect(lightDir, norm));\
			float specFactor = pow(max(dot(norm, normalize(viewDir+lightDir)), 0.0), material.shininess);\
			vec3 specular = light.specular * specFactor;\
			\
			vec3 baseColor = vec3(1.0f, 0.5f, 0.31f);\
			gl_FragColor = vec4((ambient + diffuse + specular) * baseColor, 1.0f);\
		}\
	");
	verShader->compile();
	fragShader->compile();
	setVertexShader(verShader);
	setFragmentShader(fragShader);
	//必须在link之前绑定
	bindAttributeLocation(Program::positionLocation, "nb_Position");
	bindAttributeLocation(Program::colorLocation, "nb_Color");
	bindAttributeLocation(Program::texCoordLocaltion, "nb_TextCoord");
	bindAttributeLocation(Program::normalLocation, "nb_Normal");
	link();

}

std::shared_ptr<CubeProgram> CubeProgram::instance()
{
	static std::shared_ptr<CubeProgram> p;
	if (!p)
		p = std::make_shared<CubeProgram>();
	return p;
}

CubeProgram::CubeProgram()
{
	std::shared_ptr<VertexShader> verShader = std::make_shared<VertexShader>
		("\
		attribute	vec4	nb_Position;\
		uniform		mat4	nb_Mvp;\
		varying		vec3	vary_textureCoord;\
		\
		void main()\
		{\
			gl_Position = nb_Mvp * nb_Position;\
			vary_textureCoord = -nb_Position.xyz;\
		}\
	");
	std::shared_ptr<FragmentShader> fragShader = std::make_shared<FragmentShader>
		("\
		varying		vec3		vary_textureCoord;\
		uniform		samplerCube	unif_sampler;\
		\
		void main()\
		{\
			gl_FragColor = textureCube(unif_sampler, vary_textureCoord);\
		}\
	");
	verShader->compile();
	fragShader->compile();
	setVertexShader(verShader);
	setFragmentShader(fragShader);
	//必须在link之前绑定
	bindAttributeLocation(Program::positionLocation, "nb_Position");
	bindAttributeLocation(Program::colorLocation, "nb_Color");
	bindAttributeLocation(Program::texCoordLocaltion, "nb_TextCoord");
	bindAttributeLocation(Program::normalLocation, "nb_Normal");
	link();
}